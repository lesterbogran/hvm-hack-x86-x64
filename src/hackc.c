#define HVM_IMPLEMENTATION
#include "./hvm.h"

Hvm hvm = {0};

char *shift(int *argc, char ***argv) {
  assert(*argc > 0);
  char *result = **argv;
  *argv += 1;
  *argc -= 1;
  return result;
}

void usage(FILE *stream, const char *program) {
  fprintf(stream, "Usage: %s <input.hack> <output.har>\n", program);
}

int main(int argc, char **argv) {
  const char *program = shift(&argc, &argv);

  if (argc == 0) {
    usage(stderr, program);
    fprintf(stderr, "ERROR: expected input\n");
    exit(1);
  }
  const char *input_file_path = shift(&argc, &argv);

  if (argc == 0) {
    usage(stderr, program);
    fprintf(stderr, "ERROR: expected output\n");
    exit(1);
  }
  const char *output_file_path = shift(&argc, &argv);

  String_View source = sv_slurp_file(input_file_path);

  hvm.program_size =
      hvm_translate_source(source, hvm.program, HVM_PROGRAM_CAPACITY);

  hvm_save_program_to_file(&hvm, output_file_path);

  return 0;
}
