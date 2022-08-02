%bind alloc       0
%bind free        1
%bind print_f64   2
%bind print_i64   3
%bind print_u64   4
%bind print_ptr   5
%bind dump_memory 6
%bind write       7

%bind print_memory "******************************"

reverse:
    ret

;; x
;; print_memory
print_u64_:
    swap 1

    push print_memory
    
    print_u64_loop:
        dup 1
        push 10
        modi
        push '0'
        plusi
    
        dup 1
        swap 1
        write8
    
        push 1
        plusi
    
        swap 1
        push 10
        divi
        swap 1
    
        dup 1
        push 0
        eqi
        not
    jmp_if print_u64_loop

    dup 0
    push 10
    write8

    push 1
    plusi

    push print_memory
    swap 1
    minusi

    push print_memory
    swap 1

    native write

    drop

    ret