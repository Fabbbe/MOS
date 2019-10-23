; 
; File of print functions
;
; TODO: add more and better documentation
[bits 16]

print_hex:
	pusha
	mov cx, 4			; Init the counter to 4

print_hex_loop:
	dec cx				; decrease the counter
	mov ax, dx			; copy dx to ax for obscuring numbers
	shr dx, 4			; 
	and ax, 0xf			; obscure 
	
	mov bx,	HEX_OUT 	; move bx to point to current byte we want changed = c & 0xf;
	add bx, 2			; skip the beginning "0x"
	add bx, cx			; Go to current position in HEX_OUT

	cmp ax, 0xa 		; See if value is letter (over 10)
	jl set_letter		; if not letter just add to HEX_OUT

	add byte [bx], 7 	; Skip the 7 non chars in ascii
	jmp set_letter		; then add to HEX_OUT

set_letter:
	add byte [bx], al 	; add to the current position determined by cx in HEX_OUt
	cmp cx,0 			; Check if counter is 0
	je print_hex_end	; then end
	jmp print_hex_loop	; else loop again
	
print_hex_end:
	mov bx, HEX_OUT 	; Move back pointer to beginning of data
	call print 			; Print out new HEX_OUT

	mov byte [HEX_OUT+2], '0' ; Reset HEX_OUT so you can print multiple times
	mov byte [HEX_OUT+3], '0'  
	mov byte [HEX_OUT+4], '0'
	mov byte [HEX_OUT+5], '0'

	popa
	ret

HEX_OUT:
	db '0x0000', 0 ; Null terminated string



print: ; prints wathever the bx register points to
	pusha
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
	popa
	ret
