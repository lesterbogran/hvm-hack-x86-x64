;; Fill up the memory with number from 0 to N
%include "./examples/natives.hack"

;; TODO(#21): hack does not support string literals

%bind N 256

    push 0        ; i
loop:
    dup 0
    dup 0
    write8
    
    push 1
    plusi
    
    dup 0
    push N
    eqi
    not

    jmp_if loop
    
    push 0
    push N
    native dump_memory
    
    halt
    
