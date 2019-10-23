;
; Entry point for bios that currently does nothing
;
[org 0x7c00]
KERNEL_OFFSET equ 0x1000 ; Memory offset to load kernel into

entry: ; Entrypoint of BIOS

	; Disk reading functions
	mov [BOOT_DRIVE], dl ; BIOS stores boot dirve in DL, so we can store it 
						 ; in memory

	mov bp, 0x9000 		; stack pointer address
	mov sp, bp

	;mov ah, 0x01		; Set cursor shape
	;mov ch, 0x3f		; disable cursor
	;int 0x10

	; Just print boot message
	mov bx, MSG_REAL_MODE
	call print

	call load_kernel

	call switch_to_pm	; We will never return from this
	jmp $


%include "./boot/print/bios_print.asm"
%include "./boot/disk/disk_load.asm"
%include "./boot/pm/gdt_data.asm"
%include "./boot/pm/print.asm"
%include "./boot/pm/switch_to_pm.asm"

[bits 16]
load_kernel:
	mov bx, MSG_LOAD_KERNEL
	call print
	
	mov bx, KERNEL_OFFSET	; Set up parameters for disk_load
	mov dh, 15
	mov dl, [BOOT_DRIVE]
	call disk_load

	ret

[bits 32]
; Init registers and stack once in pm

BEGIN_PM:
	mov ebx, MSG_PROT_MODE
	call print_string_pm

	call KERNEL_OFFSET

	jmp $

; DATA SECTION

MSG_REAL_MODE: db 'Booting MOS...', 0
MSG_PROT_MODE: db 'Entering 32-bit Protected Mode ', 0
MSG_LOAD_KERNEL: db 'Loading kernel into memory', 0

BOOT_DRIVE: db 0

;
; Padding and magic BIOS number
;

times 510-($-$$) db 0

dw 0xaa55
