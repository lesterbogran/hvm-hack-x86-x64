%include "./examples/natives.hack"

main:
    push 1
    push 2
    push 3
    plusi
    plusi
    native 3
    halt

%entry main