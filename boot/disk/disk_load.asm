disk_load:
	push dx

	mov ah, 0x02		; BOIS read sector function
	mov al, dh			; Read DH amount of sectors
	mov ch, 0x00		; Select cylinder 0
	mov dh, 0x00		; Select head 1 of the disk since it starts at 0
	mov cl, 0x02		; Select the 2nd (after the boot sector)

	int 0x13			; BIOS interrupt for read disk function

	jc disk_error 		; Jump to disk_error if BIOS failed to read disk

	pop dx
	cmp dh, al
	jne disk_error
	ret

disk_error:
	mov bx, DISK_ERROR_MSG
	call print
	jmp $ ; Hang

DISK_ERROR_MSG:
	db 'COULD NOT READ DISK', 0
