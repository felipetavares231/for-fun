[bits 16]
[org 0x7c00]

start:
    mov ax, 0x0003
    int 0x10

    mov si, loading_msg
    call print_string

    mov bl, 6
.load_loop:
    mov cx, 0x0007
    mov dx, 0xA120
    mov ah, 0x86
    int 0x15
    mov ah, 0x0e
    mov al, 0xDB
    int 0x10
    dec bl
    jnz .load_loop

    mov si, loading_ok
    call print_string

    mov ax, 0x0003
    int 0x10

    mov si, skin_art
    call print_string

.keyloop:
    mov ah, 0x00
    int 0x16
    mov ah, 0x0e
    int 0x10
    jmp .keyloop

print_string:
    mov ah, 0x0e
.loop:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .loop
.done:
    ret

loading_msg:
    db 13, 10, 13, 10, 13, 10
    db "     boosterOS", 13, 10
    db 13, 10
    db "     [", 0

loading_ok:
    db "] OK!", 13, 10, 0

skin_art:
    db "  boosterOS", 13, 10
    db 13, 10
    db "    @@@@@@@@", 13, 10
    db "    @@@@@@@@", 13, 10
    db "    @%%#%%%@", 13, 10
    db "    %%%%@%@@", 13, 10
    db "    %  %%  %", 13, 10
    db "    @%%@@%@@", 13, 10
    db "    @@@@@@@@", 13, 10
    db "    @@@@@@@@", 13, 10
    db "@@@@@@@@@@@@@@@@", 13, 10
    db "@@@@@@@@@@@@@@@@", 13, 10
    db "@@@@@@*--:=@@@@@", 13, 10
    db "@@@@@+..:::*@@@@", 13, 10
    db "@@@@#=::-***@@@@", 13, 10
    db "@%%%+=-*@@@@%%%@", 13, 10
    db "@%%@+-*@@%@@@%%@", 13, 10
    db "%%%@*-=@%%@@@%%%", 13, 10
    db "%%%@@=-#%#@@@%%%", 13, 10
    db "%%%%@@*++%@@%%%%", 13, 10
    db "%@@%@@@@@@@@%@@%", 13, 10
    db "%@@@@@@@@@@@@@@%", 13, 10
    db "  boosterruns", 13, 10
    db 0

times 510-($-$$) db 0
db 0x55, 0xaa
