MBOOT_PAGE_ALIGN equ 1<<0
MBOOT_MEM_INFO equ 1<<1
MBOOT_AOUT_KLUDGE equ 1<<16
MBOOT_ALIGN_MODULES   equ 0x00000001
MBOOT_HEADER_MAGIC equ  0x1BADB002 
MBOOT_HEADER_FLAGS equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO | MBOOT_AOUT_KLUDGE | MBOOT_ALIGN_MODULES
MBOOT_CHECKSUM equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

bits 32

global mboot
extern code
extern bss
extern end

mboot:
	dd MBOOT_HEADER_MAGIC
	dd MBOOT_HEADER_FLAGS
	dd MBOOT_CHECKSUM

	dd mboot
	dd code
	dd bss
	dd end
	dd boot
global boot
extern kmain

global gdt_flush
extern gp
gdt_flush:
	lgdt [gp]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush2
flush2:
	ret
boot:
	mov esp, sys_stack
	push ebx
	push eax
	cli
	call kmain
	hlt



section .bss
	align 16
	resb 32768
sys_stack:
	resb 32768
	align 4096
	global heap
heap:
	resb 1<<23