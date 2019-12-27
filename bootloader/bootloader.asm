ORG 0x7c00
BITS 16		; Target Processor Mode
CPU 386		; Assemble instructions up to the 386 instruction set

KERNEL_ADDRESS equ 0x1000

main:
	mov [BOOT_DRIVE], dl

	call setRedBackground

	mov si, STRING_BOOTLOADER
	call printString

	mov si, STRING_PRESS_ANY_KEY
	call printString
	call pressAnyKey

	call clearScreen
	call loadKernel

protected:
	cli
	lgdt [gdtEnd]
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
	jmp CODE_SEGMENT:initProtectedMode

includes:
	%include "asm/keys.asm"
	%include "asm/print.asm"
	%include "asm/screen.asm"
	%include "asm/loader.asm"

BITS 32		; 32 bit protected mode
initProtectedMode:
	mov ax, DATA_SEGMENT
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000
	mov esp, ebp

	jmp startProtectedMode

startProtectedMode:
	mov si, STRING_PROTECTED_MODE
	call printStringProtected

	call KERNEL_ADDRESS
	jmp $

; Data
%include "asm/protected.asm"

; Global Descriptor Table
gdtStart:
	dd 0x0
	dd 0x0
gdtCode:
	dw 0xffff
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0
gdtData:
	dw 0xffff
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0
gdtEnd:
	dw gdtEnd - gdtStart - 1
	dd gdtStart

CODE_SEGMENT equ gdtCode - gdtStart
DATA_SEGMENT equ gdtData - gdtStart

BOOT_DRIVE: db 0

STRING_BOOTLOADER:        db "Starting bootoader...", 10, 13, 0
STRING_PRESS_ANY_KEY:     db "=== Press ANY key ===", 10, 13, 0
STRING_PROTECTED_MODE:    db "Going into Protected Mode...", 0


times 510-($-$$) db 0
dw 0xaa55
