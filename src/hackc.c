#define HVM_IMPLEMENTATION
#include "./hvm.h"

Hvm hvm = {0};

int main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "Usage: ./hackc <input.hack> <output.har>\n");
    fprintf(stderr, "ERROR: expected input and output\n");
    exit(1);
  }

  const char *input_file_path = argv[1];
  const char *output_file_path = argv[2];

  String_View source = sv_slurp_file(input_file_path);

  hvm.program_size =
      hvm_translate_source(source, hvm.program, HVM_PROGRAM_CAPACITY);

  hvm_save_program_to_file(hvm.program, hvm.program_size, output_file_path);

  return 0;
}
