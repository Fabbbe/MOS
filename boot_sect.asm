;
; Prints Smiley Face over and over again
;

[org 0x7c00]

entry: ; Entrypoint of BIOS
	mov bp, 0x8000
	mov sp, bp

	pusha 
	mov dx, 0x0911
	call print_hex
	popa

	pusha ; Push all registers to the stack
	mov bx, BOOT_MSG
	call print ; ax unused, bx pointer to data, cx unused
	popa

	jmp the_end ; Jump past all code


%include "bios_print.asm"

BOOT_MSG:
	db ' Booting MOS...', 0 ; Null terminated string

HEX_OUT:
	db '0x0000', 0 ; Null terminated string

the_end:

;
; Padding and BIOS number
;

times 510-($-$$) db 0

dw 0xaa55
