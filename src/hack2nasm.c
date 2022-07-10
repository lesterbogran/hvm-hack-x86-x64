#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define HVM_IMPLEMENTATION
#include "hvm.h"

static void usage(FILE *stream) {
  fprintf(stream, "Usage: ./hack2nasm <input.hack>\n");
}

Hack hack = {0};

static void gen_print_i64(FILE *stream) {
  fprintf(stream, "print_i64:\n");
  fprintf(stream, ";; extracting input from the HVM's stack\n");
  fprintf(stream, "mov rsi, [stack_top]\n");
  fprintf(stream, "sub rsi, HVM_WORD_SIZE\n");
  fprintf(stream, "mov rax, [rsi]\n");
  fprintf(stream, "mov [stack_top], rsi\n");
  fprintf(stream, ";; rax contains the value we need to print\n");
  fprintf(stream, ";; rdi is the counter of chars\n");
  fprintf(stream, "mov rdi, 0\n");
  fprintf(stream, ";; adding the new line\n");
  fprintf(stream, "dec rsp\n");
  fprintf(stream, "inc rdi\n");
  fprintf(stream, "mov BYTE [rsp], 10\n");
  fprintf(stream, ".loop:\n");
  fprintf(stream, "xor rdx, rdx\n");
  fprintf(stream, "mov rbx, 10\n");
  fprintf(stream, "div rbx\n");
  fprintf(stream, "add rdx, '0'\n");
  fprintf(stream, "dec rsp\n");
  fprintf(stream, "inc rdi\n");
  fprintf(stream, "mov [rsp], dl\n");
  fprintf(stream, "cmp rax, 0\n");
  fprintf(stream, "jne .loop\n");
  fprintf(stream, ";; rsp - points at the beginning of the buf\n");
  fprintf(stream, ";; rdi - contains the size of the buf\n");
  fprintf(stream, ";; printing the buffer\n");
  fprintf(stream, "mov rbx, rdi\n");
  fprintf(stream, ";; write(STDOUT, buf, buf_size)\n");
  fprintf(stream, "mov rax, SYS_WRITE\n");
  fprintf(stream, "mov rdi, STDOUT\n");
  fprintf(stream, "mov rsi, rsp\n");
  fprintf(stream, "mov rdx, rbx\n");
  fprintf(stream, "syscall\n");
  fprintf(stream, "add rsp, rbx\n");
  fprintf(stream, "ret\n");
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    usage(stderr);
    fprintf(stderr, "ERROR: no input provided.\n");
    exit(1);
  }

  hack_translate_source(&hack, sv_from_cstr(argv[1]));

  printf("BITS 64\n");
  printf("%%define HVM_STACK_CAPACITY %d\n", HVM_STACK_CAPACITY);
  printf("%%define HVM_WORD_SIZE %d\n", HVM_WORD_SIZE);
  printf("%%define SYS_EXIT 60\n");
  printf("%%define SYS_WRITE 1\n");
  printf("%%define STDOUT 1\n");
  printf("segment .text\n");
  printf("global _start\n");
  gen_print_i64(stdout);
  printf("_start:\n");

  for (size_t i = 0; i < hack.program_size; ++i) {
    Inst inst = hack.program[i];

    switch (inst.type) {
    case INST_NOP:
      assert(false && "nop is not implemented yet");
    case INST_PUSH:
      printf(";; push %" PRIu64 "\n", inst.operand.as_u64);
      printf("mov rsi, [stack_top]\n");
      printf("mov QWORD [rsi], %" PRIu64 "\n", inst.operand.as_u64);
      printf("add QWORD [stack_top], HVM_WORD_SIZE\n");
      break;
    case INST_DROP:
      assert(false && "drop is not implemented yet");
    case INST_DUP:
      assert(false && "dup is not implemented yet");
    case INST_SWAP:
      assert(false && "swap is not implemented yet");
    case INST_PLUSI:
      printf(";; plusi\n");
      printf("mov rsi, [stack_top]\n");
      printf("sub rsi, HVM_WORD_SIZE\n");
      printf("mov rbx, [rsi]\n");
      printf("sub rsi, HVM_WORD_SIZE\n");
      printf("mov rax, [rsi]\n");
      printf("add rax, rbx\n");
      printf("mov [rsi], rax\n");
      printf("add rsi, HVM_WORD_SIZE\n");
      printf("mov [stack_top], rsi\n");
      break;
    case INST_MINUSI:
      assert(false && "minusi is not implemented yet");
    case INST_MULTI:
      assert(false && "multi is not implemented yet");
    case INST_DIVI:
      assert(false && "divi is not implemented yet");
    case INST_MODI:
      assert(false && "modi is not implemented yet");
    case INST_PLUSF:
      assert(false && "plusf is not implemented yet");
    case INST_MINUSF:
      assert(false && "minusf is not implemented yet");
    case INST_MULTF:
      assert(false && "multf is not implemented yet");
    case INST_DIVF:
      assert(false && "divf is not implemented yet");
    case INST_JMP:
      assert(false && "jmp is not implemented yet");
    case INST_JMP_IF:
      assert(false && "jmp_if is not implemented yet");
    case INST_RET:
      assert(false && "ret is not implemented yet");
    case INST_CALL:
      assert(false && "call is not implemented yet");
    case INST_NATIVE:
      if (inst.operand.as_u64 == 3) {
        printf(";; native print_i64\n");
        printf("call print_i64\n");
      } else {
        assert(false && "unsupported native function");
      }
      break;
    case INST_HALT:
      printf(";; halt\n");
      printf("mov rax, SYS_EXIT\n");
      printf("mov rdi, 0\n");
      printf("syscall\n");
      break;
    case INST_NOT:
      assert(false && "not is not implemented yet");
    case INST_EQI:
      assert(false && "eqi is not implemented yet");
    case INST_GEI:
      assert(false && "gei is not implemented yet");
    case INST_GTI:
      assert(false && "gti is not implemented yet");
    case INST_LEI:
      assert(false && "lei is not implemented yet");
    case INST_LTI:
      assert(false && "lti is not implemented yet");
    case INST_NEI:
      assert(false && "nei is not implemented yet");
    case INST_EQF:
      assert(false && "eqf is not implemented yet");
    case INST_GEF:
      assert(false && "gef is not implemented yet");
    case INST_GTF:
      assert(false && "gtf is not implemented yet");
    case INST_LEF:
      assert(false && "lef is not implemented yet");
    case INST_LTF:
      assert(false && "ltf is not implemented yet");
    case INST_NEF:
      assert(false && "nef is not implemented yet");
    case INST_ANDB:
      assert(false && "andb is not implemented yet");
    case INST_ORB:
      assert(false && "orb is not implemented yet");
    case INST_XOR:
      assert(false && "xor is not implemented yet");
    case INST_SHR:
      assert(false && "shr is not implemented yet");
    case INST_SHL:
      assert(false && "shl is not implemented yet");
    case INST_NOTB:
      assert(false && "notb is not implemented yet");
    case INST_READ8:
      assert(false && "read8 is not implemented yet");
    case INST_READ16:
      assert(false && "read16 is not implemented yet");
    case INST_READ32:
      assert(false && "read32 is not implemented yet");
    case INST_READ64:
      assert(false && "read64 is not implemented yet");
    case INST_WRITE8:
      assert(false && "write8 is not implemented yet");
    case INST_WRITE16:
      assert(false && "write16 is not implemented yet");
    case INST_WRITE32:
      assert(false && "write32 is not implemented yet");
    case INST_WRITE64:
      assert(false && "write64 is not implemented yet");
    case INST_I2F:
      assert(false && "i2f is not implemented yet");
    case INST_U2F:
      assert(false && "u2f is not implemented yet");
    case INST_F2I:
      assert(false && "f2i is not implemented yet");
    case INST_F2U:
      assert(false && "f2u is not implemented yet");
    case NUMBER_OF_INSTS:
    default:
      assert(false && "unknown instruction");
    }
  }

  printf("ret\n");
  printf("segment .data\n");
  printf("stack_top: dq stack\n");
  printf("segment .bss\n");
  printf("stack: resq HVM_STACK_CAPACITY\n");

  return 0;
}
