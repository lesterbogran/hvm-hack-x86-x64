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
  hvm_push_native(&hvm, hvm_alloc);
  hvm_push_native(&hvm, hvm_free);

  if (!debug) {
    Err err = hvm_execute_program(&hvm, limit);
    hvm_dump_stack(stdout, &hvm);

    if (err != ERR_OK) {
      fprintf(stderr, "ERROR: %s\n", err_as_cstr(err));
      return 1;
    }
  } else {
    while (limit != 0 && !hvm.halt) {
      hvm_dump_stack(stdout, &hvm);
      printf("%s %" PRIu64 "\n", inst_name(hvm.program[hvm.ip].type),
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
