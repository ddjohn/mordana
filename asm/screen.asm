clearScreen:
	mov ax, 2
	int 0x10
	ret

setRedBackground:
	mov ah, 0x0B
	mov bx, 0x0034
	int 0x10
	ret

enterVideoMode:
	mov ax, 0x0013
	int 0x10
	ret

