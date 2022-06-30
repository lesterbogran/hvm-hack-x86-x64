#define HVM_IMPLEMENTATION
#include "./hvm.h"

Hvm hvm = {0};

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: ./debasm <input.har>\n");
    fprintf(stderr, "ERROR: no input is provided\n");
    exit(1);
  }

  const char *input_file_path = argv[1];

  hvm_load_program_from_file(&hvm, input_file_path);

  for (Word i = 0; i < hvm.program_size; ++i) {
    switch (hvm.program[i].type) {
    case INST_NOP:
      printf("nop\n");
      break;
    case INST_PUSH:
      printf("push %ld\n", hvm.program[i].operand);
      break;
    case INST_DUP:
      printf("dup %ld\n", hvm.program[i].operand);
      break;
    case INST_PLUS:
      printf("plus\n");
      break;
    case INST_MINUS:
      printf("minus\n");
      break;
    case INST_MULT:
      printf("mult\n");
      break;
    case INST_DIV:
      printf("div\n");
      break;
    case INST_JMP:
      printf("jmp %ld\n", hvm.program[i].operand);
      break;
    case INST_JMP_IF:
      printf("jmp_if %ld\n", hvm.program[i].operand);
      break;
    case INST_EQ:
      printf("eq\n");
      break;
    case INST_HALT:
      printf("halt\n");
      break;
    case INST_PRINT_DEBUG:
      printf("print_debug\n");
      break;
    }
  }

  return 0;
}
