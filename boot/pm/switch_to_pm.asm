[bits 16]
switch_to_pm:
	; Entering 32-bit protected mode
	cli 			; Clear the interrupt register
	lgdt [gdt_descriptor]
	
	mov eax, cr0	; Set the first bit of cr0, a control register to high to 
	or eax, 0x1		; switch to protected mode.
	mov cr0, eax	; update cr0.
	
	jmp CODE_SEG:init_pm

[bits 32]
init_pm:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000
	mov esp, ebp
	
	jmp BEGIN_PM
