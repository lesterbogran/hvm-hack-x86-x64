#include <stdlib.h>
#define HVM_IMPLEMENTATION
#include "./hvm.h"

Hvm hvm = {0};

static char *shift(int *argc, char ***argv) {
  assert(*argc > 0);
  char *result = **argv;
  *argv += 1;
  *argc -= 1;
  return result;
}

static void usage(FILE *stream, const char *program) {
  fprintf(stream, "Usage: %s -i <input.har> [-l <limit>] [-h] [-d]\n", program);
}

static Err hvm_alloc(Hvm *hvm) {
  if (hvm->stack_size < 1) {
    return ERR_STACK_UNDERFLOW;
  }

  hvm->stack[hvm->stack_size - 1].as_ptr =
      malloc(hvm->stack[hvm->stack_size - 1].as_u64);
  return ERR_OK;
}

static Err hvm_free(Hvm *hvm) {
  if (hvm->stack_size < 1) {
    return ERR_STACK_UNDERFLOW;
  }

  free(hvm->stack[hvm->stack_size - 1].as_ptr);
  hvm->stack_size -= 1;
  return ERR_OK;
}

static Err hvm_print_f64(Hvm *hvm) {
  if (hvm->stack_size < 1) {
    return ERR_STACK_UNDERFLOW;
  }

  printf("%lf\n", hvm->stack[hvm->stack_size - 1].as_f64);
  hvm->stack_size -= 1;
  return ERR_OK;
}

static Err hvm_print_i64(Hvm *hvm) {
  if (hvm->stack_size < 1) {
    return ERR_STACK_UNDERFLOW;
  }

  printf("%" PRId64 "\n", hvm->stack[hvm->stack_size - 1].as_i64);
  hvm->stack_size -= 1;
  return ERR_OK;
}

static Err hvm_print_u64(Hvm *hvm) {
  if (hvm->stack_size < 1) {
    return ERR_STACK_UNDERFLOW;
  }

  printf("%" PRIu64 "\n", hvm->stack[hvm->stack_size - 1].as_u64);
  hvm->stack_size -= 1;
  return ERR_OK;
}

static Err hvm_print_ptr(Hvm *hvm) {
  if (hvm->stack_size < 1) {
    return ERR_STACK_UNDERFLOW;
  }

  printf("%p\n", hvm->stack[hvm->stack_size - 1].as_ptr);
  hvm->stack_size -= 1;
  return ERR_OK;
}

static Err hvm_dump_memory(Hvm *hvm) {
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

static Err hvm_write(Hvm *hvm) {
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

// TODO(#17): implement gdb-style (but better of course) debugger for hvm
// TODO(#18): rot13 example that read/write data from/to the hvm memory

int main(int argc, char **argv) {
  const char *program = shift(&argc, &argv);
  const char *input_file_path = NULL;
  int limit = -1;
  int debug = 0;

  while (argc > 0) {
    const char *flag = shift(&argc, &argv);

    if (strcmp(flag, "-i") == 0) {
      if (argc == 0) {
        usage(stderr, program);
        fprintf(stderr, "ERROR: No argument is provided for flag `%s`\n", flag);
        exit(1);
      }

      input_file_path = shift(&argc, &argv);
    } else if (strcmp(flag, "-l") == 0) {
      if (argc == 0) {
        usage(stderr, program);
        fprintf(stderr, "ERROR: No argument is provided for flag `%s`\n", flag);
        exit(1);
      }

      limit = atoi(shift(&argc, &argv));
    } else if (strcmp(flag, "-h") == 0) {
      usage(stdout, program);
      exit(0);
    } else if (strcmp(flag, "-d") == 0) {
      debug = 1;
    } else {
      usage(stderr, program);
      fprintf(stderr, "ERROR: Unknown flag `%s`\n", flag);
      exit(1);
    }
  }

  if (input_file_path == NULL) {
    usage(stderr, program);
    fprintf(stderr, "ERROR: input was not provided\n");
    exit(1);
  }

  hvm_load_program_from_file(&hvm, input_file_path);
  // TODO(#3): some sort of mechanism to load native functions from DLLs
  hvm_push_native(&hvm, hvm_alloc);       // 0
  hvm_push_native(&hvm, hvm_free);        // 1
  hvm_push_native(&hvm, hvm_print_f64);   // 2
  hvm_push_native(&hvm, hvm_print_i64);   // 3
  hvm_push_native(&hvm, hvm_print_u64);   // 4
  hvm_push_native(&hvm, hvm_print_ptr);   // 5
  hvm_push_native(&hvm, hvm_dump_memory); // 6
  hvm_push_native(&hvm, hvm_write);       // 7

  if (!debug) {
    Err err = hvm_execute_program(&hvm, limit);

    if (err != ERR_OK) {
      fprintf(stderr, "ERROR: %s\n", err_as_cstr(err));
      return 1;
    }
  } else {
    while (limit != 0 && !hvm.halt) {
      hvm_dump_stack(stdout, &hvm);
      printf("Instruction: %s %" PRIu64 "\n",
             inst_name(hvm.program[hvm.ip].type),
             hvm.program[hvm.ip].operand.as_u64);
      getchar();

      Err err = hvm_execute_inst(&hvm);
      if (err != ERR_OK) {
        fprintf(stderr, "ERROR: %s\n", err_as_cstr(err));
        return 1;
      }
      if (limit > 0) {
        --limit;
      }
    }
  }

  return 0;
}
