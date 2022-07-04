#include <assert.h>
#include <fcntl.h>

#if defined(__FreeBSD__) || defined(__APPLE__) || defined(__NetBSD__) ||       \
    defined(__OpenBSD__) || defined(__DragonFly__)
#include <limits.h>
#else
/* TODO(#26): find a better way to get PATH_MAX on unportable OSes
 *   Windows? -> MAX_PATH is obsolete
 *   Linux? -> PATH_MAX is not guaranteed to be available.
 *             This already causes CI build failures
 * NOTE: This issue also applies to hackc.c
 */
#define PATH_MAX 4096
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "hdb.h"

#define HVM_IMPLEMENTATION
#include "hvm.h"

static void usage(void) { fprintf(stderr, "Usage: hdb <input.har>\n"); }

Hdb_Err hdb_state_init(Hdb_State *state, const char *executable) {
  assert(state);
  assert(executable);

  state->cood_file_name = sv_from_cstr(executable);
  hvm_load_program_from_file(&state->hvm, executable);

  char buf[PATH_MAX];
  memcpy(buf, executable, strlen(executable));
  memcpy(buf + strlen(executable), ".sym", 5);

  if (access(buf, R_OK) == 0) {
    fprintf(stdout, "INFO: Loading debug symbols...\n");
    return hdb_load_symtab(state, buf);
  } else {
    return HDB_OK;
  }
}

Hdb_Err hdb_mmap_file(const char *path, String_View *out) {
  assert(path);
  assert(out);

  int fd;

  if ((fd = open(path, O_RDONLY)) < 0) {
    return HDB_FAIL;
  }

  struct stat stat_buf;
  if (fstat(fd, &stat_buf) < 0) {
    return HDB_FAIL;
  }

  char *content =
      mmap(NULL, (size_t)stat_buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (content == MAP_FAILED) {
    return HDB_FAIL;
  }

  out->data = content;
  out->count = (size_t)stat_buf.st_size;

  close(fd);

  return HDB_OK;
}

Hdb_Err hdb_find_addr_of_label(Hdb_State *state, const char *name,
                               Inst_Addr *out) {
  String_View _name = sv_trim_right(sv_from_cstr(name));
  for (Inst_Addr i = 0; i < HVM_PROGRAM_CAPACITY; ++i) {
    if (state->labels[i].data && sv_eq(state->labels[i], _name)) {
      *out = i;
      return HDB_OK;
    }
  }

  return HDB_FAIL;
}

Hdb_Err hdb_load_symtab(Hdb_State *state, const char *symtab_file) {
  String_View symtab;
  if (hdb_mmap_file(symtab_file, &symtab) == HDB_FAIL) {
    return HDB_FAIL;
  }

  while (symtab.count > 0) {
    symtab = sv_trim_left(symtab);
    String_View raw_addr = sv_chop_by_delim(&symtab, '\t');
    symtab = sv_trim_left(symtab);
    String_View label_name = sv_chop_by_delim(&symtab, '\n');
    Inst_Addr addr = (Inst_Addr)sv_to_int(raw_addr);

    /*
     * Huh? you ask? Yes, if we have a label, whose size is bigger
     * than the program size, which is to say, that it is a
     * preprocessor label, then we don't wanna overrun our label
     * storage buffer.
     */
    if (addr < HVM_PROGRAM_CAPACITY) {
      state->labels[addr] = label_name;
    }
  }

  return HDB_OK;
}

void hdb_print_instr(FILE *f, Inst *i) {
  fprintf(f, "%s ", inst_name(i->type));
  if (inst_has_operand(i->type)) {
    fprintf(f, "%" PRIu64, i->operand.as_i64);
  }
}

void hdb_add_breakpoint(Hdb_State *state, Inst_Addr addr) {
  if (addr > state->hvm.program_size) {
    fprintf(stderr, "ERROR: Symbol out of program\n");
    return;
  }

  if (addr > HVM_PROGRAM_CAPACITY) {
    fprintf(stderr, "ERROR: Symbol out of memory\n");
    return;
  }

  if (state->breakpoints[addr].is_enabled) {
    fprintf(stderr, "ERROR: Breakpoint already set\n");
    return;
  }

  state->breakpoints[addr].is_enabled = 1;
}

void hdb_delete_breakpoint(Hdb_State *state, Inst_Addr addr) {
  if (addr > state->hvm.program_size) {
    fprintf(stderr, "ERROR: Symbol out of program\n");
    return;
  }

  if (addr > HVM_PROGRAM_CAPACITY) {
    fprintf(stderr, "ERROR: Symbol out of memory\n");
    return;
  }

  if (!state->breakpoints[addr].is_enabled) {
    fprintf(stderr, "ERROR: No such breakpoint\n");
    return;
  }

  state->breakpoints[addr].is_enabled = 0;
}

Hdb_Err hdb_continue(Hdb_State *state) {
  if (state->hvm.halt) {
    fprintf(stderr, "ERROR: Program is not being run\n");
    return HDB_OK;
  }

  do {
    Hdb_Breakpoint *bp = &state->breakpoints[state->hvm.ip];
    if (!bp->is_broken && bp->is_enabled) {
      fprintf(stdout, "Hit breakpoint at %" PRIu64, state->hvm.ip);
      if (state->labels[state->hvm.ip].data) {
        fprintf(stdout, " label '%.*s'",
                (int)state->labels[state->hvm.ip].count,
                state->labels[state->hvm.ip].data);
      }

      fprintf(stdout, "\n");
      bp->is_broken = 1;

      return HDB_OK;
    }

    bp->is_broken = 0;

    Err err = hvm_execute_inst(&state->hvm);
    if (err) {
      return hdb_fault(state, err);
    }
  } while (!state->hvm.halt);

  printf("Program halted.\n");

  return HDB_OK;
}

Hdb_Err hdb_fault(Hdb_State *state, Err err) {
  fprintf(stderr, "%s at %" PRIu64 " (INSTR: ", err_as_cstr(err),
          state->hvm.ip);
  hdb_print_instr(stderr, &state->hvm.program[state->hvm.ip]);
  fprintf(stderr, ")\n");
  state->hvm.halt = 1;
  return HDB_OK;
}

Hdb_Err hdb_step_instr(Hdb_State *state) {
  if (state->hvm.halt) {
    fprintf(stderr, "ERROR: Program is not being run\n");
    return HDB_OK;
  }

  Err err = hvm_execute_inst(&state->hvm);
  if (!err) {
    return HDB_OK;
  } else {
    return hdb_fault(state, err);
  }
}

Hdb_Err hdb_parse_label_or_addr(Hdb_State *st, const char *in, Inst_Addr *out) {
  char *endptr = NULL;
  size_t len = strlen(in);

  *out = strtoull(in, &endptr, 10);
  if (endptr != in + len) {
    if (hdb_find_addr_of_label(st, in, out) == HDB_FAIL) {
      return HDB_FAIL;
    }
  }

  return HDB_OK;
}

/*
 * TODO(#27): support for native function in the debugger
 * TODO: there is no way to examine the memory in hdb
 * TODO: using String_View for parsing in hdb
 */
int main(int argc, char **argv) {
  if (argc < 2) {
    usage();
    return EXIT_FAILURE;
  }

  /*
   * Create the HDB state and initialize it with the file names
   */

  Hdb_State state = {0};
  state.hvm.halt = 1;

  printf("HDB - The HVM debugger.\n"
         "Type 'h' and enter for a quick help\n");
  if (hdb_state_init(&state, argv[1]) == HDB_FAIL) {
    fprintf(stderr, "FATAL: Unable to initialize the debugger: %s\n",
            strerror(errno));
  }

  while (1) {
    printf("(hdb) ");
    char input_buf[32];
    fgets(input_buf, 32, stdin);

    switch (*input_buf) {
    /*
     * Next instruction
     */
    case 'n': {
      Hdb_Err err = hdb_step_instr(&state);
      if (err) {
        return EXIT_FAILURE;
      }

      printf("-> ");
      hdb_print_instr(stdout, &state.hvm.program[state.hvm.ip]);
      printf("\n");
    } break;

    /*
     * Print the IP
     */
    case 'i':
      printf("ip = %" PRIu64 "\n", state.hvm.ip);
      break;

    /*
     * Dump the stack
     */
    case 's':
      hvm_dump_stack(stdout, &state.hvm);
      break;

    case 'b': {
      // TODO: `b 0` in hdb results in "ERROR: Cannot parse address or
      // labels"
      char *addr = input_buf + 2;
      Inst_Addr break_addr;

      if (hdb_parse_label_or_addr(&state, addr, &break_addr) == HDB_FAIL) {
        fprintf(stderr, "ERROR: Cannot parse address or labels\n");
        continue;
      }

      hdb_add_breakpoint(&state, break_addr);
      fprintf(stdout, "INFO: Breakpoint set at %" PRIu64 "\n", break_addr);
    } break;

    case 'd': {
      char *addr = input_buf + 2;
      Inst_Addr break_addr;

      if (hdb_parse_label_or_addr(&state, addr, &break_addr) == HDB_FAIL) {
        fprintf(stderr, "ERROR: Cannot parse address or labels\n");
        continue;
      }

      hdb_delete_breakpoint(&state, break_addr);
      fprintf(stdout, "INFO: Deleted breakpoint at %" PRIu64 "\n", break_addr);
    } break;

    case 'r':
      if (!state.hvm.halt) {
        fprintf(stderr, "ERROR: Program is already running\n");
        /* TODO: Reset hvm and restart program */
      }

      state.hvm.halt = 0;
      /* fall through */

    case 'c':
      if (hdb_continue(&state)) {
        return EXIT_FAILURE;
      }
      break;

    case EOF:

    case 'q':
      return EXIT_SUCCESS;

    case 'h':
      printf("r - run program\n"
             "n - next instruction\n"
             "c - continue program execution\n"
             "s - stack dump\n"
             "i - instruction pointer\n"
             "b - set breakpoint at address or label\n"
             "d - destroy breakpoint at address or label\n"
             "q - quit\n");
      break;

    default:
      fprintf(stderr, "?\n");
      break;
    }
  }

  return EXIT_SUCCESS;
}
