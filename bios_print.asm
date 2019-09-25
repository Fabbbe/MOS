print_hex:
	; TODO: manipulate chars so HEX_OUT represents DX
	mov cx, 4	

print_hex_loop:
	dec cx
	mov ax, dx			; copy dx to ax for obscuring numbers
	shr dx, 4			; 
	and ax, 0xf
	
	mov bx,	HEX_OUT ; move bx to point to current byte we want changed
	add bx, 2
	add bx, cx

	cmp ax, 0xa 		; See if value is letter (over 10)
	jl set_letter		; if not letter

	add byte [bx], 7 	; Skip the 7 non chars in ascii
	jmp set_letter		; 

set_letter:
	add byte [bx], al
	cmp cx,0 			; Check if counter is 0
	je print_hex_end	; then end
	jmp print_hex_loop	; else loop again
	
print_hex_end:
	mov bx, HEX_OUT ; Move back pointer to beginning of data
	call print
	ret



print: ; prints wathever the bx register points to
	mov ah, 0x0e ; int 0x10 / ah = 0x0e, BIOS Print interrupt
	jmp print_loop
print_loop:
	mov al, [bx]
	cmp al, 0x00
	je print_end
	int 0x10
	inc bx
	jmp print_loop
print_end:
	ret
