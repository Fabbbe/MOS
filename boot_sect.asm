;
; Prints Smiley Face over and over again
;

[org 0x7c00]

entry: ; Entrypoint of BIOS
	mov bp, 0x8000
	mov sp, bp

	pusha ; Push all registers to the stack
	mov bx, boot_msg
	call print ; ax unused, bx pointer to data, cx unused
	popa

	jmp entry ; Jump past all code

print: ; prints wathever the bx register points to
	mov ah, 0x0e ; int 0x10 / ah = 0x0e, BIOS Print interrupt
	jmp print_loop
print_loop:
	mov al, [bx]
	cmp al, 0x00
	je print_end
	int 0x10
	inc bx
	jmp print_loop
print_end:
	ret

boot_msg:
	db 'FUCK YEAH', 0 ; Null terminated string

the_end:

;
; Padding and BIOS number
;

times 510-($-$$) db 0

dw 0xaa55
