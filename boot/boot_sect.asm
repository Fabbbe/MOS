;
; Entry point for bios that currently does nothing
;

[org 0x7c00]

entry: ; Entrypoint of BIOS
	mov bp, 0x8000
	mov sp, bp

	pusha 
	mov dx, 0x0919 		; arbitrary number
	call print_hex		; dx is hex to print
	popa

	pusha 				; Push all registers to the stack
	mov bx, BOOT_MSG
	call print 			; bx should be pointer to data
	popa

	jmp the_end 		; Jump past all code


%include "./boot/bios_print.asm"


; DATA SECTION

BOOT_MSG:
	db ' Booting MOS...', 0 ; Null terminated string

the_end:

;
; Padding and magic BIOS number
;

times 510-($-$$) db 0

dw 0xaa55
