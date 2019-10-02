;
; Entry point for bios that currently does nothing
;
[org 0x7c00]

entry: ; Entrypoint of BIOS

	; Disk reading functions
	mov [BOOT_DRIVE], dl ; BIOS stores boot dirve in DL, so we can store it 
						 ; in memory

	mov bp, 0x8000 		; stack pointer address
	mov sp, bp

	; Just print boot message
	mov bx, MSG_REAL_MODE
	call print

	jmp switch_to_pm; We should never return from this
	jmp $


;%include "./boot/disk_load.asm"
%include "./boot/16/bios_print.asm"
%include "./boot/gdt_data.asm"
%include "./boot/32/print.asm"
%include "./boot/switch_to_pm.asm"

[bits 32]
; Init registers and stack once in pm

BEGIN_PM:
	mov ebx, MSG_PROT_MODE
	call print_string_pm
	jmp $

; DATA SECTION

MSG_REAL_MODE:
	db 'Booting MOS...', 0 ; Null terminated string
MSG_PROT_MODE:
	db 'Entering 32-bit Protected Mode ', 0 ; Null terminated string

BOOT_DRIVE: db 0

;
; Padding and magic BIOS number
;

times 510-($-$$) db 0

dw 0xaa55
