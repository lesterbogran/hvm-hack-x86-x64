#!/usr/bin/env elvish

use str

var cc = 'cc'
if (not-eq '' $E:CC) { set cc = $E:CC }

var cflags = '-Wall -Wextra -Wswitch-enum -Wmissing-prototypes -Wconversion -pedantic -fno-strict-aliasing -ggdb -std=c11'
var libs = ''

var tools = [hackc hack dehack]
var examples = [(e:ls examples/**.hack)]

var run = {|cmd| eval $cmd; echo '+ '$cmd}

each {|tool| $run $cc' '$cflags' -o '$tool' src/'$tool'.c' } $tools

each {|example|
  if (not-eq $example "examples/natives.hack") {
    $run './hackc '$example' '(str:trim-suffix $example "hack")'har'
  }
} $examples