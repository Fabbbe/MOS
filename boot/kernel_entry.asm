; Makes sure that we enter into the right funcion
[bits 32]
[extern kmain]

	call kmain
	jmp $
