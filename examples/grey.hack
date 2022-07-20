;; Generate N Gray Code numbers https://en.wikipedia.org/wiki/Gray_Code

%include "./examples/natives.hack"

%bind N 100

main:
    push 0        ; i
loop:
    dup 0
    dup 0
    push 1
    shr
    xor
    native print_u64
    
    push 1
    plusi
    
    dup 0
    push N
    eqi
    not
    
    jmp_if loop

    halt

%entry main