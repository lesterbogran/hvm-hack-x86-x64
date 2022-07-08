module.exports = grammar({
  name: 'hack',

  rules: {
    source_file: $ => repeat(
      choice(
        seq($._expression, optional($.comment)),
        $.comment,
      )
    ),

    _expression: $ => choice(
      $.directive,
      $.label,
      $.operation,
    ),

    directive: $ => choice(
      seq(
        field('name', $._directive_name),
        field('label', $.identifier),
        field('value', choice($.string, $.number)),
      ),
      seq(
        field('name', $._directive_name),
        field('param', $.string),
      )
    ),

    _directive_name: () => choice(
      '%include',
      '%bind',
    ),

    label: $ => seq(
      field('name', $._label_name),
    ),

    _label_name: () => /[a-zA-Z_]+:/,

    operation: $ => seq(
      $._inst,
      field('operand', optional(
        choice($.identifier, $.number)
      ))
    ),

    _inst: () => choice(
      'nop',
      'push',
      'drop',
      'dup',
      'swap',
      'plusi',
      'minusi',
      'multi',
      'divi',
      'modi',
      'plusf',
      'minusf',
      'multf',
      'divf',
      'jmp',
      'jmp_if',
      'ret',
      'call',
      'native',
      'eqi',
      'eqf',
      'halt',
      'not',
      'gei',
      'gef',
      'andb',
      'orb',
      'xor',
      'shr',
      'shl',
      'notb',
      'read8',
      'read16',
      'read32',
      'read64',
      'write8',
      'write16',
      'write32',
      'write64',
      'i2f',
      'u2f',
      'f2i',
      'f2u',
    ),

    identifier: () => token(prec(-1, /[A-Za-z.@_][A-Za-z0-9.@_$-]*/)),
    string: () => /"(.*)"/,
    number: () => /[0-9]+/,
    comment: () => /[;]([^\n]*)/,
  }
})
