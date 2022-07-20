#ifndef HVM_H_
#define HVM_H_

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NOTE: Stolen from https://stackoverflow.com/a/3312896
#if defined(__GNUC__) || defined(__clang__)
#define PACK(__Declaration__) __Declaration__ __attribute__((__packed__))
#elif defined(_MSC_VER)
#define PACK(__Declaration__)                                                  \
  __pragma(pack(push, 1)) __Declaration__ __pragma(pack(pop))
#else
#error                                                                         \
    "Packed attributes for struct is not implemented for this compiler. This may result in a program working incorrectly. Feel free to fix that and submit a Pull Request to https://github.com/frexsdev/hvm"
#endif

#define HVM_WORD_SIZE 8
#define HVM_STACK_CAPACITY 1024
#define HVM_PROGRAM_CAPACITY 1024
#define HVM_NATIVES_CAPACITY 1024
#define HVM_MEMORY_CAPACITY (640 * 1000)

#define HACK_BINDINGS_CAPACITY 1024
#define HACK_DEFERRED_OPERANDS_CAPACITY 1024
#define HACK_COMMENT_SYMBOL ';'
#define HACK_PP_SYMBOL '%'
#define HACK_MAX_INCLUDE_LEVEL 69

#define ARENA_CAPACITY (1000 * 1000 * 1000)

typedef struct {
  size_t count;
  const char *data;
} String_View;

// printf macros for String_View
#define SV_Fmt ".*s"
#define SV_Arg(sv) (int)sv.count, sv.data
// USAGE:
//   String_View name = ...;
//   printf("Name: %"SV_Fmt"\n", SV_Arg(name));

String_View sv_from_cstr(const char *cstr);
String_View sv_trim_left(String_View sv);
String_View sv_trim_right(String_View sv);
String_View sv_trim(String_View sv);
String_View sv_chop_by_delim(String_View *sv, char delim);
bool sv_eq(String_View a, String_View b);
int sv_to_int(String_View sv);

typedef enum {
  ERR_OK = 0,
  ERR_STACK_OVERFLOW,
  ERR_STACK_UNDERFLOW,
  ERR_ILLEGAL_INST,
  ERR_ILLEGAL_INST_ACCESS,
  ERR_ILLEGAL_OPERAND,
  ERR_ILLEGAL_MEMORY_ACCESS,
  ERR_DIV_BY_ZERO,
} Err;

const char *err_as_cstr(Err err);

typedef enum {
  INST_NOP = 0,
  INST_PUSH,
  INST_DROP,
  INST_DUP,
  INST_SWAP,
  INST_PLUSI,
  INST_MINUSI,
  INST_MULTI,
  INST_DIVI,
  INST_MODI,
  INST_PLUSF,
  INST_MINUSF,
  INST_MULTF,
  INST_DIVF,
  INST_JMP,
  INST_JMP_IF,
  INST_RET,
  INST_CALL,
  INST_NATIVE,
  INST_HALT,
  INST_NOT,

  INST_EQI,
  INST_GEI,
  INST_GTI,
  INST_LEI,
  INST_LTI,
  INST_NEI,

  INST_EQF,
  INST_GEF,
  INST_GTF,
  INST_LEF,
  INST_LTF,
  INST_NEF,

  INST_ANDB,
  INST_ORB,
  INST_XOR,
  INST_SHR,
  INST_SHL,
  INST_NOTB,
  INST_READ8,
  INST_READ16,
  INST_READ32,
  INST_READ64,
  INST_WRITE8,
  INST_WRITE16,
  INST_WRITE32,
  INST_WRITE64,

  INST_I2F,
  INST_U2F,
  INST_F2I,
  INST_F2U,

  NUMBER_OF_INSTS,
} Inst_Type;

const char *inst_name(Inst_Type type);
bool inst_has_operand(Inst_Type type);
bool inst_by_name(String_View name, Inst_Type *output);

typedef uint64_t Inst_Addr;
typedef uint64_t Memory_Addr;

typedef union {
  uint64_t as_u64;
  int64_t as_i64;
  double as_f64;
  void *as_ptr;
} Word;

Word word_u64(uint64_t u64);
Word word_i64(int64_t i64);
Word word_f64(double f64);
Word word_ptr(void *ptr);

static_assert(sizeof(Word) == HVM_WORD_SIZE,
              "The HVM's Word is expected to be 64 bits");

typedef struct {
  Inst_Type type;
  Word operand;
} Inst;

typedef struct Hvm Hvm;

typedef Err (*Hvm_Native)(Hvm *);

struct Hvm {
  Word stack[HVM_STACK_CAPACITY];
  uint64_t stack_size;

  Inst program[HVM_PROGRAM_CAPACITY];
  uint64_t program_size;
  Inst_Addr ip;

  Hvm_Native natives[HVM_NATIVES_CAPACITY];
  size_t natives_size;

  uint8_t memory[HVM_MEMORY_CAPACITY];

  bool halt;
};

Err hvm_execute_inst(Hvm *hvm);
Err hvm_execute_program(Hvm *hvm, int limit);
void hvm_push_native(Hvm *hvm, Hvm_Native native);
void hvm_dump_stack(FILE *stream, const Hvm *hvm);
void hvm_load_program_from_file(Hvm *hvm, const char *file_path);

#define HAR_MAGIC 0x4D5648
#define HAR_VERSION 5

PACK(struct Har_Meta {
  uint32_t magic;
  uint16_t version;
  uint64_t program_size;
  uint64_t entry;
  uint64_t memory_size;
  uint64_t memory_capacity;
});

typedef struct Har_Meta Har_Meta;

typedef struct {
  String_View name;
  Word value;
} Binding;

typedef struct {
  Inst_Addr addr;
  String_View name;
} Deferred_Operand;

// NOTE: https://en.wikipedia.org/wiki/Region-based_memory_management
typedef struct {
  char buffer[ARENA_CAPACITY];
  size_t size;
} Arena;

void *arena_alloc(Arena *arena, size_t size);
String_View arena_slurp_file(Arena *arena, String_View file_path);
String_View arena_sv_concat2(Arena *arena, const char *a, const char *b);
const char *arena_cstr_concat2(Arena *arena, const char *a, const char *b);

typedef struct {
  Binding bindings[HACK_BINDINGS_CAPACITY];
  size_t bindings_size;

  Deferred_Operand deferred_operands[HACK_DEFERRED_OPERANDS_CAPACITY];
  size_t deferred_operands_size;

  Inst program[HVM_PROGRAM_CAPACITY];
  uint64_t program_size;
  Inst_Addr entry;
  bool has_entry;
  String_View deferred_entry_binding_name;

  uint8_t memory[HVM_MEMORY_CAPACITY];
  size_t memory_size;
  size_t memory_capacity;

  Arena arena;

  size_t include_level;
} Hack;

bool hack_resolve_binding(const Hack *hack, String_View name, Word *output);
bool hack_bind_value(Hack *hack, String_View name, Word word);
void hack_push_deferred_operand(Hack *hack, Inst_Addr addr, String_View name);
bool hack_translate_literal(Hack *hack, String_View sv, Word *output);
void hack_save_to_file(Hack *hack, const char *output_file_path);
Word hack_push_string_to_memory(Hack *hack, String_View sv);
void hack_translate_source(Hack *hack, String_View input_file_path);

void hvm_load_standard_natives(Hvm *hvm);

Err native_alloc(Hvm *hvm);
Err native_free(Hvm *hvm);
Err native_print_f64(Hvm *hvm);
Err native_print_i64(Hvm *hvm);
Err native_print_u64(Hvm *hvm);
Err native_print_ptr(Hvm *hvm);
Err native_dump_memory(Hvm *hvm);
Err native_write(Hvm *hvm);

#endif // HVM_H_

#ifdef HVM_IMPLEMENTATION

Word word_u64(uint64_t u64) { return (Word){.as_u64 = u64}; }

Word word_i64(int64_t i64) { return (Word){.as_i64 = i64}; }

Word word_f64(double f64) { return (Word){.as_f64 = f64}; }

Word word_ptr(void *ptr) { return (Word){.as_ptr = ptr}; }

bool inst_has_operand(Inst_Type type) {
  switch (type) {
  case INST_NOP:
    return false;
  case INST_PUSH:
    return true;
  case INST_DROP:
    return false;
  case INST_DUP:
    return true;
  case INST_PLUSI:
    return false;
  case INST_MINUSI:
    return false;
  case INST_MULTI:
    return false;
  case INST_DIVI:
    return false;
  case INST_MODI:
    return false;
  case INST_PLUSF:
    return false;
  case INST_MINUSF:
    return false;
  case INST_MULTF:
    return false;
  case INST_DIVF:
    return false;
  case INST_JMP:
    return true;
  case INST_JMP_IF:
    return true;
  case INST_HALT:
    return false;
  case INST_SWAP:
    return true;
  case INST_NOT:
    return false;
  case INST_EQF:
    return false;
  case INST_GEF:
    return false;
  case INST_GTF:
    return false;
  case INST_LEF:
    return false;
  case INST_LTF:
    return false;
  case INST_NEF:
    return false;
  case INST_EQI:
    return false;
  case INST_GEI:
    return false;
  case INST_GTI:
    return false;
  case INST_LEI:
    return false;
  case INST_LTI:
    return false;
  case INST_NEI:
    return false;
  case INST_RET:
    return false;
  case INST_CALL:
    return true;
  case INST_NATIVE:
    return true;
  case INST_ANDB:
    return false;
  case INST_ORB:
    return false;
  case INST_XOR:
    return false;
  case INST_SHR:
    return false;
  case INST_SHL:
    return false;
  case INST_NOTB:
    return false;
  case INST_READ8:
    return false;
  case INST_READ16:
    return false;
  case INST_READ32:
    return false;
  case INST_READ64:
    return false;
  case INST_WRITE8:
    return false;
  case INST_WRITE16:
    return false;
  case INST_WRITE32:
    return false;
  case INST_WRITE64:
    return false;
  case INST_I2F:
    return false;
  case INST_U2F:
    return false;
  case INST_F2I:
    return false;
  case INST_F2U:
    return false;
  case NUMBER_OF_INSTS:
  default:
    assert(false && "inst_has_operand: unreachable");
    exit(1);
  }
}

bool inst_by_name(String_View name, Inst_Type *output) {
  for (Inst_Type type = (Inst_Type)0; type < NUMBER_OF_INSTS; type += 1) {
    if (sv_eq(sv_from_cstr(inst_name(type)), name)) {
      *output = type;
      return true;
    }
  }

  return false;
}

const char *inst_name(Inst_Type type) {
  switch (type) {
  case INST_NOP:
    return "nop";
  case INST_PUSH:
    return "push";
  case INST_DROP:
    return "drop";
  case INST_DUP:
    return "dup";
  case INST_PLUSI:
    return "plusi";
  case INST_MINUSI:
    return "minusi";
  case INST_MULTI:
    return "multi";
  case INST_DIVI:
    return "divi";
  case INST_MODI:
    return "modi";
  case INST_PLUSF:
    return "plusf";
  case INST_MINUSF:
    return "minusf";
  case INST_MULTF:
    return "multf";
  case INST_DIVF:
    return "divf";
  case INST_JMP:
    return "jmp";
  case INST_JMP_IF:
    return "jmp_if";
  case INST_HALT:
    return "halt";
  case INST_SWAP:
    return "swap";
  case INST_NOT:
    return "not";
  case INST_EQI:
    return "eqi";
  case INST_GEI:
    return "gei";
  case INST_GTI:
    return "gti";
  case INST_LEI:
    return "lei";
  case INST_LTI:
    return "lti";
  case INST_NEI:
    return "nei";
  case INST_EQF:
    return "eqf";
  case INST_GEF:
    return "gef";
  case INST_GTF:
    return "gtf";
  case INST_LEF:
    return "lef";
  case INST_LTF:
    return "ltf";
  case INST_NEF:
    return "nef";
  case INST_RET:
    return "ret";
  case INST_CALL:
    return "call";
  case INST_NATIVE:
    return "native";
  case INST_ANDB:
    return "andb";
  case INST_ORB:
    return "orb";
  case INST_XOR:
    return "xor";
  case INST_SHR:
    return "shr";
  case INST_SHL:
    return "shl";
  case INST_NOTB:
    return "notb";
  case INST_READ8:
    return "read8";
  case INST_READ16:
    return "read16";
  case INST_READ32:
    return "read32";
  case INST_READ64:
    return "read64";
  case INST_WRITE8:
    return "write8";
  case INST_WRITE16:
    return "write16";
  case INST_WRITE32:
    return "write32";
  case INST_WRITE64:
    return "write64";
  case INST_I2F:
    return "i2f";
  case INST_U2F:
    return "u2f";
  case INST_F2I:
    return "f2i";
  case INST_F2U:
    return "f2u";
  case NUMBER_OF_INSTS:
  default:
    assert(false && "inst_name: unreachable");
    exit(1);
  }
}

const char *err_as_cstr(Err err) {
  switch (err) {
  case ERR_OK:
    return "ERR_OK";
  case ERR_STACK_OVERFLOW:
    return "ERR_STACK_OVERFLOW";
  case ERR_STACK_UNDERFLOW:
    return "ERR_STACK_UNDERFLOW";
  case ERR_ILLEGAL_INST:
    return "ERR_ILLEGAL_INST";
  case ERR_ILLEGAL_OPERAND:
    return "ERR_ILLEGAL_OPERAND";
  case ERR_ILLEGAL_INST_ACCESS:
    return "ERR_ILLEGAL_INST_ACCESS";
  case ERR_DIV_BY_ZERO:
    return "ERR_DIV_BY_ZERO";
  case ERR_ILLEGAL_MEMORY_ACCESS:
    return "ERR_ILLEGAL_MEMORY_ACCESS";
  default:
    assert(false && "err_as_cstr: Unreachable");
    exit(1);
  }
}

Err hvm_execute_program(Hvm *hvm, int limit) {
  while (limit != 0 && !hvm->halt) {
    Err err = hvm_execute_inst(hvm);
    if (err != ERR_OK) {
      return err;
    }
    if (limit > 0) {
      --limit;
    }
  }

  return ERR_OK;
}

#define BINARY_OP(hvm, in, out, op)                                            \
  do {                                                                         \
    if ((hvm)->stack_size < 2) {                                               \
      return ERR_STACK_UNDERFLOW;                                              \
    }                                                                          \
                                                                               \
    (hvm)->stack[(hvm)->stack_size - 2].as_##out =                             \
        (hvm)                                                                  \
            ->stack[(hvm)->stack_size - 2]                                     \
            .as_##in op(hvm)                                                   \
            ->stack[(hvm)->stack_size - 1]                                     \
            .as_##in;                                                          \
    (hvm)->stack_size -= 1;                                                    \
    (hvm)->ip += 1;                                                            \
  } while (false)

#define CAST_OP(hvm, src, dst, cast)                                           \
  do {                                                                         \
    if ((hvm)->stack_size < 1) {                                               \
      return ERR_STACK_UNDERFLOW;                                              \
    }                                                                          \
                                                                               \
    (hvm)->stack[(hvm)->stack_size - 1].as_##dst =                             \
        cast(hvm)->stack[(hvm)->stack_size - 1].as_##src;                      \
    (hvm)->ip += 1;                                                            \
  } while (false)

Err hvm_execute_inst(Hvm *hvm) {
  if (hvm->ip >= hvm->program_size) {
    return ERR_ILLEGAL_INST_ACCESS;
  }

  Inst inst = hvm->program[hvm->ip];

  switch (inst.type) {
  case INST_NOP:
    hvm->ip += 1;
    break;

  case INST_PUSH:
    if (hvm->stack_size >= HVM_STACK_CAPACITY) {
      return ERR_STACK_OVERFLOW;
    }
    hvm->stack[hvm->stack_size++] = inst.operand;
    hvm->ip += 1;
    break;

  case INST_DROP:
    if (hvm->stack_size < 1) {
      return ERR_STACK_UNDERFLOW;
    }
    hvm->stack_size -= 1;
    hvm->ip += 1;
    break;

  case INST_PLUSI:
    BINARY_OP(hvm, u64, u64, +);
    break;

  case INST_MINUSI:
    BINARY_OP(hvm, u64, u64, -);
    break;

  case INST_MULTI:
    BINARY_OP(hvm, u64, u64, *);
    break;

  case INST_DIVI:
    if (hvm->stack[hvm->stack_size - 1].as_u64 == 0) {
      return ERR_DIV_BY_ZERO;
    }

    BINARY_OP(hvm, u64, u64, /);
    break;

  case INST_MODI:
    if (hvm->stack[hvm->stack_size - 1].as_u64 == 0) {
      return ERR_DIV_BY_ZERO;
    }

    BINARY_OP(hvm, u64, u64, %);
    break;

  case INST_PLUSF:
    BINARY_OP(hvm, f64, f64, +);
    break;

  case INST_MINUSF:
    BINARY_OP(hvm, f64, f64, -);
    break;

  case INST_MULTF:
    BINARY_OP(hvm, f64, f64, *);
    break;

  case INST_DIVF:
    BINARY_OP(hvm, f64, f64, /);
    break;

  case INST_JMP:
    hvm->ip = inst.operand.as_u64;
    break;

  case INST_RET:
    if (hvm->stack_size < 1) {
      return ERR_STACK_UNDERFLOW;
    }

    hvm->ip = hvm->stack[hvm->stack_size - 1].as_u64;
    hvm->stack_size -= 1;
    break;

  case INST_CALL:
    if (hvm->stack_size >= HVM_STACK_CAPACITY) {
      return ERR_STACK_OVERFLOW;
    }

    hvm->stack[hvm->stack_size++].as_u64 = hvm->ip + 1;
    hvm->ip = inst.operand.as_u64;
    break;

  case INST_NATIVE:
    if (inst.operand.as_u64 > hvm->natives_size) {
      return ERR_ILLEGAL_OPERAND;
    }
    const Err err = hvm->natives[inst.operand.as_u64](hvm);
    if (err != ERR_OK) {
      return err;
    }
    hvm->ip += 1;
    break;

  case INST_HALT:
    hvm->halt = 1;
    break;

  case INST_EQF:
    BINARY_OP(hvm, f64, u64, ==);
    break;

  case INST_GEF:
    BINARY_OP(hvm, f64, u64, >=);
    break;

  case INST_GTF:
    BINARY_OP(hvm, f64, u64, >);
    break;

  case INST_LEF:
    BINARY_OP(hvm, f64, u64, <=);
    break;

  case INST_LTF:
    BINARY_OP(hvm, f64, u64, <);
    break;

  case INST_NEF:
    BINARY_OP(hvm, f64, u64, !=);
    break;

  case INST_EQI:
    BINARY_OP(hvm, u64, u64, ==);
    break;

  case INST_GEI:
    BINARY_OP(hvm, u64, u64, >=);
    break;

  case INST_GTI:
    BINARY_OP(hvm, u64, u64, >);
    break;

  case INST_LEI:
    BINARY_OP(hvm, u64, u64, <=);
    break;

  case INST_LTI:
    BINARY_OP(hvm, u64, u64, <);
    break;

  case INST_NEI:
    BINARY_OP(hvm, u64, u64, !=);
    break;

  case INST_JMP_IF:
    if (hvm->stack_size < 1) {
      return ERR_STACK_UNDERFLOW;
    }

    if (hvm->stack[hvm->stack_size - 1].as_u64) {
      hvm->ip = inst.operand.as_u64;
    } else {
      hvm->ip += 1;
    }

    hvm->stack_size -= 1;
    break;

  case INST_DUP:
    if (hvm->stack_size >= HVM_STACK_CAPACITY) {
      return ERR_STACK_OVERFLOW;
    }

    if (hvm->stack_size - inst.operand.as_u64 <= 0) {
      return ERR_STACK_UNDERFLOW;
    }

    hvm->stack[hvm->stack_size] =
        hvm->stack[hvm->stack_size - 1 - inst.operand.as_u64];
    hvm->stack_size += 1;
    hvm->ip += 1;
    break;

  case INST_SWAP:
    if (inst.operand.as_u64 >= hvm->stack_size) {
      return ERR_STACK_UNDERFLOW;
    }

    const uint64_t a = hvm->stack_size - 1;
    const uint64_t b = hvm->stack_size - 1 - inst.operand.as_u64;

    Word t = hvm->stack[a];
    hvm->stack[a] = hvm->stack[b];
    hvm->stack[b] = t;
    hvm->ip += 1;
    break;

  case INST_NOT:
    if (hvm->stack_size < 1) {
      return ERR_STACK_UNDERFLOW;
    }

    hvm->stack[hvm->stack_size - 1].as_u64 =
        !hvm->stack[hvm->stack_size - 1].as_u64;
    hvm->ip += 1;
    break;

  case INST_ANDB:
    BINARY_OP(hvm, u64, u64, &);
    break;

  case INST_ORB:
    BINARY_OP(hvm, u64, u64, |);
    break;

  case INST_XOR:
    BINARY_OP(hvm, u64, u64, ^);
    break;

  case INST_SHR:
    BINARY_OP(hvm, u64, u64, >>);
    break;

  case INST_SHL:
    BINARY_OP(hvm, u64, u64, <<);
    break;

  case INST_NOTB:
    if (hvm->stack_size < 1) {
      return ERR_STACK_UNDERFLOW;
    }

    hvm->stack[hvm->stack_size - 1].as_u64 =
        ~hvm->stack[hvm->stack_size - 1].as_u64;
    hvm->ip += 1;
    break;

  case INST_READ8: {
    if (hvm->stack_size < 1) {
      return ERR_STACK_UNDERFLOW;
    }
    const Memory_Addr addr = hvm->stack[hvm->stack_size - 1].as_u64;
    if (addr >= HVM_MEMORY_CAPACITY) {
      return ERR_ILLEGAL_MEMORY_ACCESS;
    }
    hvm->stack[hvm->stack_size - 1].as_u64 = hvm->memory[addr];
    hvm->ip += 1;
  } break;

  case INST_READ16: {
    if (hvm->stack_size < 1) {
      return ERR_STACK_UNDERFLOW;
    }
    const Memory_Addr addr = hvm->stack[hvm->stack_size - 1].as_u64;
    if (addr >= HVM_MEMORY_CAPACITY - 1) {
      return ERR_ILLEGAL_MEMORY_ACCESS;
    }
    hvm->stack[hvm->stack_size - 1].as_u64 = *(uint16_t *)&hvm->memory[addr];
    hvm->ip += 1;
  } break;

  case INST_READ32: {
    if (hvm->stack_size < 1) {
      return ERR_STACK_UNDERFLOW;
    }
    const Memory_Addr addr = hvm->stack[hvm->stack_size - 1].as_u64;
    if (addr >= HVM_MEMORY_CAPACITY - 3) {
      return ERR_ILLEGAL_MEMORY_ACCESS;
    }
    hvm->stack[hvm->stack_size - 1].as_u64 = *(uint32_t *)&hvm->memory[addr];
    hvm->ip += 1;
  } break;

  case INST_READ64: {
    if (hvm->stack_size < 1) {
      return ERR_STACK_UNDERFLOW;
    }
    const Memory_Addr addr = hvm->stack[hvm->stack_size - 1].as_u64;
    if (addr >= HVM_MEMORY_CAPACITY - 7) {
      return ERR_ILLEGAL_MEMORY_ACCESS;
    }
    hvm->stack[hvm->stack_size - 1].as_u64 = *(uint64_t *)&hvm->memory[addr];
    hvm->ip += 1;
  } break;

  case INST_WRITE8: {
    if (hvm->stack_size < 2) {
      return ERR_STACK_UNDERFLOW;
    }
    const Memory_Addr addr = hvm->stack[hvm->stack_size - 2].as_u64;
    if (addr >= HVM_MEMORY_CAPACITY) {
      return ERR_ILLEGAL_MEMORY_ACCESS;
    }
    hvm->memory[addr] = (uint8_t)hvm->stack[hvm->stack_size - 1].as_u64;
    hvm->stack_size -= 2;
    hvm->ip += 1;
  } break;

  case INST_WRITE16: {
    if (hvm->stack_size < 2) {
      return ERR_STACK_UNDERFLOW;
    }
    const Memory_Addr addr = hvm->stack[hvm->stack_size - 2].as_u64;
    if (addr >= HVM_MEMORY_CAPACITY - 1) {
      return ERR_ILLEGAL_MEMORY_ACCESS;
    }
    *(uint16_t *)&hvm->memory[addr] =
        (uint16_t)hvm->stack[hvm->stack_size - 1].as_u64;
    hvm->stack_size -= 2;
    hvm->ip += 1;
  } break;

  case INST_WRITE32: {
    if (hvm->stack_size < 2) {
      return ERR_STACK_UNDERFLOW;
    }
    const Memory_Addr addr = hvm->stack[hvm->stack_size - 2].as_u64;
    if (addr >= HVM_MEMORY_CAPACITY - 3) {
      return ERR_ILLEGAL_MEMORY_ACCESS;
    }
    *(uint32_t *)&hvm->memory[addr] =
        (uint32_t)hvm->stack[hvm->stack_size - 1].as_u64;
    hvm->stack_size -= 2;
    hvm->ip += 1;
  } break;

  case INST_WRITE64: {
    if (hvm->stack_size < 2) {
      return ERR_STACK_UNDERFLOW;
    }
    const Memory_Addr addr = hvm->stack[hvm->stack_size - 2].as_u64;
    if (addr >= HVM_MEMORY_CAPACITY - 7) {
      return ERR_ILLEGAL_MEMORY_ACCESS;
    }
    *(uint64_t *)&hvm->memory[addr] = hvm->stack[hvm->stack_size - 1].as_u64;
    hvm->stack_size -= 2;
    hvm->ip += 1;
  } break;

  case INST_I2F:
    CAST_OP(hvm, i64, f64, (double));
    break;

  case INST_U2F:
    CAST_OP(hvm, u64, f64, (double));
    break;

  case INST_F2I:
    CAST_OP(hvm, f64, i64, (int64_t));
    break;

  case INST_F2U:
    CAST_OP(hvm, f64, u64, (uint64_t)(int64_t));
    break;

  case NUMBER_OF_INSTS:
  default:
    return ERR_ILLEGAL_INST;
  }

  return ERR_OK;
}

void hvm_push_native(Hvm *hvm, Hvm_Native native) {
  assert(hvm->natives_size < HVM_NATIVES_CAPACITY);
  hvm->natives[hvm->natives_size++] = native;
}

void hvm_dump_stack(FILE *stream, const Hvm *hvm) {
  fprintf(stream, "Stack:\n");
  if (hvm->stack_size > 0) {
    for (Inst_Addr i = 0; i < hvm->stack_size; ++i) {
      fprintf(stream,
              "  u64: %" PRIu64 ", i64: %" PRId64 ", f64: %lf, ptr: %p\n",
              hvm->stack[i].as_u64, hvm->stack[i].as_i64, hvm->stack[i].as_f64,
              hvm->stack[i].as_ptr);
    }
  } else {
    fprintf(stream, "  [empty]\n");
  }
}

void hvm_load_program_from_file(Hvm *hvm, const char *file_path) {
  FILE *f = fopen(file_path, "rb");
  if (f == NULL) {
    fprintf(stderr, "ERROR: Could not open file `%s`: %s\n", file_path,
            strerror(errno));
    exit(1);
  }

  Har_Meta meta = {0};

  size_t n = fread(&meta, sizeof(meta), 1, f);
  if (n < 1) {
    fprintf(stderr, "ERROR: Could not read meta data from file `%s`: %s\n",
            file_path, strerror(errno));
    exit(1);
  }

  if (meta.magic != HAR_MAGIC) {
    fprintf(stderr,
            "ERROR: %s does not appear to be a valid Har. "
            "Unexpected magic %04X. Expected %04X.\n",
            file_path, meta.magic, HAR_MAGIC);
    exit(1);
  }

  if (meta.version != HAR_VERSION) {
    fprintf(stderr,
            "ERROR: %s: unsupported version of Har %d. Expected version %d.\n",
            file_path, meta.version, HAR_VERSION);
    exit(1);
  }

  if (meta.program_size > HVM_PROGRAM_CAPACITY) {
    fprintf(stderr,
            "ERROR: %s: program section is too big. The file contains %" PRIu64
            " program instruction. But the capacity is %" PRIu64 "\n",
            file_path, meta.program_size, (uint64_t)HVM_PROGRAM_CAPACITY);
    exit(1);
  }

  hvm->ip = meta.entry;

  if (meta.memory_capacity > HVM_MEMORY_CAPACITY) {
    fprintf(stderr,
            "ERROR: %s: memory section is too big. The file wants %" PRIu64
            " bytes. But the capacity is %" PRIu64 " bytes\n",
            file_path, meta.memory_capacity, (uint64_t)HVM_MEMORY_CAPACITY);
    exit(1);
  }

  if (meta.memory_size > meta.memory_capacity) {
    fprintf(stderr,
            "ERROR: %s: memory size %" PRIu64
            " is greater than declared memory capacity %" PRIu64 "\n",
            file_path, meta.memory_size, meta.memory_capacity);
    exit(1);
  }

  hvm->program_size =
      fread(hvm->program, sizeof(hvm->program[0]), meta.program_size, f);

  if (hvm->program_size != meta.program_size) {
    fprintf(stderr,
            "ERROR: %s: read %zd program instructions, but expected %" PRIu64
            "\n",
            file_path, hvm->program_size, meta.program_size);
    exit(1);
  }

  n = fread(hvm->memory, sizeof(hvm->memory[0]), meta.memory_size, f);

  if (n != meta.memory_size) {
    fprintf(stderr,
            "ERROR: %s: read %zd bytes of memory section, but expected %" PRIu64
            " bytes.\n",
            file_path, n, meta.memory_size);
    exit(1);
  }

  fclose(f);
}

String_View sv_from_cstr(const char *cstr) {
  return (String_View){
      .count = strlen(cstr),
      .data = cstr,
  };
}

String_View sv_trim_left(String_View sv) {
  size_t i = 0;
  while (i < sv.count && isspace(sv.data[i])) {
    i += 1;
  }

  return (String_View){
      .count = sv.count - i,
      .data = sv.data + i,
  };
}

String_View sv_trim_right(String_View sv) {
  size_t i = 0;
  while (i < sv.count && isspace(sv.data[sv.count - 1 - i])) {
    i += 1;
  }

  return (String_View){.count = sv.count - i, .data = sv.data};
}

String_View sv_trim(String_View sv) { return sv_trim_right(sv_trim_left(sv)); }

String_View sv_chop_by_delim(String_View *sv, char delim) {
  size_t i = 0;
  while (i < sv->count && sv->data[i] != delim) {
    i += 1;
  }

  String_View result = {
      .count = i,
      .data = sv->data,
  };

  if (i < sv->count) {
    sv->count -= i + 1;
    sv->data += i + 1;
  } else {
    sv->count -= i;
    sv->data += i;
  }

  return result;
}

bool sv_eq(String_View a, String_View b) {
  if (a.count != b.count) {
    return false;
  } else {
    return memcmp(a.data, b.data, a.count) == 0;
  }
}

int sv_to_int(String_View sv) {
  int result = 0;

  for (size_t i = 0; i < sv.count && isdigit(sv.data[i]); ++i) {
    result = result * 10 + sv.data[i] - '0';
  }

  return result;
}

const char *arena_cstr_concat2(Arena *arena, const char *a, const char *b) {
  const size_t a_len = strlen(a);
  const size_t b_len = strlen(b);
  char *buf = arena_alloc(arena, a_len + b_len + 1);
  memcpy(buf, a, a_len);
  memcpy(buf + a_len, b, b_len);
  buf[a_len + b_len] = '\0';
  return buf;
}

String_View arena_sv_concat2(Arena *arena, const char *a, const char *b) {
  const size_t a_len = strlen(a);
  const size_t b_len = strlen(b);
  char *buf = arena_alloc(arena, a_len + b_len);
  memcpy(buf, a, a_len);
  memcpy(buf + a_len, b, b_len);
  return (String_View){
      .count = a_len + b_len,
      .data = buf,
  };
}

void *arena_alloc(Arena *arena, size_t size) {
  assert(arena->size + size <= ARENA_CAPACITY);

  void *result = arena->buffer + arena->size;
  arena->size += size;
  return result;
}

bool hack_resolve_binding(const Hack *hack, String_View name, Word *output) {
  for (size_t i = 0; i < hack->bindings_size; ++i) {
    if (sv_eq(hack->bindings[i].name, name)) {
      *output = hack->bindings[i].value;
      return true;
    }
  }

  return false;
}

bool hack_bind_value(Hack *hack, String_View name, Word value) {
  assert(hack->bindings_size < HACK_BINDINGS_CAPACITY);

  Word ignore = {0};
  if (hack_resolve_binding(hack, name, &ignore)) {
    return false;
  }

  hack->bindings[hack->bindings_size++] =
      (Binding){.name = name, .value = value};
  return true;
}

void hack_push_deferred_operand(Hack *hack, Inst_Addr addr, String_View name) {
  assert(hack->deferred_operands_size < HACK_DEFERRED_OPERANDS_CAPACITY);
  hack->deferred_operands[hack->deferred_operands_size++] =
      (Deferred_Operand){.addr = addr, .name = name};
}

Word hack_push_string_to_memory(Hack *hack, String_View sv) {
  assert(hack->memory_size + sv.count <= HVM_MEMORY_CAPACITY);

  Word result = word_u64(hack->memory_size);
  memcpy(hack->memory + hack->memory_size, sv.data, sv.count);
  hack->memory_size += sv.count;

  if (hack->memory_size > hack->memory_capacity) {
    hack->memory_capacity = hack->memory_size;
  }

  return result;
}

bool hack_translate_literal(Hack *hack, String_View sv, Word *output) {
  if (sv.count >= 2 && *sv.data == '\'' && sv.data[sv.count - 1] == '\'') {
    if (sv.count - 2 != 1) {
      return false;
    }

    *output = word_u64((uint64_t)sv.data[1]);

    return true;
  } else if (sv.count >= 2 && *sv.data == '"' && sv.data[sv.count - 1] == '"') {
    // TODO(#23): string literals don't support escaped characters
    sv.data += 1;
    sv.count -= 2;
    *output = hack_push_string_to_memory(hack, sv);
  } else {
    char *cstr = arena_alloc(&hack->arena, sv.count + 1);
    memcpy(cstr, sv.data, sv.count);
    cstr[sv.count] = '\0';

    char *endptr = 0;
    Word result = {0};

    result.as_u64 = strtoull(cstr, &endptr, 10);
    if ((size_t)(endptr - cstr) != sv.count) {
      result.as_f64 = strtod(cstr, &endptr);
      if ((size_t)(endptr - cstr) != sv.count) {
        return false;
      }
    }

    *output = result;
  }
  return true;
}

void hack_save_to_file(Hack *hack, const char *file_path) {
  FILE *f = fopen(file_path, "wb");
  if (f == NULL) {
    fprintf(stderr, "ERROR: Could not open file `%s`: %s\n", file_path,
            strerror(errno));
    exit(1);
  }

  Har_Meta meta = {
      .magic = HAR_MAGIC,
      .version = HAR_VERSION,
      .program_size = hack->program_size,
      .entry = hack->entry,
      .memory_size = hack->memory_size,
      .memory_capacity = hack->memory_capacity,
  };

  fwrite(&meta, sizeof(meta), 1, f);
  if (ferror(f)) {
    fprintf(stderr, "ERROR: Could not write to file `%s`: %s\n", file_path,
            strerror(errno));
    exit(1);
  }

  fwrite(hack->program, sizeof(hack->program[0]), hack->program_size, f);
  if (ferror(f)) {
    fprintf(stderr, "ERROR: Could not write to file `%s`: %s\n", file_path,
            strerror(errno));
    exit(1);
  }

  fwrite(hack->memory, sizeof(hack->memory[0]), hack->memory_size, f);
  if (ferror(f)) {
    fprintf(stderr, "ERROR: Could not write to file `%s`: %s\n", file_path,
            strerror(errno));
    exit(1);
  }

  fclose(f);
}

void hack_translate_source(Hack *hack, String_View input_file_path) {
  String_View original_source = arena_slurp_file(&hack->arena, input_file_path);
  String_View source = original_source;

  int line_number = 0;

  // First pass
  while (source.count > 0) {
    String_View line = sv_trim(sv_chop_by_delim(&source, '\n'));
    line = sv_trim(sv_chop_by_delim(&line, HACK_COMMENT_SYMBOL));
    line_number += 1;
    if (line.count > 0) {
      String_View token = sv_trim(sv_chop_by_delim(&line, ' '));

      // Pre-processor
      if (token.count > 0 && *token.data == HACK_PP_SYMBOL) {
        token.count -= 1;
        token.data += 1;
        if (sv_eq(token, sv_from_cstr("bind"))) {
          line = sv_trim(line);
          String_View name = sv_chop_by_delim(&line, ' ');
          if (name.count > 0) {
            line = sv_trim(line);
            String_View value = line;
            Word word = {0};
            if (!hack_translate_literal(hack, value, &word)) {
              fprintf(stderr,
                      "%" SV_Fmt ":%d: ERROR: `%" SV_Fmt "` is not a number",
                      SV_Arg(input_file_path), line_number, SV_Arg(value));
              exit(1);
            }

            if (!hack_bind_value(hack, name, word)) {
              // TODO(#14): label redefinition error does not tell where the
              // first label was already defined
              fprintf(stderr,
                      "%" SV_Fmt ":%d: ERROR: name `%" SV_Fmt
                      "` is already bound\n",
                      SV_Arg(input_file_path), line_number, SV_Arg(name));
              exit(1);
            }
          } else {
            fprintf(stderr,
                    "%" SV_Fmt ":%d: ERROR: binding name is not provided\n",
                    SV_Arg(input_file_path), line_number);
            exit(1);
          }
        } else if (sv_eq(token, sv_from_cstr("include"))) {
          line = sv_trim(line);

          if (line.count > 0) {
            if (*line.data == '"' && line.data[line.count - 1] == '"') {
              line.data += 1;
              line.count -= 2;

              if (hack->include_level + 1 >= HACK_MAX_INCLUDE_LEVEL) {
                fprintf(stderr,
                        "%" SV_Fmt
                        ":%d: ERROR: exceeded maximum include level\n",
                        SV_Arg(input_file_path), line_number);
                exit(1);
              }

              hack_translate_source(hack, line);
            } else {
              fprintf(stderr,
                      "%" SV_Fmt
                      ":%d: ERROR: include file path has to be surrounded "
                      "with quotation marks\n",
                      SV_Arg(input_file_path), line_number);
              exit(1);
            }
          } else {
            fprintf(stderr,
                    "%" SV_Fmt
                    ":%d: ERROR: include file path is not provided\n",
                    SV_Arg(input_file_path), line_number);
            exit(1);
          }
        } else if (sv_eq(token, sv_from_cstr("entry"))) {
          if (hack->has_entry) {
            // TODO: "entry point already set" error does not tell where exactly
            // the entry has been already set
            fprintf(stderr,
                    "%" SV_Fmt
                    ":%d: ERROR: entry point has been already set!\n",
                    SV_Arg(input_file_path), line_number);
            exit(1);
          }

          line = sv_trim(line);

          if (line.count == 0) {
            fprintf(stderr,
                    "%" SV_Fmt
                    ":%d: ERROR: literal or binding name is expected\n",
                    SV_Arg(input_file_path), line_number);
            exit(1);
          }

          Word entry = {0};

          if (!hack_translate_literal(hack, line, &entry)) {
            hack->deferred_entry_binding_name = line;
          } else {
            hack->entry = entry.as_u64;
          }

          hack->has_entry = true;
        } else {
          fprintf(stderr,
                  "%" SV_Fmt
                  ":%d: ERROR: unknown pre-processor directive `%" SV_Fmt "`\n",
                  SV_Arg(input_file_path), line_number, SV_Arg(token));
          exit(1);
        }
      } else {
        // Label binding
        if (token.count > 0 && token.data[token.count - 1] == ':') {
          String_View label = {.count = token.count - 1, .data = token.data};

          if (!hack_bind_value(hack, label, word_u64(hack->program_size))) {
            fprintf(stderr,
                    "%" SV_Fmt ":%d: ERROR: name `%" SV_Fmt
                    "` is already bound to something\n",
                    SV_Arg(input_file_path), line_number, SV_Arg(label));
            exit(1);
          }

          token = sv_trim(sv_chop_by_delim(&line, ' '));
        }

        // Instruction
        if (token.count > 0) {
          String_View operand = line;
          Inst_Type inst_type = INST_NOP;
          if (inst_by_name(token, &inst_type)) {
            assert(hack->program_size < HVM_PROGRAM_CAPACITY);
            hack->program[hack->program_size].type = inst_type;

            if (inst_has_operand(inst_type)) {
              if (operand.count == 0) {
                fprintf(stderr,
                        "%" SV_Fmt ":%d: ERROR: instruction `%" SV_Fmt
                        "` requires an operand\n",
                        SV_Arg(input_file_path), line_number, SV_Arg(token));
                exit(1);
              }

              if (!hack_translate_literal(
                      hack, operand,
                      &hack->program[hack->program_size].operand)) {
                hack_push_deferred_operand(hack, hack->program_size, operand);
              }
            }

            hack->program_size += 1;
          } else {
            fprintf(stderr,
                    "%" SV_Fmt ":%d: ERROR: unknown instruction `%" SV_Fmt
                    "`\n",
                    SV_Arg(input_file_path), line_number, SV_Arg(token));
            exit(1);
          }
        }
      }
    }
  }

  // Second pass
  for (size_t i = 0; i < hack->deferred_operands_size; ++i) {
    String_View name = hack->deferred_operands[i].name;
    if (!hack_resolve_binding(
            hack, name,
            &hack->program[hack->deferred_operands[i].addr].operand)) {
      // TODO(#15): second pass label resolution errors don't report the
      // location in the source code
      fprintf(stderr, "%" SV_Fmt ": ERROR: unknown binding `%" SV_Fmt "`\n",
              SV_Arg(input_file_path), SV_Arg(name));
      exit(1);
    }
  }

  if (hack->has_entry && (hack->deferred_entry_binding_name.count > 0)) {
    Word output = {0};
    if (!hack_resolve_binding(hack, hack->deferred_entry_binding_name,
                              &output)) {
      fprintf(stderr, "%" SV_Fmt ": ERROR: unknown binding `%" SV_Fmt "`\n",
              SV_Arg(input_file_path),
              SV_Arg(hack->deferred_entry_binding_name));
      exit(1);
    }

    hack->entry = output.as_u64;
  }
}

String_View arena_slurp_file(Arena *arena, String_View file_path) {
  char *file_path_cstr = arena_alloc(arena, file_path.count + 1);
  if (file_path_cstr == NULL) {
    fprintf(stderr,
            "ERROR: Could not allocate memory for the file path `%" SV_Fmt
            "`: %s\n",
            SV_Arg(file_path), strerror(errno));
    exit(1);
  }

  memcpy(file_path_cstr, file_path.data, file_path.count);
  file_path_cstr[file_path.count] = '\0';

  FILE *f = fopen(file_path_cstr, "r");
  if (f == NULL) {
    fprintf(stderr, "ERROR: Could not read file `%s`: %s\n", file_path_cstr,
            strerror(errno));
    exit(1);
  }

  if (fseek(f, 0, SEEK_END) < 0) {
    fprintf(stderr, "ERROR: Could not read file `%s`: %s\n", file_path_cstr,
            strerror(errno));
    exit(1);
  }

  long m = ftell(f);
  if (m < 0) {
    fprintf(stderr, "ERROR: Could not read file `%s`: %s\n", file_path_cstr,
            strerror(errno));
    exit(1);
  }

  char *buffer = arena_alloc(arena, (size_t)m);
  if (buffer == NULL) {
    fprintf(stderr, "ERROR: Could not allocate memory for file: %s\n",
            strerror(errno));
    exit(1);
  }

  if (fseek(f, 0, SEEK_SET) < 0) {
    fprintf(stderr, "ERROR: Could not read file `%s`: %s\n", file_path_cstr,
            strerror(errno));
    exit(1);
  }

  size_t n = fread(buffer, 1, (size_t)m, f);
  if (ferror(f)) {
    fprintf(stderr, "ERROR: Could not read file `%s`: %s\n", file_path_cstr,
            strerror(errno));
    exit(1);
  }

  fclose(f);

  return (String_View){
      .count = n,
      .data = buffer,
  };
}

void hvm_load_standard_natives(Hvm *hvm) {
  // TODO(#3): some sort of mechanism to load native functions from DLLs
  hvm_push_native(hvm, native_alloc);       // 0
  hvm_push_native(hvm, native_free);        // 1
  hvm_push_native(hvm, native_print_f64);   // 2
  hvm_push_native(hvm, native_print_i64);   // 3
  hvm_push_native(hvm, native_print_u64);   // 4
  hvm_push_native(hvm, native_print_ptr);   // 5
  hvm_push_native(hvm, native_dump_memory); // 6
  hvm_push_native(hvm, native_write);       // 7
}

Err native_alloc(Hvm *hvm) {
  if (hvm->stack_size < 1) {
    return ERR_STACK_UNDERFLOW;
  }

  hvm->stack[hvm->stack_size - 1].as_ptr =
      malloc(hvm->stack[hvm->stack_size - 1].as_u64);

  return ERR_OK;
}

Err native_free(Hvm *hvm) {
  if (hvm->stack_size < 1) {
    return ERR_STACK_UNDERFLOW;
  }

  free(hvm->stack[hvm->stack_size - 1].as_ptr);
  hvm->stack_size -= 1;

  return ERR_OK;
}

Err native_print_f64(Hvm *hvm) {
  if (hvm->stack_size < 1) {
    return ERR_STACK_UNDERFLOW;
  }

  printf("%lf\n", hvm->stack[hvm->stack_size - 1].as_f64);
  hvm->stack_size -= 1;
  return ERR_OK;
}

Err native_print_i64(Hvm *hvm) {
  if (hvm->stack_size < 1) {
    return ERR_STACK_UNDERFLOW;
  }

  printf("%" PRId64 "\n", hvm->stack[hvm->stack_size - 1].as_i64);
  hvm->stack_size -= 1;
  return ERR_OK;
}

Err native_print_u64(Hvm *hvm) {
  if (hvm->stack_size < 1) {
    return ERR_STACK_UNDERFLOW;
  }

  printf("%" PRIu64 "\n", hvm->stack[hvm->stack_size - 1].as_u64);
  hvm->stack_size -= 1;
  return ERR_OK;
}

Err native_print_ptr(Hvm *hvm) {
  if (hvm->stack_size < 1) {
    return ERR_STACK_UNDERFLOW;
  }

  printf("%p\n", hvm->stack[hvm->stack_size - 1].as_ptr);
  hvm->stack_size -= 1;
  return ERR_OK;
}

Err native_dump_memory(Hvm *hvm) {
  if (hvm->stack_size < 2) {
    return ERR_STACK_UNDERFLOW;
  }

  Memory_Addr addr = hvm->stack[hvm->stack_size - 2].as_u64;
  uint64_t count = hvm->stack[hvm->stack_size - 1].as_u64;

  if (addr >= HVM_MEMORY_CAPACITY) {
    return ERR_ILLEGAL_MEMORY_ACCESS;
  }

  if (addr + count < addr || addr + count >= HVM_MEMORY_CAPACITY) {
    return ERR_ILLEGAL_MEMORY_ACCESS;
  }

  for (uint64_t i = 0; i < count; ++i) {
    printf("%02X ", hvm->memory[addr + i]);
  }
  printf("\n");

  hvm->stack_size -= 2;

  return ERR_OK;
}

Err native_write(Hvm *hvm) {
  if (hvm->stack_size < 2) {
    return ERR_STACK_UNDERFLOW;
  }

  Memory_Addr addr = hvm->stack[hvm->stack_size - 2].as_u64;
  uint64_t count = hvm->stack[hvm->stack_size - 1].as_u64;

  if (addr >= HVM_MEMORY_CAPACITY) {
    return ERR_ILLEGAL_MEMORY_ACCESS;
  }

  if (addr + count < addr || addr + count >= HVM_MEMORY_CAPACITY) {
    return ERR_ILLEGAL_MEMORY_ACCESS;
  }

  fwrite(&hvm->memory[addr], sizeof(hvm->memory[0]), count, stdout);

  hvm->stack_size -= 2;

  return ERR_OK;
}

#endif // HVM_IMPLEMENTATION
