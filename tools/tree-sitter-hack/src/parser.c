#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 13
#define STATE_COUNT 14
#define LARGE_STATE_COUNT 11
#define SYMBOL_COUNT 54
#define ALIAS_COUNT 0
#define TOKEN_COUNT 46
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 5
#define MAX_ALIAS_SEQUENCE_LENGTH 3
#define PRODUCTION_ID_COUNT 5

enum {
  anon_sym_PERCENTinclude = 1,
  anon_sym_PERCENTbind = 2,
  sym__label_name = 3,
  anon_sym_nop = 4,
  anon_sym_push = 5,
  anon_sym_drop = 6,
  anon_sym_dup = 7,
  anon_sym_swap = 8,
  anon_sym_plusi = 9,
  anon_sym_minusi = 10,
  anon_sym_multi = 11,
  anon_sym_divi = 12,
  anon_sym_modi = 13,
  anon_sym_plusf = 14,
  anon_sym_minusf = 15,
  anon_sym_multf = 16,
  anon_sym_divf = 17,
  anon_sym_jmp = 18,
  anon_sym_jmp_if = 19,
  anon_sym_ret = 20,
  anon_sym_call = 21,
  anon_sym_native = 22,
  anon_sym_eq = 23,
  anon_sym_halt = 24,
  anon_sym_not = 25,
  anon_sym_gei = 26,
  anon_sym_gef = 27,
  anon_sym_andb = 28,
  anon_sym_orb = 29,
  anon_sym_xor = 30,
  anon_sym_shr = 31,
  anon_sym_shl = 32,
  anon_sym_notb = 33,
  anon_sym_read8 = 34,
  anon_sym_read16 = 35,
  anon_sym_read32 = 36,
  anon_sym_read64 = 37,
  anon_sym_write8 = 38,
  anon_sym_write16 = 39,
  anon_sym_write32 = 40,
  anon_sym_write64 = 41,
  sym_identifier = 42,
  sym_string = 43,
  sym_number = 44,
  sym_comment = 45,
  sym_source_file = 46,
  sym__expression = 47,
  sym_directive = 48,
  sym__directive_name = 49,
  sym_label = 50,
  sym_operation = 51,
  sym__inst = 52,
  aux_sym_source_file_repeat1 = 53,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_PERCENTinclude] = "%include",
  [anon_sym_PERCENTbind] = "%bind",
  [sym__label_name] = "_label_name",
  [anon_sym_nop] = "nop",
  [anon_sym_push] = "push",
  [anon_sym_drop] = "drop",
  [anon_sym_dup] = "dup",
  [anon_sym_swap] = "swap",
  [anon_sym_plusi] = "plusi",
  [anon_sym_minusi] = "minusi",
  [anon_sym_multi] = "multi",
  [anon_sym_divi] = "divi",
  [anon_sym_modi] = "modi",
  [anon_sym_plusf] = "plusf",
  [anon_sym_minusf] = "minusf",
  [anon_sym_multf] = "multf",
  [anon_sym_divf] = "divf",
  [anon_sym_jmp] = "jmp",
  [anon_sym_jmp_if] = "jmp_if",
  [anon_sym_ret] = "ret",
  [anon_sym_call] = "call",
  [anon_sym_native] = "native",
  [anon_sym_eq] = "eq",
  [anon_sym_halt] = "halt",
  [anon_sym_not] = "not",
  [anon_sym_gei] = "gei",
  [anon_sym_gef] = "gef",
  [anon_sym_andb] = "andb",
  [anon_sym_orb] = "orb",
  [anon_sym_xor] = "xor",
  [anon_sym_shr] = "shr",
  [anon_sym_shl] = "shl",
  [anon_sym_notb] = "notb",
  [anon_sym_read8] = "read8",
  [anon_sym_read16] = "read16",
  [anon_sym_read32] = "read32",
  [anon_sym_read64] = "read64",
  [anon_sym_write8] = "write8",
  [anon_sym_write16] = "write16",
  [anon_sym_write32] = "write32",
  [anon_sym_write64] = "write64",
  [sym_identifier] = "identifier",
  [sym_string] = "string",
  [sym_number] = "number",
  [sym_comment] = "comment",
  [sym_source_file] = "source_file",
  [sym__expression] = "_expression",
  [sym_directive] = "directive",
  [sym__directive_name] = "_directive_name",
  [sym_label] = "label",
  [sym_operation] = "operation",
  [sym__inst] = "_inst",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_PERCENTinclude] = anon_sym_PERCENTinclude,
  [anon_sym_PERCENTbind] = anon_sym_PERCENTbind,
  [sym__label_name] = sym__label_name,
  [anon_sym_nop] = anon_sym_nop,
  [anon_sym_push] = anon_sym_push,
  [anon_sym_drop] = anon_sym_drop,
  [anon_sym_dup] = anon_sym_dup,
  [anon_sym_swap] = anon_sym_swap,
  [anon_sym_plusi] = anon_sym_plusi,
  [anon_sym_minusi] = anon_sym_minusi,
  [anon_sym_multi] = anon_sym_multi,
  [anon_sym_divi] = anon_sym_divi,
  [anon_sym_modi] = anon_sym_modi,
  [anon_sym_plusf] = anon_sym_plusf,
  [anon_sym_minusf] = anon_sym_minusf,
  [anon_sym_multf] = anon_sym_multf,
  [anon_sym_divf] = anon_sym_divf,
  [anon_sym_jmp] = anon_sym_jmp,
  [anon_sym_jmp_if] = anon_sym_jmp_if,
  [anon_sym_ret] = anon_sym_ret,
  [anon_sym_call] = anon_sym_call,
  [anon_sym_native] = anon_sym_native,
  [anon_sym_eq] = anon_sym_eq,
  [anon_sym_halt] = anon_sym_halt,
  [anon_sym_not] = anon_sym_not,
  [anon_sym_gei] = anon_sym_gei,
  [anon_sym_gef] = anon_sym_gef,
  [anon_sym_andb] = anon_sym_andb,
  [anon_sym_orb] = anon_sym_orb,
  [anon_sym_xor] = anon_sym_xor,
  [anon_sym_shr] = anon_sym_shr,
  [anon_sym_shl] = anon_sym_shl,
  [anon_sym_notb] = anon_sym_notb,
  [anon_sym_read8] = anon_sym_read8,
  [anon_sym_read16] = anon_sym_read16,
  [anon_sym_read32] = anon_sym_read32,
  [anon_sym_read64] = anon_sym_read64,
  [anon_sym_write8] = anon_sym_write8,
  [anon_sym_write16] = anon_sym_write16,
  [anon_sym_write32] = anon_sym_write32,
  [anon_sym_write64] = anon_sym_write64,
  [sym_identifier] = sym_identifier,
  [sym_string] = sym_string,
  [sym_number] = sym_number,
  [sym_comment] = sym_comment,
  [sym_source_file] = sym_source_file,
  [sym__expression] = sym__expression,
  [sym_directive] = sym_directive,
  [sym__directive_name] = sym__directive_name,
  [sym_label] = sym_label,
  [sym_operation] = sym_operation,
  [sym__inst] = sym__inst,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_PERCENTinclude] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PERCENTbind] = {
    .visible = true,
    .named = false,
  },
  [sym__label_name] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_nop] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_push] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_drop] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_dup] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_swap] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_plusi] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_minusi] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_multi] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_divi] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_modi] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_plusf] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_minusf] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_multf] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_divf] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_jmp] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_jmp_if] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ret] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_call] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_native] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_eq] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_halt] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_not] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_gei] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_gef] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_andb] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_orb] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_xor] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_shr] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_shl] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_notb] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_read8] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_read16] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_read32] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_read64] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_write8] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_write16] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_write32] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_write64] = {
    .visible = true,
    .named = false,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym__expression] = {
    .visible = false,
    .named = true,
  },
  [sym_directive] = {
    .visible = true,
    .named = true,
  },
  [sym__directive_name] = {
    .visible = false,
    .named = true,
  },
  [sym_label] = {
    .visible = true,
    .named = true,
  },
  [sym_operation] = {
    .visible = true,
    .named = true,
  },
  [sym__inst] = {
    .visible = false,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum {
  field_label = 1,
  field_name = 2,
  field_operand = 3,
  field_param = 4,
  field_value = 5,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_label] = "label",
  [field_name] = "name",
  [field_operand] = "operand",
  [field_param] = "param",
  [field_value] = "value",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 2},
  [3] = {.index = 3, .length = 1},
  [4] = {.index = 4, .length = 3},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_name, 0},
  [1] =
    {field_name, 0},
    {field_param, 1},
  [3] =
    {field_operand, 1},
  [4] =
    {field_label, 1},
    {field_name, 0},
    {field_value, 2},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(13);
      if (lookahead == '"') ADVANCE(2);
      if (lookahead == '%') ADVANCE(3);
      if (lookahead == ';') ADVANCE(126);
      if (lookahead == 'a') ADVANCE(98);
      if (lookahead == 'c') ADVANCE(63);
      if (lookahead == 'd') ADVANCE(85);
      if (lookahead == 'e') ADVANCE(107);
      if (lookahead == 'g') ADVANCE(73);
      if (lookahead == 'h') ADVANCE(65);
      if (lookahead == 'j') ADVANCE(97);
      if (lookahead == 'm') ADVANCE(88);
      if (lookahead == 'n') ADVANCE(64);
      if (lookahead == 'o') ADVANCE(108);
      if (lookahead == 'p') ADVANCE(91);
      if (lookahead == 'r') ADVANCE(74);
      if (lookahead == 's') ADVANCE(83);
      if (lookahead == 'w') ADVANCE(109);
      if (lookahead == 'x') ADVANCE(100);
      if (lookahead == '.' ||
          lookahead == '@') ADVANCE(123);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(125);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(2);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(1)
      if (lookahead == '.' ||
          ('@' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(123);
      END_STATE();
    case 2:
      if (lookahead == '"') ADVANCE(124);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(2);
      END_STATE();
    case 3:
      if (lookahead == 'b') ADVANCE(8);
      if (lookahead == 'i') ADVANCE(10);
      END_STATE();
    case 4:
      if (lookahead == 'c') ADVANCE(9);
      END_STATE();
    case 5:
      if (lookahead == 'd') ADVANCE(15);
      END_STATE();
    case 6:
      if (lookahead == 'd') ADVANCE(7);
      END_STATE();
    case 7:
      if (lookahead == 'e') ADVANCE(14);
      END_STATE();
    case 8:
      if (lookahead == 'i') ADVANCE(11);
      END_STATE();
    case 9:
      if (lookahead == 'l') ADVANCE(12);
      END_STATE();
    case 10:
      if (lookahead == 'n') ADVANCE(4);
      END_STATE();
    case 11:
      if (lookahead == 'n') ADVANCE(5);
      END_STATE();
    case 12:
      if (lookahead == 'u') ADVANCE(6);
      END_STATE();
    case 13:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 14:
      ACCEPT_TOKEN(anon_sym_PERCENTinclude);
      END_STATE();
    case 15:
      ACCEPT_TOKEN(anon_sym_PERCENTbind);
      END_STATE();
    case 16:
      ACCEPT_TOKEN(sym__label_name);
      END_STATE();
    case 17:
      ACCEPT_TOKEN(anon_sym_nop);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 18:
      ACCEPT_TOKEN(anon_sym_push);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 19:
      ACCEPT_TOKEN(anon_sym_drop);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(anon_sym_dup);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(anon_sym_swap);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 22:
      ACCEPT_TOKEN(anon_sym_plusi);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 23:
      ACCEPT_TOKEN(anon_sym_minusi);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(anon_sym_multi);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 25:
      ACCEPT_TOKEN(anon_sym_divi);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 26:
      ACCEPT_TOKEN(anon_sym_modi);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(anon_sym_plusf);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(anon_sym_minusf);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(anon_sym_multf);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_divf);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(anon_sym_jmp);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == '_') ADVANCE(87);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(anon_sym_jmp_if);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(anon_sym_ret);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(anon_sym_call);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(anon_sym_native);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(anon_sym_eq);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(anon_sym_halt);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(anon_sym_not);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'b') ADVANCE(46);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(anon_sym_gei);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(anon_sym_gef);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(anon_sym_andb);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(anon_sym_orb);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(anon_sym_xor);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(anon_sym_shr);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(anon_sym_shl);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(anon_sym_notb);
      if (lookahead == ':') ADVANCE(16);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(anon_sym_read8);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(anon_sym_read16);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(anon_sym_read32);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(anon_sym_read64);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(anon_sym_write8);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(anon_sym_write16);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(anon_sym_write32);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(anon_sym_write64);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '1') ADVANCE(61);
      if (lookahead == '3') ADVANCE(57);
      if (lookahead == '6') ADVANCE(59);
      if (lookahead == '8') ADVANCE(47);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '1') ADVANCE(62);
      if (lookahead == '3') ADVANCE(58);
      if (lookahead == '6') ADVANCE(60);
      if (lookahead == '8') ADVANCE(51);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '2') ADVANCE(49);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('@' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(123);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '2') ADVANCE(53);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('@' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(123);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '4') ADVANCE(50);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('@' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(123);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '4') ADVANCE(54);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('@' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(123);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '6') ADVANCE(48);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('@' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(123);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '6') ADVANCE(52);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('@' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(123);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'a') ADVANCE(95);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'a') ADVANCE(117);
      if (lookahead == 'o') ADVANCE(104);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'a') ADVANCE(94);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'a') ADVANCE(70);
      if (lookahead == 't') ADVANCE(33);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'a') ADVANCE(106);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'b') ADVANCE(42);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'b') ADVANCE(41);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'd') ADVANCE(55);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'd') ADVANCE(69);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'd') ADVANCE(86);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'e') ADVANCE(77);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'e') ADVANCE(66);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'e') ADVANCE(35);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'e') ADVANCE(56);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'f') ADVANCE(40);
      if (lookahead == 'i') ADVANCE(39);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'f') ADVANCE(30);
      if (lookahead == 'i') ADVANCE(25);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'f') ADVANCE(29);
      if (lookahead == 'i') ADVANCE(24);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'f') ADVANCE(27);
      if (lookahead == 'i') ADVANCE(22);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'f') ADVANCE(32);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'f') ADVANCE(28);
      if (lookahead == 'i') ADVANCE(23);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'h') ADVANCE(92);
      if (lookahead == 'w') ADVANCE(67);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'h') ADVANCE(18);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'i') ADVANCE(120);
      if (lookahead == 'r') ADVANCE(101);
      if (lookahead == 'u') ADVANCE(102);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'i') ADVANCE(26);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'i') ADVANCE(81);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'i') ADVANCE(99);
      if (lookahead == 'o') ADVANCE(72);
      if (lookahead == 'u') ADVANCE(96);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'i') ADVANCE(121);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'i') ADVANCE(115);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'l') ADVANCE(118);
      if (lookahead == 'u') ADVANCE(111);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'l') ADVANCE(45);
      if (lookahead == 'r') ADVANCE(44);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'l') ADVANCE(34);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'l') ADVANCE(114);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'l') ADVANCE(93);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'l') ADVANCE(116);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'm') ADVANCE(103);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'n') ADVANCE(71);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'n') ADVANCE(119);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'o') ADVANCE(110);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'o') ADVANCE(105);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'p') ADVANCE(20);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'p') ADVANCE(31);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'p') ADVANCE(17);
      if (lookahead == 't') ADVANCE(38);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'p') ADVANCE(19);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'p') ADVANCE(21);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'q') ADVANCE(36);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'r') ADVANCE(68);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'r') ADVANCE(90);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'r') ADVANCE(43);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 's') ADVANCE(84);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 's') ADVANCE(80);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 's') ADVANCE(82);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 't') ADVANCE(37);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 't') ADVANCE(76);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 't') ADVANCE(79);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 't') ADVANCE(89);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'u') ADVANCE(112);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'u') ADVANCE(113);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'v') ADVANCE(78);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'v') ADVANCE(75);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          lookahead == '@') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(122);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '$' ||
          lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('@' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(123);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(sym_string);
      if (lookahead == '"') ADVANCE(124);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(2);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(125);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(126);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 0},
  [3] = {.lex_state = 0},
  [4] = {.lex_state = 0},
  [5] = {.lex_state = 0},
  [6] = {.lex_state = 0},
  [7] = {.lex_state = 0},
  [8] = {.lex_state = 0},
  [9] = {.lex_state = 0},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 1},
  [12] = {.lex_state = 0},
  [13] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_PERCENTinclude] = ACTIONS(1),
    [anon_sym_PERCENTbind] = ACTIONS(1),
    [sym__label_name] = ACTIONS(1),
    [anon_sym_nop] = ACTIONS(1),
    [anon_sym_push] = ACTIONS(1),
    [anon_sym_drop] = ACTIONS(1),
    [anon_sym_dup] = ACTIONS(1),
    [anon_sym_swap] = ACTIONS(1),
    [anon_sym_plusi] = ACTIONS(1),
    [anon_sym_minusi] = ACTIONS(1),
    [anon_sym_multi] = ACTIONS(1),
    [anon_sym_divi] = ACTIONS(1),
    [anon_sym_modi] = ACTIONS(1),
    [anon_sym_plusf] = ACTIONS(1),
    [anon_sym_minusf] = ACTIONS(1),
    [anon_sym_multf] = ACTIONS(1),
    [anon_sym_divf] = ACTIONS(1),
    [anon_sym_jmp] = ACTIONS(1),
    [anon_sym_jmp_if] = ACTIONS(1),
    [anon_sym_ret] = ACTIONS(1),
    [anon_sym_call] = ACTIONS(1),
    [anon_sym_native] = ACTIONS(1),
    [anon_sym_eq] = ACTIONS(1),
    [anon_sym_halt] = ACTIONS(1),
    [anon_sym_not] = ACTIONS(1),
    [anon_sym_gei] = ACTIONS(1),
    [anon_sym_gef] = ACTIONS(1),
    [anon_sym_andb] = ACTIONS(1),
    [anon_sym_orb] = ACTIONS(1),
    [anon_sym_xor] = ACTIONS(1),
    [anon_sym_shr] = ACTIONS(1),
    [anon_sym_shl] = ACTIONS(1),
    [anon_sym_notb] = ACTIONS(1),
    [anon_sym_read8] = ACTIONS(1),
    [anon_sym_read16] = ACTIONS(1),
    [anon_sym_read32] = ACTIONS(1),
    [anon_sym_read64] = ACTIONS(1),
    [anon_sym_write8] = ACTIONS(1),
    [anon_sym_write16] = ACTIONS(1),
    [anon_sym_write32] = ACTIONS(1),
    [anon_sym_write64] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [sym_string] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
    [sym_comment] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(13),
    [sym__expression] = STATE(6),
    [sym_directive] = STATE(6),
    [sym__directive_name] = STATE(11),
    [sym_label] = STATE(6),
    [sym_operation] = STATE(6),
    [sym__inst] = STATE(4),
    [aux_sym_source_file_repeat1] = STATE(2),
    [ts_builtin_sym_end] = ACTIONS(3),
    [anon_sym_PERCENTinclude] = ACTIONS(5),
    [anon_sym_PERCENTbind] = ACTIONS(5),
    [sym__label_name] = ACTIONS(7),
    [anon_sym_nop] = ACTIONS(9),
    [anon_sym_push] = ACTIONS(9),
    [anon_sym_drop] = ACTIONS(9),
    [anon_sym_dup] = ACTIONS(9),
    [anon_sym_swap] = ACTIONS(9),
    [anon_sym_plusi] = ACTIONS(9),
    [anon_sym_minusi] = ACTIONS(9),
    [anon_sym_multi] = ACTIONS(9),
    [anon_sym_divi] = ACTIONS(9),
    [anon_sym_modi] = ACTIONS(9),
    [anon_sym_plusf] = ACTIONS(9),
    [anon_sym_minusf] = ACTIONS(9),
    [anon_sym_multf] = ACTIONS(9),
    [anon_sym_divf] = ACTIONS(9),
    [anon_sym_jmp] = ACTIONS(9),
    [anon_sym_jmp_if] = ACTIONS(9),
    [anon_sym_ret] = ACTIONS(9),
    [anon_sym_call] = ACTIONS(9),
    [anon_sym_native] = ACTIONS(9),
    [anon_sym_eq] = ACTIONS(9),
    [anon_sym_halt] = ACTIONS(9),
    [anon_sym_not] = ACTIONS(9),
    [anon_sym_gei] = ACTIONS(9),
    [anon_sym_gef] = ACTIONS(9),
    [anon_sym_andb] = ACTIONS(9),
    [anon_sym_orb] = ACTIONS(9),
    [anon_sym_xor] = ACTIONS(9),
    [anon_sym_shr] = ACTIONS(9),
    [anon_sym_shl] = ACTIONS(9),
    [anon_sym_notb] = ACTIONS(9),
    [anon_sym_read8] = ACTIONS(11),
    [anon_sym_read16] = ACTIONS(11),
    [anon_sym_read32] = ACTIONS(11),
    [anon_sym_read64] = ACTIONS(11),
    [anon_sym_write8] = ACTIONS(11),
    [anon_sym_write16] = ACTIONS(11),
    [anon_sym_write32] = ACTIONS(11),
    [anon_sym_write64] = ACTIONS(11),
    [sym_comment] = ACTIONS(13),
  },
  [2] = {
    [sym__expression] = STATE(6),
    [sym_directive] = STATE(6),
    [sym__directive_name] = STATE(11),
    [sym_label] = STATE(6),
    [sym_operation] = STATE(6),
    [sym__inst] = STATE(4),
    [aux_sym_source_file_repeat1] = STATE(3),
    [ts_builtin_sym_end] = ACTIONS(15),
    [anon_sym_PERCENTinclude] = ACTIONS(5),
    [anon_sym_PERCENTbind] = ACTIONS(5),
    [sym__label_name] = ACTIONS(7),
    [anon_sym_nop] = ACTIONS(9),
    [anon_sym_push] = ACTIONS(9),
    [anon_sym_drop] = ACTIONS(9),
    [anon_sym_dup] = ACTIONS(9),
    [anon_sym_swap] = ACTIONS(9),
    [anon_sym_plusi] = ACTIONS(9),
    [anon_sym_minusi] = ACTIONS(9),
    [anon_sym_multi] = ACTIONS(9),
    [anon_sym_divi] = ACTIONS(9),
    [anon_sym_modi] = ACTIONS(9),
    [anon_sym_plusf] = ACTIONS(9),
    [anon_sym_minusf] = ACTIONS(9),
    [anon_sym_multf] = ACTIONS(9),
    [anon_sym_divf] = ACTIONS(9),
    [anon_sym_jmp] = ACTIONS(9),
    [anon_sym_jmp_if] = ACTIONS(9),
    [anon_sym_ret] = ACTIONS(9),
    [anon_sym_call] = ACTIONS(9),
    [anon_sym_native] = ACTIONS(9),
    [anon_sym_eq] = ACTIONS(9),
    [anon_sym_halt] = ACTIONS(9),
    [anon_sym_not] = ACTIONS(9),
    [anon_sym_gei] = ACTIONS(9),
    [anon_sym_gef] = ACTIONS(9),
    [anon_sym_andb] = ACTIONS(9),
    [anon_sym_orb] = ACTIONS(9),
    [anon_sym_xor] = ACTIONS(9),
    [anon_sym_shr] = ACTIONS(9),
    [anon_sym_shl] = ACTIONS(9),
    [anon_sym_notb] = ACTIONS(9),
    [anon_sym_read8] = ACTIONS(11),
    [anon_sym_read16] = ACTIONS(11),
    [anon_sym_read32] = ACTIONS(11),
    [anon_sym_read64] = ACTIONS(11),
    [anon_sym_write8] = ACTIONS(11),
    [anon_sym_write16] = ACTIONS(11),
    [anon_sym_write32] = ACTIONS(11),
    [anon_sym_write64] = ACTIONS(11),
    [sym_comment] = ACTIONS(17),
  },
  [3] = {
    [sym__expression] = STATE(6),
    [sym_directive] = STATE(6),
    [sym__directive_name] = STATE(11),
    [sym_label] = STATE(6),
    [sym_operation] = STATE(6),
    [sym__inst] = STATE(4),
    [aux_sym_source_file_repeat1] = STATE(3),
    [ts_builtin_sym_end] = ACTIONS(19),
    [anon_sym_PERCENTinclude] = ACTIONS(21),
    [anon_sym_PERCENTbind] = ACTIONS(21),
    [sym__label_name] = ACTIONS(24),
    [anon_sym_nop] = ACTIONS(27),
    [anon_sym_push] = ACTIONS(27),
    [anon_sym_drop] = ACTIONS(27),
    [anon_sym_dup] = ACTIONS(27),
    [anon_sym_swap] = ACTIONS(27),
    [anon_sym_plusi] = ACTIONS(27),
    [anon_sym_minusi] = ACTIONS(27),
    [anon_sym_multi] = ACTIONS(27),
    [anon_sym_divi] = ACTIONS(27),
    [anon_sym_modi] = ACTIONS(27),
    [anon_sym_plusf] = ACTIONS(27),
    [anon_sym_minusf] = ACTIONS(27),
    [anon_sym_multf] = ACTIONS(27),
    [anon_sym_divf] = ACTIONS(27),
    [anon_sym_jmp] = ACTIONS(27),
    [anon_sym_jmp_if] = ACTIONS(27),
    [anon_sym_ret] = ACTIONS(27),
    [anon_sym_call] = ACTIONS(27),
    [anon_sym_native] = ACTIONS(27),
    [anon_sym_eq] = ACTIONS(27),
    [anon_sym_halt] = ACTIONS(27),
    [anon_sym_not] = ACTIONS(27),
    [anon_sym_gei] = ACTIONS(27),
    [anon_sym_gef] = ACTIONS(27),
    [anon_sym_andb] = ACTIONS(27),
    [anon_sym_orb] = ACTIONS(27),
    [anon_sym_xor] = ACTIONS(27),
    [anon_sym_shr] = ACTIONS(27),
    [anon_sym_shl] = ACTIONS(27),
    [anon_sym_notb] = ACTIONS(27),
    [anon_sym_read8] = ACTIONS(30),
    [anon_sym_read16] = ACTIONS(30),
    [anon_sym_read32] = ACTIONS(30),
    [anon_sym_read64] = ACTIONS(30),
    [anon_sym_write8] = ACTIONS(30),
    [anon_sym_write16] = ACTIONS(30),
    [anon_sym_write32] = ACTIONS(30),
    [anon_sym_write64] = ACTIONS(30),
    [sym_comment] = ACTIONS(33),
  },
  [4] = {
    [ts_builtin_sym_end] = ACTIONS(36),
    [anon_sym_PERCENTinclude] = ACTIONS(36),
    [anon_sym_PERCENTbind] = ACTIONS(36),
    [sym__label_name] = ACTIONS(36),
    [anon_sym_nop] = ACTIONS(38),
    [anon_sym_push] = ACTIONS(38),
    [anon_sym_drop] = ACTIONS(38),
    [anon_sym_dup] = ACTIONS(38),
    [anon_sym_swap] = ACTIONS(38),
    [anon_sym_plusi] = ACTIONS(38),
    [anon_sym_minusi] = ACTIONS(38),
    [anon_sym_multi] = ACTIONS(38),
    [anon_sym_divi] = ACTIONS(38),
    [anon_sym_modi] = ACTIONS(38),
    [anon_sym_plusf] = ACTIONS(38),
    [anon_sym_minusf] = ACTIONS(38),
    [anon_sym_multf] = ACTIONS(38),
    [anon_sym_divf] = ACTIONS(38),
    [anon_sym_jmp] = ACTIONS(38),
    [anon_sym_jmp_if] = ACTIONS(38),
    [anon_sym_ret] = ACTIONS(38),
    [anon_sym_call] = ACTIONS(38),
    [anon_sym_native] = ACTIONS(38),
    [anon_sym_eq] = ACTIONS(38),
    [anon_sym_halt] = ACTIONS(38),
    [anon_sym_not] = ACTIONS(38),
    [anon_sym_gei] = ACTIONS(38),
    [anon_sym_gef] = ACTIONS(38),
    [anon_sym_andb] = ACTIONS(38),
    [anon_sym_orb] = ACTIONS(38),
    [anon_sym_xor] = ACTIONS(38),
    [anon_sym_shr] = ACTIONS(38),
    [anon_sym_shl] = ACTIONS(38),
    [anon_sym_notb] = ACTIONS(38),
    [anon_sym_read8] = ACTIONS(36),
    [anon_sym_read16] = ACTIONS(36),
    [anon_sym_read32] = ACTIONS(36),
    [anon_sym_read64] = ACTIONS(36),
    [anon_sym_write8] = ACTIONS(36),
    [anon_sym_write16] = ACTIONS(36),
    [anon_sym_write32] = ACTIONS(36),
    [anon_sym_write64] = ACTIONS(36),
    [sym_identifier] = ACTIONS(40),
    [sym_number] = ACTIONS(42),
    [sym_comment] = ACTIONS(36),
  },
  [5] = {
    [ts_builtin_sym_end] = ACTIONS(44),
    [anon_sym_PERCENTinclude] = ACTIONS(44),
    [anon_sym_PERCENTbind] = ACTIONS(44),
    [sym__label_name] = ACTIONS(44),
    [anon_sym_nop] = ACTIONS(46),
    [anon_sym_push] = ACTIONS(46),
    [anon_sym_drop] = ACTIONS(46),
    [anon_sym_dup] = ACTIONS(46),
    [anon_sym_swap] = ACTIONS(46),
    [anon_sym_plusi] = ACTIONS(46),
    [anon_sym_minusi] = ACTIONS(46),
    [anon_sym_multi] = ACTIONS(46),
    [anon_sym_divi] = ACTIONS(46),
    [anon_sym_modi] = ACTIONS(46),
    [anon_sym_plusf] = ACTIONS(46),
    [anon_sym_minusf] = ACTIONS(46),
    [anon_sym_multf] = ACTIONS(46),
    [anon_sym_divf] = ACTIONS(46),
    [anon_sym_jmp] = ACTIONS(46),
    [anon_sym_jmp_if] = ACTIONS(46),
    [anon_sym_ret] = ACTIONS(46),
    [anon_sym_call] = ACTIONS(46),
    [anon_sym_native] = ACTIONS(46),
    [anon_sym_eq] = ACTIONS(46),
    [anon_sym_halt] = ACTIONS(46),
    [anon_sym_not] = ACTIONS(46),
    [anon_sym_gei] = ACTIONS(46),
    [anon_sym_gef] = ACTIONS(46),
    [anon_sym_andb] = ACTIONS(46),
    [anon_sym_orb] = ACTIONS(46),
    [anon_sym_xor] = ACTIONS(46),
    [anon_sym_shr] = ACTIONS(46),
    [anon_sym_shl] = ACTIONS(46),
    [anon_sym_notb] = ACTIONS(46),
    [anon_sym_read8] = ACTIONS(44),
    [anon_sym_read16] = ACTIONS(44),
    [anon_sym_read32] = ACTIONS(44),
    [anon_sym_read64] = ACTIONS(44),
    [anon_sym_write8] = ACTIONS(44),
    [anon_sym_write16] = ACTIONS(44),
    [anon_sym_write32] = ACTIONS(44),
    [anon_sym_write64] = ACTIONS(44),
    [sym_comment] = ACTIONS(44),
  },
  [6] = {
    [ts_builtin_sym_end] = ACTIONS(48),
    [anon_sym_PERCENTinclude] = ACTIONS(48),
    [anon_sym_PERCENTbind] = ACTIONS(48),
    [sym__label_name] = ACTIONS(48),
    [anon_sym_nop] = ACTIONS(50),
    [anon_sym_push] = ACTIONS(50),
    [anon_sym_drop] = ACTIONS(50),
    [anon_sym_dup] = ACTIONS(50),
    [anon_sym_swap] = ACTIONS(50),
    [anon_sym_plusi] = ACTIONS(50),
    [anon_sym_minusi] = ACTIONS(50),
    [anon_sym_multi] = ACTIONS(50),
    [anon_sym_divi] = ACTIONS(50),
    [anon_sym_modi] = ACTIONS(50),
    [anon_sym_plusf] = ACTIONS(50),
    [anon_sym_minusf] = ACTIONS(50),
    [anon_sym_multf] = ACTIONS(50),
    [anon_sym_divf] = ACTIONS(50),
    [anon_sym_jmp] = ACTIONS(50),
    [anon_sym_jmp_if] = ACTIONS(50),
    [anon_sym_ret] = ACTIONS(50),
    [anon_sym_call] = ACTIONS(50),
    [anon_sym_native] = ACTIONS(50),
    [anon_sym_eq] = ACTIONS(50),
    [anon_sym_halt] = ACTIONS(50),
    [anon_sym_not] = ACTIONS(50),
    [anon_sym_gei] = ACTIONS(50),
    [anon_sym_gef] = ACTIONS(50),
    [anon_sym_andb] = ACTIONS(50),
    [anon_sym_orb] = ACTIONS(50),
    [anon_sym_xor] = ACTIONS(50),
    [anon_sym_shr] = ACTIONS(50),
    [anon_sym_shl] = ACTIONS(50),
    [anon_sym_notb] = ACTIONS(50),
    [anon_sym_read8] = ACTIONS(48),
    [anon_sym_read16] = ACTIONS(48),
    [anon_sym_read32] = ACTIONS(48),
    [anon_sym_read64] = ACTIONS(48),
    [anon_sym_write8] = ACTIONS(48),
    [anon_sym_write16] = ACTIONS(48),
    [anon_sym_write32] = ACTIONS(48),
    [anon_sym_write64] = ACTIONS(48),
    [sym_comment] = ACTIONS(52),
  },
  [7] = {
    [ts_builtin_sym_end] = ACTIONS(19),
    [anon_sym_PERCENTinclude] = ACTIONS(19),
    [anon_sym_PERCENTbind] = ACTIONS(19),
    [sym__label_name] = ACTIONS(19),
    [anon_sym_nop] = ACTIONS(55),
    [anon_sym_push] = ACTIONS(55),
    [anon_sym_drop] = ACTIONS(55),
    [anon_sym_dup] = ACTIONS(55),
    [anon_sym_swap] = ACTIONS(55),
    [anon_sym_plusi] = ACTIONS(55),
    [anon_sym_minusi] = ACTIONS(55),
    [anon_sym_multi] = ACTIONS(55),
    [anon_sym_divi] = ACTIONS(55),
    [anon_sym_modi] = ACTIONS(55),
    [anon_sym_plusf] = ACTIONS(55),
    [anon_sym_minusf] = ACTIONS(55),
    [anon_sym_multf] = ACTIONS(55),
    [anon_sym_divf] = ACTIONS(55),
    [anon_sym_jmp] = ACTIONS(55),
    [anon_sym_jmp_if] = ACTIONS(55),
    [anon_sym_ret] = ACTIONS(55),
    [anon_sym_call] = ACTIONS(55),
    [anon_sym_native] = ACTIONS(55),
    [anon_sym_eq] = ACTIONS(55),
    [anon_sym_halt] = ACTIONS(55),
    [anon_sym_not] = ACTIONS(55),
    [anon_sym_gei] = ACTIONS(55),
    [anon_sym_gef] = ACTIONS(55),
    [anon_sym_andb] = ACTIONS(55),
    [anon_sym_orb] = ACTIONS(55),
    [anon_sym_xor] = ACTIONS(55),
    [anon_sym_shr] = ACTIONS(55),
    [anon_sym_shl] = ACTIONS(55),
    [anon_sym_notb] = ACTIONS(55),
    [anon_sym_read8] = ACTIONS(19),
    [anon_sym_read16] = ACTIONS(19),
    [anon_sym_read32] = ACTIONS(19),
    [anon_sym_read64] = ACTIONS(19),
    [anon_sym_write8] = ACTIONS(19),
    [anon_sym_write16] = ACTIONS(19),
    [anon_sym_write32] = ACTIONS(19),
    [anon_sym_write64] = ACTIONS(19),
    [sym_comment] = ACTIONS(19),
  },
  [8] = {
    [ts_builtin_sym_end] = ACTIONS(57),
    [anon_sym_PERCENTinclude] = ACTIONS(57),
    [anon_sym_PERCENTbind] = ACTIONS(57),
    [sym__label_name] = ACTIONS(57),
    [anon_sym_nop] = ACTIONS(59),
    [anon_sym_push] = ACTIONS(59),
    [anon_sym_drop] = ACTIONS(59),
    [anon_sym_dup] = ACTIONS(59),
    [anon_sym_swap] = ACTIONS(59),
    [anon_sym_plusi] = ACTIONS(59),
    [anon_sym_minusi] = ACTIONS(59),
    [anon_sym_multi] = ACTIONS(59),
    [anon_sym_divi] = ACTIONS(59),
    [anon_sym_modi] = ACTIONS(59),
    [anon_sym_plusf] = ACTIONS(59),
    [anon_sym_minusf] = ACTIONS(59),
    [anon_sym_multf] = ACTIONS(59),
    [anon_sym_divf] = ACTIONS(59),
    [anon_sym_jmp] = ACTIONS(59),
    [anon_sym_jmp_if] = ACTIONS(59),
    [anon_sym_ret] = ACTIONS(59),
    [anon_sym_call] = ACTIONS(59),
    [anon_sym_native] = ACTIONS(59),
    [anon_sym_eq] = ACTIONS(59),
    [anon_sym_halt] = ACTIONS(59),
    [anon_sym_not] = ACTIONS(59),
    [anon_sym_gei] = ACTIONS(59),
    [anon_sym_gef] = ACTIONS(59),
    [anon_sym_andb] = ACTIONS(59),
    [anon_sym_orb] = ACTIONS(59),
    [anon_sym_xor] = ACTIONS(59),
    [anon_sym_shr] = ACTIONS(59),
    [anon_sym_shl] = ACTIONS(59),
    [anon_sym_notb] = ACTIONS(59),
    [anon_sym_read8] = ACTIONS(57),
    [anon_sym_read16] = ACTIONS(57),
    [anon_sym_read32] = ACTIONS(57),
    [anon_sym_read64] = ACTIONS(57),
    [anon_sym_write8] = ACTIONS(57),
    [anon_sym_write16] = ACTIONS(57),
    [anon_sym_write32] = ACTIONS(57),
    [anon_sym_write64] = ACTIONS(57),
    [sym_comment] = ACTIONS(57),
  },
  [9] = {
    [ts_builtin_sym_end] = ACTIONS(61),
    [anon_sym_PERCENTinclude] = ACTIONS(61),
    [anon_sym_PERCENTbind] = ACTIONS(61),
    [sym__label_name] = ACTIONS(61),
    [anon_sym_nop] = ACTIONS(63),
    [anon_sym_push] = ACTIONS(63),
    [anon_sym_drop] = ACTIONS(63),
    [anon_sym_dup] = ACTIONS(63),
    [anon_sym_swap] = ACTIONS(63),
    [anon_sym_plusi] = ACTIONS(63),
    [anon_sym_minusi] = ACTIONS(63),
    [anon_sym_multi] = ACTIONS(63),
    [anon_sym_divi] = ACTIONS(63),
    [anon_sym_modi] = ACTIONS(63),
    [anon_sym_plusf] = ACTIONS(63),
    [anon_sym_minusf] = ACTIONS(63),
    [anon_sym_multf] = ACTIONS(63),
    [anon_sym_divf] = ACTIONS(63),
    [anon_sym_jmp] = ACTIONS(63),
    [anon_sym_jmp_if] = ACTIONS(63),
    [anon_sym_ret] = ACTIONS(63),
    [anon_sym_call] = ACTIONS(63),
    [anon_sym_native] = ACTIONS(63),
    [anon_sym_eq] = ACTIONS(63),
    [anon_sym_halt] = ACTIONS(63),
    [anon_sym_not] = ACTIONS(63),
    [anon_sym_gei] = ACTIONS(63),
    [anon_sym_gef] = ACTIONS(63),
    [anon_sym_andb] = ACTIONS(63),
    [anon_sym_orb] = ACTIONS(63),
    [anon_sym_xor] = ACTIONS(63),
    [anon_sym_shr] = ACTIONS(63),
    [anon_sym_shl] = ACTIONS(63),
    [anon_sym_notb] = ACTIONS(63),
    [anon_sym_read8] = ACTIONS(61),
    [anon_sym_read16] = ACTIONS(61),
    [anon_sym_read32] = ACTIONS(61),
    [anon_sym_read64] = ACTIONS(61),
    [anon_sym_write8] = ACTIONS(61),
    [anon_sym_write16] = ACTIONS(61),
    [anon_sym_write32] = ACTIONS(61),
    [anon_sym_write64] = ACTIONS(61),
    [sym_comment] = ACTIONS(61),
  },
  [10] = {
    [ts_builtin_sym_end] = ACTIONS(65),
    [anon_sym_PERCENTinclude] = ACTIONS(65),
    [anon_sym_PERCENTbind] = ACTIONS(65),
    [sym__label_name] = ACTIONS(65),
    [anon_sym_nop] = ACTIONS(67),
    [anon_sym_push] = ACTIONS(67),
    [anon_sym_drop] = ACTIONS(67),
    [anon_sym_dup] = ACTIONS(67),
    [anon_sym_swap] = ACTIONS(67),
    [anon_sym_plusi] = ACTIONS(67),
    [anon_sym_minusi] = ACTIONS(67),
    [anon_sym_multi] = ACTIONS(67),
    [anon_sym_divi] = ACTIONS(67),
    [anon_sym_modi] = ACTIONS(67),
    [anon_sym_plusf] = ACTIONS(67),
    [anon_sym_minusf] = ACTIONS(67),
    [anon_sym_multf] = ACTIONS(67),
    [anon_sym_divf] = ACTIONS(67),
    [anon_sym_jmp] = ACTIONS(67),
    [anon_sym_jmp_if] = ACTIONS(67),
    [anon_sym_ret] = ACTIONS(67),
    [anon_sym_call] = ACTIONS(67),
    [anon_sym_native] = ACTIONS(67),
    [anon_sym_eq] = ACTIONS(67),
    [anon_sym_halt] = ACTIONS(67),
    [anon_sym_not] = ACTIONS(67),
    [anon_sym_gei] = ACTIONS(67),
    [anon_sym_gef] = ACTIONS(67),
    [anon_sym_andb] = ACTIONS(67),
    [anon_sym_orb] = ACTIONS(67),
    [anon_sym_xor] = ACTIONS(67),
    [anon_sym_shr] = ACTIONS(67),
    [anon_sym_shl] = ACTIONS(67),
    [anon_sym_notb] = ACTIONS(67),
    [anon_sym_read8] = ACTIONS(65),
    [anon_sym_read16] = ACTIONS(65),
    [anon_sym_read32] = ACTIONS(65),
    [anon_sym_read64] = ACTIONS(65),
    [anon_sym_write8] = ACTIONS(65),
    [anon_sym_write16] = ACTIONS(65),
    [anon_sym_write32] = ACTIONS(65),
    [anon_sym_write64] = ACTIONS(65),
    [sym_comment] = ACTIONS(65),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 2,
    ACTIONS(69), 1,
      sym_identifier,
    ACTIONS(71), 1,
      sym_string,
  [7] = 1,
    ACTIONS(73), 2,
      sym_string,
      sym_number,
  [12] = 1,
    ACTIONS(75), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(11)] = 0,
  [SMALL_STATE(12)] = 7,
  [SMALL_STATE(13)] = 12,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(4),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [15] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [19] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [21] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(11),
  [24] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(5),
  [27] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(4),
  [30] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(4),
  [33] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(3),
  [36] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_operation, 1),
  [38] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_operation, 1),
  [40] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [42] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [44] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_label, 1, .production_id = 1),
  [46] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_label, 1, .production_id = 1),
  [48] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 1),
  [50] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 1),
  [52] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 1), SHIFT_REPEAT(7),
  [55] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [57] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_directive, 2, .production_id = 2),
  [59] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_directive, 2, .production_id = 2),
  [61] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_operation, 2, .production_id = 3),
  [63] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_operation, 2, .production_id = 3),
  [65] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_directive, 3, .production_id = 4),
  [67] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_directive, 3, .production_id = 4),
  [69] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [71] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [73] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [75] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_hack(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
