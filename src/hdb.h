#ifndef HDB_H
#define HDB_H

#include "hvm.h"

typedef enum { HDB_OK = 0, HDB_FAIL = 1, HDB_EXIT } Hdb_Err;

typedef struct Hdb_Breakpoint {
  int is_enabled;
  int id;
  int is_broken;
} Hdb_Breakpoint;

typedef struct Hdb_State {
  Hvm hvm;
  String_View cood_file_name;
  Hdb_Breakpoint breakpoints[HVM_PROGRAM_CAPACITY];
  String_View labels[HVM_PROGRAM_CAPACITY];
  Arena arena;
} Hdb_State;

Hdb_Err hdb_state_init(Hdb_State *, const char *executable);
Hdb_Err hdb_load_symtab(Hdb_State *state, String_View symtab_file);
Hdb_Err hdb_step_instr(Hdb_State *);
Hdb_Err hdb_continue(Hdb_State *);
Hdb_Err hdb_find_addr_of_label(Hdb_State *, const char *, Inst_Addr *);
Hdb_Err hdb_parse_label_or_addr(Hdb_State *, const char *, Inst_Addr *);
Hdb_Err hdb_mmap_file(const char *, String_View *);
void hdb_print_instr(FILE *, Inst *);
void hdb_add_breakpoint(Hdb_State *, Inst_Addr);
void hdb_delete_breakpoint(Hdb_State *, Inst_Addr);
Hdb_Err hdb_fault(Hdb_State *, Err);

#endif // HDB_H
