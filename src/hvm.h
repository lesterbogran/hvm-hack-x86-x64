#ifndef HVM_H_
#define HVM_H_

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(xs) (sizeof(xs) / sizeof((xs)[0]))
#define HVM_STACK_CAPACITY 1024
#define HVM_PROGRAM_CAPACITY 1024
#define LABEL_CAPACITY 1024
#define DEFERRED_OPERANDS_CAPACITY 1024
#define NUMBER_LITERAL_CAPACITY 1024

typedef enum {
  ERR_OK = 0,
  ERR_STACK_OVERFLOW,
  ERR_STACK_UNDERFLOW,
  ERR_ILLEGAL_INST,
  ERR_ILLEGAL_INST_ACCESS,
  ERR_ILLEGAL_OPERAND,
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
  INST_PLUSF,
  INST_MINUSF,
  INST_MULTF,
  INST_DIVF,
  INST_JMP,
  INST_JMP_IF,
  INST_RET,
  INST_CALL,
  INST_EQ,
  INST_HALT,
  INST_NOT,
  INST_GEF,
  INST_PRINT_DEBUG,
  NUMBER_OF_INSTS,
} Inst_Type;

const char *inst_name(Inst_Type type);
int inst_has_operand(Inst_Type type);

typedef uint64_t Inst_Addr;

typedef union {
  uint64_t as_u64;
  int64_t as_i64;
  double as_f64;
  void *as_ptr;
} Word;

static_assert(sizeof(Word) == 8, "The HVM's Word is expected to be 64 bits");

typedef struct {
  Inst_Type type;
  Word operand;
} Inst;

typedef struct {
  Word stack[HVM_STACK_CAPACITY];
  uint64_t stack_size;

  Inst program[HVM_PROGRAM_CAPACITY];
  uint64_t program_size;
  Inst_Addr ip;

  int halt;
} Hvm;

Err hvm_execute_inst(Hvm *hvm);
Err hvm_execute_program(Hvm *hvm, int limit);
void hvm_dump_stack(FILE *stream, const Hvm *hvm);
void hvm_load_program_from_memory(Hvm *hvm, Inst *program, size_t program_size);
void hvm_load_program_from_file(Hvm *hvm, const char *file_path);
void hvm_save_program_to_file(const Hvm *hvm, const char *file_path);

typedef struct {
  size_t count;
  const char *data;
} String_View;

String_View cstr_as_sv(const char *cstr);
String_View sv_trim_left(String_View sv);
String_View sv_trim_right(String_View sv);
String_View sv_trim(String_View sv);
String_View sv_chop_by_delim(String_View *sv, char delim);
int sv_eq(String_View a, String_View b);
int sv_to_int(String_View sv);
String_View sv_slurp_file(const char *file_path);

typedef struct {
  String_View name;
  Inst_Addr addr;
} Label;

typedef struct {
  Inst_Addr addr;
  String_View label;
} Deferred_Operand;

typedef struct {
  Label labels[LABEL_CAPACITY];
  size_t labels_size;
  Deferred_Operand deferred_operands[DEFERRED_OPERANDS_CAPACITY];
  size_t deferred_operands_size;
} Basm;

Inst_Addr basm_find_label_addr(const Basm *basm, String_View name);
void basm_push_label(Basm *basm, String_View name, Inst_Addr addr);
void basm_push_deferred_operand(Basm *basm, Inst_Addr addr, String_View label);

void hvm_translate_source(String_View source, Hvm *hvm, Basm *basm);

Word number_literal_as_word(String_View sv);

#endif // HVM_H_

#ifdef HVM_IMPLEMENTATION

int inst_has_operand(Inst_Type type) {
  switch (type) {
  case INST_NOP:
    return 0;
  case INST_PUSH:
    return 1;
  case INST_DROP:
    return 0;
  case INST_DUP:
    return 1;
  case INST_PLUSI:
    return 0;
  case INST_MINUSI:
    return 0;
  case INST_MULTI:
    return 0;
  case INST_DIVI:
    return 0;
  case INST_PLUSF:
    return 0;
  case INST_MINUSF:
    return 0;
  case INST_MULTF:
    return 0;
  case INST_DIVF:
    return 0;
  case INST_JMP:
    return 1;
  case INST_JMP_IF:
    return 1;
  case INST_RET:
    return 0;
  case INST_CALL:
    return 1;
  case INST_EQ:
    return 0;
  case INST_HALT:
    return 0;
  case INST_PRINT_DEBUG:
    return 0;
  case INST_SWAP:
    return 1;
  case INST_NOT:
    return 0;
  case INST_GEF:
    return 0;
  case NUMBER_OF_INSTS:
  default:
    assert(0 && "inst_has_operand: unreachable");
    exit(1);
  }
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
  case INST_RET:
    return "ret";
  case INST_CALL:
    return "call";
  case INST_EQ:
    return "eq";
  case INST_HALT:
    return "halt";
  case INST_PRINT_DEBUG:
    return "print_debug";
  case INST_SWAP:
    return "swap";
  case INST_NOT:
    return "not";
  case INST_GEF:
    return "gef";
  case NUMBER_OF_INSTS:
  default:
    assert(0 && "inst_name: unreachable");
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
  default:
    assert(0 && "err_as_cstr: Unreachable");
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
    if (hvm->stack_size >= HVM_STACK_CAPACITY) {
      return ERR_STACK_OVERFLOW;
    }
    hvm->stack_size -= 1;
    hvm->ip += 1;
    break;

  case INST_PLUSI:
    if (hvm->stack_size < 2) {
      return ERR_STACK_UNDERFLOW;
    }
    hvm->stack[hvm->stack_size - 2].as_u64 +=
        hvm->stack[hvm->stack_size - 1].as_u64;
    hvm->stack_size -= 1;
    hvm->ip += 1;
    break;

  case INST_MINUSI:
    if (hvm->stack_size < 2) {
      return ERR_STACK_UNDERFLOW;
    }
    hvm->stack[hvm->stack_size - 2].as_u64 -=
        hvm->stack[hvm->stack_size - 1].as_u64;
    hvm->stack_size -= 1;
    hvm->ip += 1;
    break;

  case INST_MULTI:
    if (hvm->stack_size < 2) {
      return ERR_STACK_UNDERFLOW;
    }
    hvm->stack[hvm->stack_size - 2].as_u64 *=
        hvm->stack[hvm->stack_size - 1].as_u64;
    hvm->stack_size -= 1;
    hvm->ip += 1;
    break;

  case INST_DIVI:
    if (hvm->stack_size < 2) {
      return ERR_STACK_UNDERFLOW;
    }

    if (hvm->stack[hvm->stack_size - 1].as_u64 == 0) {
      return ERR_DIV_BY_ZERO;
    }

    hvm->stack[hvm->stack_size - 2].as_u64 /=
        hvm->stack[hvm->stack_size - 1].as_u64;
    hvm->stack_size -= 1;
    hvm->ip += 1;
    break;

  case INST_PLUSF:
    if (hvm->stack_size < 2) {
      return ERR_STACK_UNDERFLOW;
    }

    hvm->stack[hvm->stack_size - 2].as_f64 +=
        hvm->stack[hvm->stack_size - 1].as_f64;
    hvm->stack_size -= 1;
    hvm->ip += 1;
    break;

  case INST_MINUSF:
    if (hvm->stack_size < 2) {
      return ERR_STACK_UNDERFLOW;
    }

    hvm->stack[hvm->stack_size - 2].as_f64 -=
        hvm->stack[hvm->stack_size - 1].as_f64;
    hvm->stack_size -= 1;
    hvm->ip += 1;
    break;

  case INST_MULTF:
    if (hvm->stack_size < 2) {
      return ERR_STACK_UNDERFLOW;
    }

    hvm->stack[hvm->stack_size - 2].as_f64 *=
        hvm->stack[hvm->stack_size - 1].as_f64;
    hvm->stack_size -= 1;
    hvm->ip += 1;
    break;

  case INST_DIVF:
    if (hvm->stack_size < 2) {
      return ERR_STACK_UNDERFLOW;
    }

    hvm->stack[hvm->stack_size - 2].as_f64 /=
        hvm->stack[hvm->stack_size - 1].as_f64;
    hvm->stack_size -= 1;
    hvm->ip += 1;
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

  case INST_HALT:
    hvm->halt = 1;
    break;

  case INST_EQ:
    if (hvm->stack_size < 2) {
      return ERR_STACK_UNDERFLOW;
    }

    hvm->stack[hvm->stack_size - 2].as_u64 =
        hvm->stack[hvm->stack_size - 1].as_u64 ==
        hvm->stack[hvm->stack_size - 2].as_u64;
    hvm->stack_size -= 1;
    hvm->ip += 1;
    break;

  case INST_GEF:
    if (hvm->stack_size < 2) {
      return ERR_STACK_UNDERFLOW;
    }

    hvm->stack[hvm->stack_size - 2].as_u64 =
        hvm->stack[hvm->stack_size - 1].as_f64 >=
        hvm->stack[hvm->stack_size - 2].as_f64;
    hvm->stack_size -= 1;
    hvm->ip += 1;
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

  case INST_PRINT_DEBUG:
    if (hvm->stack_size < 1) {
      return ERR_STACK_UNDERFLOW;
    }
    fprintf(stdout, "  u64: %" PRIu64 ", i64: %" PRId64 ", f64: %lf, ptr: %p\n",
            hvm->stack[hvm->stack_size - 1].as_u64,
            hvm->stack[hvm->stack_size - 1].as_i64,
            hvm->stack[hvm->stack_size - 1].as_f64,
            hvm->stack[hvm->stack_size - 1].as_ptr);
    hvm->stack_size -= 1;
    hvm->ip += 1;
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

  case NUMBER_OF_INSTS:
  default:
    return ERR_ILLEGAL_INST;
  }

  return ERR_OK;
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

void hvm_load_program_from_memory(Hvm *hvm, Inst *program,
                                  size_t program_size) {
  assert(program_size < HVM_PROGRAM_CAPACITY);
  memcpy(hvm->program, program, sizeof(program[0]) * program_size);
  hvm->program_size = program_size;
}

void hvm_load_program_from_file(Hvm *hvm, const char *file_path) {
  FILE *f = fopen(file_path, "rb");
  if (f == NULL) {
    fprintf(stderr, "ERROR: Could not open file `%s`: %s\n", file_path,
            strerror(errno));
    exit(1);
  }

  if (fseek(f, 0, SEEK_END) < 0) {
    fprintf(stderr, "ERROR: Could not set position at end of file %s: %s\n",
            file_path, strerror(errno));
    exit(1);
  }

  long m = ftell(f);
  if (m < 0) {
    fprintf(stderr, "ERROR: Could not determine length of file %s: %s\n",
            file_path, strerror(errno));
    exit(1);
  }

  assert(m % sizeof(hvm->program[0]) == 0);
  assert((size_t)m <= HVM_PROGRAM_CAPACITY * sizeof(hvm->program[0]));

  if (fseek(f, 0, SEEK_SET) < 0) {
    fprintf(stderr, "ERROR: Could not rewind file %s: %s\n", file_path,
            strerror(errno));
    exit(1);
  }

  hvm->program_size = fread(hvm->program, sizeof(hvm->program[0]),
                            m / sizeof(hvm->program[0]), f);

  if (ferror(f)) {
    fprintf(stderr, "ERROR: Could not consume file %s: %s\n", file_path,
            strerror(errno));
    exit(1);
  }

  fclose(f);
}

void hvm_save_program_to_file(const Hvm *hvm, const char *file_path) {
  FILE *f = fopen(file_path, "wb");
  if (f == NULL) {
    fprintf(stderr, "ERROR: Could not open file `%s`: %s\n", file_path,
            strerror(errno));
    exit(1);
  }

  fwrite(hvm->program, sizeof(hvm->program[0]), hvm->program_size, f);

  if (ferror(f)) {
    fprintf(stderr, "ERROR: Could not write to file `%s`: %s\n", file_path,
            strerror(errno));
    exit(1);
  }

  fclose(f);
}

String_View cstr_as_sv(const char *cstr) {
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

int sv_eq(String_View a, String_View b) {
  if (a.count != b.count) {
    return 0;
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

Inst_Addr basm_find_label_addr(const Basm *basm, String_View name) {
  for (size_t i = 0; i < basm->labels_size; ++i) {
    if (sv_eq(basm->labels[i].name, name)) {
      return basm->labels[i].addr;
    }
  }

  fprintf(stderr, "ERROR: label `%.*s` does not exist\n", (int)name.count,
          name.data);
  exit(1);
}

void basm_push_label(Basm *basm, String_View name, Inst_Addr addr) {
  assert(basm->labels_size < LABEL_CAPACITY);
  basm->labels[basm->labels_size++] = (Label){.name = name, .addr = addr};
}

void basm_push_deferred_operand(Basm *basm, Inst_Addr addr, String_View label) {
  assert(basm->deferred_operands_size < DEFERRED_OPERANDS_CAPACITY);
  basm->deferred_operands[basm->deferred_operands_size++] =
      (Deferred_Operand){.addr = addr, .label = label};
}

Word number_literal_as_word(String_View sv) {
  assert(sv.count < NUMBER_LITERAL_CAPACITY);
  char cstr[NUMBER_LITERAL_CAPACITY + 1];
  char *endptr = 0;

  memcpy(cstr, sv.data, sv.count);
  cstr[sv.count] = '\0';

  Word result = {0};

  result.as_u64 = strtoull(cstr, &endptr, 10);
  if ((size_t)(endptr - cstr) != sv.count) {
    result.as_f64 = strtod(cstr, &endptr);
    if ((size_t)(endptr - cstr) != sv.count) {
      fprintf(stderr, "ERROR: `%s` is not a number literal\n", cstr);
      exit(1);
    }
  }

  return result;
}

void hvm_translate_source(String_View source, Hvm *hvm, Basm *basm) {
  hvm->program_size = 0;

  // First pass
  while (source.count > 0) {
    assert(hvm->program_size < HVM_PROGRAM_CAPACITY);
    String_View line = sv_trim(sv_chop_by_delim(&source, '\n'));
    if (line.count > 0 && *line.data != '#') {
      String_View token = sv_chop_by_delim(&line, ' ');

      if (token.count > 0 && token.data[token.count - 1] == ':') {
        String_View label = {.count = token.count - 1, .data = token.data};

        basm_push_label(basm, label, hvm->program_size);

        token = sv_trim(sv_chop_by_delim(&line, ' '));
      }

      if (token.count > 0) {
        String_View operand = sv_trim(sv_chop_by_delim(&line, '#'));

        if (sv_eq(token, cstr_as_sv(inst_name(INST_NOP)))) {
          hvm->program[hvm->program_size++] = (Inst){
              .type = INST_NOP,
          };
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_PUSH)))) {
          hvm->program[hvm->program_size++] = (Inst){
              .type = INST_PUSH,
              .operand = number_literal_as_word(operand),
          };
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_DUP)))) {
          hvm->program[hvm->program_size++] = (Inst){
              .type = INST_DUP, .operand = {.as_i64 = sv_to_int(operand)}};
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_PLUSI)))) {
          hvm->program[hvm->program_size++] = (Inst){.type = INST_PLUSI};
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_MINUSI)))) {
          hvm->program[hvm->program_size++] = (Inst){.type = INST_MINUSI};
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_DIVI)))) {
          hvm->program[hvm->program_size++] = (Inst){.type = INST_DIVI};
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_MULTI)))) {
          hvm->program[hvm->program_size++] = (Inst){.type = INST_MULTI};
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_JMP)))) {
          if (operand.count > 0 && isdigit(*operand.data)) {
            hvm->program[hvm->program_size++] = (Inst){
                .type = INST_JMP,
                .operand = {.as_i64 = sv_to_int(operand)},
            };
          } else {
            basm_push_deferred_operand(basm, hvm->program_size, operand);

            hvm->program[hvm->program_size++] = (Inst){.type = INST_JMP};
          }
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_JMP_IF)))) {
          if (operand.count > 0 && isdigit(*operand.data)) {
            hvm->program[hvm->program_size++] = (Inst){
                .type = INST_JMP_IF,
                .operand = {.as_i64 = sv_to_int(operand)},
            };
          } else {
            basm_push_deferred_operand(basm, hvm->program_size, operand);

            hvm->program[hvm->program_size++] = (Inst){
                .type = INST_JMP_IF,
            };
          }
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_CALL)))) {
          if (operand.count > 0 && isdigit(*operand.data)) {
            hvm->program[hvm->program_size++] = (Inst){
                .type = INST_CALL,
                .operand = {.as_i64 = sv_to_int(operand)},
            };
          } else {
            basm_push_deferred_operand(basm, hvm->program_size, operand);

            hvm->program[hvm->program_size++] = (Inst){
                .type = INST_CALL,
            };
          }
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_HALT)))) {
          hvm->program[hvm->program_size++] = (Inst){.type = INST_HALT};
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_PLUSF)))) {
          hvm->program[hvm->program_size++] = (Inst){.type = INST_PLUSF};
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_MINUSF)))) {
          hvm->program[hvm->program_size++] = (Inst){.type = INST_MINUSF};
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_DIVF)))) {
          hvm->program[hvm->program_size++] = (Inst){.type = INST_DIVF};
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_MULTF)))) {
          hvm->program[hvm->program_size++] = (Inst){.type = INST_MULTF};
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_SWAP)))) {
          hvm->program[hvm->program_size++] = (Inst){
              .type = INST_SWAP,
              .operand = {.as_i64 = sv_to_int(operand)},
          };
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_EQ)))) {
          hvm->program[hvm->program_size++] = (Inst){
              .type = INST_EQ,
          };
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_GEF)))) {
          hvm->program[hvm->program_size++] = (Inst){
              .type = INST_GEF,
          };
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_NOT)))) {
          hvm->program[hvm->program_size++] = (Inst){
              .type = INST_NOT,
          };
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_DROP)))) {
          hvm->program[hvm->program_size++] = (Inst){
              .type = INST_DROP,
          };
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_PRINT_DEBUG)))) {
          hvm->program[hvm->program_size++] = (Inst){
              .type = INST_PRINT_DEBUG,
          };
        } else if (sv_eq(token, cstr_as_sv(inst_name(INST_RET)))) {
          hvm->program[hvm->program_size++] = (Inst){
              .type = INST_RET,
          };
        } else {
          fprintf(stderr, "ERROR: unknown instruction `%.*s`\n",
                  (int)token.count, token.data);
          exit(1);
        }
      }
    }
  }

  // Second pass
  for (size_t i = 0; i < basm->deferred_operands_size; ++i) {
    Inst_Addr addr =
        basm_find_label_addr(basm, basm->deferred_operands[i].label);
    hvm->program[basm->deferred_operands[i].addr].operand.as_u64 = addr;
  }
}

String_View sv_slurp_file(const char *file_path) {
  FILE *f = fopen(file_path, "r");
  if (f == NULL) {
    fprintf(stderr, "ERROR: Could not read file `%s`: %s\n", file_path,
            strerror(errno));
    exit(1);
  }

  if (fseek(f, 0, SEEK_END) < 0) {
    fprintf(stderr, "ERROR: Could not read file `%s`: %s\n", file_path,
            strerror(errno));
    exit(1);
  }

  long m = ftell(f);
  if (m < 0) {
    fprintf(stderr, "ERROR: Could not read file `%s`: %s\n", file_path,
            strerror(errno));
    exit(1);
  }

  char *buffer = malloc(m);
  if (buffer == NULL) {
    fprintf(stderr, "ERROR: Could not allocate memory for file: %s\n",
            strerror(errno));
    exit(1);
  }

  if (fseek(f, 0, SEEK_SET) < 0) {
    fprintf(stderr, "ERROR: Could not read file `%s`: %s\n", file_path,
            strerror(errno));
    exit(1);
  }

  size_t n = fread(buffer, 1, m, f);
  if (ferror(f)) {
    fprintf(stderr, "ERROR: Could not read file `%s`: %s\n", file_path,
            strerror(errno));
    exit(1);
  }

  fclose(f);

  return (String_View){
      .count = n,
      .data = buffer,
  };
}

#endif // HVM_IMPLEMENTATION
