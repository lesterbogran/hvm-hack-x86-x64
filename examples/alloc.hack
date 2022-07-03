%include "./examples/natives.hack"
%bind MEMORY_SIZE 420

push MEMORY_SIZE 
native alloc
dup 0
native print_ptr
native free
halt
