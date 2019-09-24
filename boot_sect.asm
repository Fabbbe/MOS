;
; Prints Booting OS... And does nothing.
;

[org 0x7c00]

entry: ; Entrypoint of BIOS
	mov bp, 0x8000
	mov sp, bp

	mov ah, 0x0e ; int 10 / ah = 0eh -> scrolling teletype BIOS routine

	mov cx, 0x00
	jmp loop

loop:
	cmp cx, 12 ; number of bytes in boot_msg
	je the_end
	
	mov bx, boot_msg
	add bx, cx
	mov al, [bx]
	int 0x10

	add cl, 0x01
	jmp loop

boot_msg:
	db 'Smiley Face '


the_end:
	jmp entry

;
; Padding and BIOS number
;

times 510-($-$$) db 0

dw 0xaa55
