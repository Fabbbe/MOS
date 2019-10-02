[bits 32]
; Constant meomry addresses
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_string_pm: ; print_string_pms wathever the bx register points to
	pusha
	mov edx, VIDEO_MEMORY ; Set EDX to start of video memory

print_string_pm_loop:
	mov al, [ebx]
	mov ah, WHITE_ON_BLACK

	cmp al, 0x00
	je print_string_pm_end

	mov [edx], ax

	add ebx, 1
	add edx, 2

	jmp print_string_pm_loop

print_string_pm_end:
	popa
	ret
