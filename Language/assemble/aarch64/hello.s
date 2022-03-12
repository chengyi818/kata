.text

.global main
main:
ldr x0, addr_of_keep_x30
str x30, [x0]

ldr x0, addr_of_msg
bl puts

ldr x0, addr_of_keep_x30
ldr x30, [x0]

mov w0, #0
ret


addr_of_msg: .dword msg
addr_of_keep_x30: .dword keep_x30

.data
msg: .asciz "hello world!\n"
keep_x30: .dword 0

