; Interrupt assembly code
;
;

global keyboard_handler
global load_idt

extern keyboardHandlerMain

load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti
	ret

keyboard_handler:
	call keyboardHandlerMain
	iretd
