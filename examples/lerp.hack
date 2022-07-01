    jmp main

# a
# b
# t
# --
# a + (b - a) * t
lerpf:
    dup 3
    dup 3
    dup 1
    minusf
    dup 3
    multf
    plusf

    # clean up
    swap 2
    drop
    swap 2
    drop
    swap 2
    drop
    ret

# TODO(#4): make lerp.hack example more interesting
# Sample throw the lerp with regular intervals
main:
    push 69.0
    push 420.0
    push 0.0
    call lerpf
    native 2
    # 69.0

    push 69.0
    push 420.0
    push 1.0
    call lerpf
    native 2
    # 420.0

    push 69.0
    push 420.0
    push 0.5
    call lerpf
    native 2
    # 244.5

    halt
