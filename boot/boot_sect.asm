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

	mov bx, 0x9000 
	mov dh, 5			; Load 5 sectors to 0x0000:0x9000(ES:BX)
	mov dl, [BOOT_DRIVE]; Load from boot drive
	call disk_load

	pusha 
	mov dx, [0x9000] 	; load data we loaded from disk
	call print_hex		; dx is hex to print
	popa

	pusha 
	mov dx, [0x9000 + 512]; load data we loaded from disk
	call print_hex		  ; dx is hex to print
	popa

	pusha 				; Push all registers to the stack
	mov bx, BOOT_MSG
	call print 			; bx should be pointer to data
	popa

	jmp the_end 		; Jump past all code

%include "./boot/disk_load.asm"
%include "./boot/bios_print.asm"

; DATA SECTION

BOOT_MSG:
	db 'Booting MOS...', 0 ; Null terminated string

BOOT_DRIVE: db 0


the_end:

;
; Padding and magic BIOS number
;

times 510-($-$$) db 0

dw 0xaa55
times 256 dw 0xdead 
times 256 dw 0xbeef
