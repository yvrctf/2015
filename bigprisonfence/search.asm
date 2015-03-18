mov al, byte [0xDEADBEEF]
cmp al, 123
jge label
int 3
label:
xor eax, eax
mov ebx, eax
or eax, 1
int 0x80
