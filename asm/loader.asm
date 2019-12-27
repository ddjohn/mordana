loadKernel:
	mov bx, KERNEL_ADDRESS
	mov dh, 10
	mov dl, [BOOT_DRIVE]
	call .loadDisk
	ret

.loadDisk:
	push dx

	mov ah, 0x02
	mov al, dh
	mov ch, 0x00
	mov cl, 0x02
	mov dh, 0x00
	int 0x13

	jc .error

	pop dx
	cmp dh, al
	jne .errorSectorsNotSame
	ret

.error:
	mov si, STRING_DISK_ERROR
	call printString

	mov dx, ax
	mov si, dx
	call printHex
	jmp $

.errorSectorsNotSame:
	mov si, STRING_DISK_SECTOR_ERROR
	call printString
	jmp $

STRING_DISK_ERROR:        db "Could not read from disk!", 10, 13, 0
STRING_DISK_SECTOR_ERROR: db "Could not read the specified amount of sectors from disk!", 10, 13, 0
