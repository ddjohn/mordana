printStringProtected:
	pusha
	mov edx, 0xb8000

.loop:
	cmp [si], byte 0
	je .end
	mov ah, 0x0f
	mov al, [si]
	mov [edx], ax
	inc si
	add edx, 2
	jmp .loop

.end:
	popa
	ret

