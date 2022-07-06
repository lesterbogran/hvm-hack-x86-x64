#!/usr/bin/env nu

let cc = 'cc'
let cflags = '-Wall -Wextra -Wswitch-enum -Wmissing-prototypes -Wconversion -pedantic -fno-strict-aliasing -ggdb -std=c11'
let libs = ''

let tools = [hackc hack dehack hdb]
let examples = (ls examples/*.hack | where name != natives.hack).name

$tools | each { |t| $'($cc) ($cflags) -o ($t) src/($t).c' }
$examples | each { |e| $'./hackc -d ($e) ($e | str replace "(.+).hack" "$1.har")' }
