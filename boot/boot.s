MBOOT_PAGE_ALIGN equ 1<<0
MBOOT_MEM_INFO equ 1<<1
MBOOT_HEADER_MAGIC equ  0x1BADB002 
MBOOT_HEADER_FLAGS equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
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

jmp load_gdt

gdt:
gdt_null:
	dq 0
gdt_code:
	dw 0xFFFF
	dw 0

	db 0
	db 10011010b
	db 11001111b
	db 0

gdt_data:
	dw 0xFFFF
	dw 0

	db 0
	db 10010010b
	db 11001111b
	db 0
gdt_end:

gdt_desc:
	dw gdt_end - gdt - 1
	dd gdt

load_gdt:
	cli
	lgdt[gdt_desc]
	sti
global idt_flush
idt_flush:
	mov eax, [esp + 4]
	lidt [eax]
	ret
boot:
	push ebx
	cli
	call kmain
	jmp $

