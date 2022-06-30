#define HVM_IMPLEMENTATION
#include "./hvm.h"

Hvm hvm = {0};

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: ./hack <input.har>\n");
    fprintf(stderr, "ERROR: expected input\n");
    exit(1);
  }

  hvm_load_program_from_file(&hvm, argv[1]);
  for (int i = 0; i < 69 && !hvm.halt; ++i) {
    Err err = hvm_execute_inst(&hvm);
    hvm_dump_stack(stdout, &hvm);
    if (err != ERR_OK) {
      fprintf(stderr, "ERROR: %s\n", err_as_cstr(err));
      exit(1);
    }
  }

  return 0;
}
