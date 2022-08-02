%include "./examples/natives.hack"

main:
    push 1234567890
    call print_u64_
    halt

%entry main