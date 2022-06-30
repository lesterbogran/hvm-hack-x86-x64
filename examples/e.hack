# n+1.0
# n!*(n+1.0)
# sum+1.0/n!

# sum(1/n!)
# 1/1 + 1/1 + 1/(1 * 2) + 1/(1 * 2 * 3) + ...
    push 1.0       # n
    push 1.0       # n!
    push 1.0       # sum
loop:
    push 1.0
    dup 2
    divf
    plusf

    swap 2
    push 1.0
    plusf
    dup 0
    swap 2
    multf

    swap 1
    swap 2

    dup 2
    push 100.0
    gef

    jmp_if loop

    swap 1
    drop
    swap 1
    drop

    halt
