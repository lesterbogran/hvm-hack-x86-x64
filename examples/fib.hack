# Some nonsense to test label resolution
    jmp 1
    nop
    nop
    nop
# First two Fibonacci numbers
    push 0
    push 1
loop:
    dup 1   # The Loop
    dup 1
    plusi
    jmp loop   # Repeat
