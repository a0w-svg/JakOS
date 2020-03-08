# set magic number to 0x1BADB002 to identified by bootloader
.set MAGIC,	0x1BADB002 
# set flags to 0
.set FLAGS,	0
# set checksum
.set CHECKSUM, -(MAGIC + FLAGS)
# set multiboot enabled
.section .multiboot

# define type to long for each data defined as above
.long MAGIC
.long FLAGS
.long CHECKSUM

# set the stack bottom
stack_bottom:
# define maximum size of stack to 512 bytes
.skip 1024
# set the stack to which grows from higher to lower
stacktop:

.section .text
.global _start
.type _start, @function

_start:
# assign current stack pointer location to stackTop
		mov $stackTop, %esp
# call the kernel main source
		call k_main
		cli
# put system in infinite loop
hltLoop:
		hlt
		jmp hltLoop
		
.size _start, . - _start