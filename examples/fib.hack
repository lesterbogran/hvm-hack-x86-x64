# Some nonsense to test label resolution
  jmp 1
  nop
  nop
  nop
# First two Fibonacci numbers
  push 0
  push 1
# The Loop
loop:
  dup 1
  dup 1
  plus
  jmp loop # Repeat
