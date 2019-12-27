printString:
	push ax

.loop:
	cmp [si], byte 0
	je .end
	mov ah, 0x0e
	mov al, [si]
	int 0x10
	inc si
	jmp .loop

.end:
	pop ax
	ret

printHex:
	; We're going to loop 4 times and process 4 bits each iteration.
	; By right shifting and ANDing we get the 4 bit integer, which
	;   we can do simple arithmetics on to get the proper ASCII value.
	xor dx, dx ;counter

.loop:
	mov ax, si
	mov cx, dx
	shl cx, 2  ; x4
	shr ax, cl ; Shift to 4 LSB
	and ax, 0xf
	cmp al, 9
	jle .loopend
	add al, 7  ; Diff between ASCII 0-9 and A-F 

.loopend:
	add al, 48 ; ASCII 0
	mov bx, 3
	sub bx, dx ; Calculate the offset into the string
	           ; (0th number (from right) is 3 into string)
	mov [STR_HEX + bx + 2], al
	inc dx
	cmp dx, 3
	jle .loop

.print:
	mov si, STR_HEX
	call printString
	ret

STR_HEX: db "0x0000", 10, 13, 0
