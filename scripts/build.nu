#!/usr/bin/env nu

let cc = 'cc'
let cflags = ['-Wall' '-Wextra' '-Wswitch-enum' '-Wmissing-prototypes' '-Wconversion' '-pedantic' '-fno-strict-aliasing' '-ggdb' '-std=c11']
let libs = ''

let tools = ['hackc' 'hack' 'dehack' 'hdb' 'hack2nasm']
let examples = (ls 'examples/*.hack' | where name != 'natives.hack').name

$tools
  | each { |it| 
      echo $'compiling ($it)...' | wrap 'tool' 
      ^$cc $cflags '-o' $it $'src/($it).c'
      if ($env.LAST_EXIT_CODE == 1) { exit 1 } 
    }

$examples 
  | each { |it| 
      echo $'compiling ($it)...' | wrap 'example'
      ^'./hackc' '-d' $it ($it | str replace '(.+).hack' '$1.har')
      if ($env.LAST_EXIT_CODE == 1) { exit 1 } 
    }
