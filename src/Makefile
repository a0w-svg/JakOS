#Sources files compile
C_SOURCES = $(wildcard kernel/*.c drivers/*.c kernel/cpu/*.c libc/*.c common/*c)
#Headers files list
HEADERS = $(wildcard kernel/include/*.h drivers/include/*.h kernel/cpu/include/*.h libc/include/*.h common/*h)
#compiled files .o
OBJ = ${C_SOURCES:.c=.o kernel/cpu/interrupts.o} 
#add macro to the cross compiler
CC =i686-elf-gcc
#add macro to the debugger
GDB = i686-elf-gdb
#GCC flags
CFLAGS = -g -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs \
		 -Wall -Wextra -Werror

#create bootable file 
kernel.bin: boot/boot.o ${OBJ}
	i686-elf-ld  $^ -T Link.ld -o kernel.bin

#create file
kernel.elf: boot/boot.o ${OBJ}
	i686-elf-ld -T Link.ld ${OBJ} -o kernel.elf

#run compiled image
run: kernel.bin
	qemu-system-i386 -kernel kernel.bin

#debug compiled image
debug: os-image.bin kernel.elf
	qemu-system-i386 -s -kernel kernel.elf -d guest_errors,int &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

#compile c files
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@
#compiles nasm files to elf
%.o: %.s
	nasm $< -f elf -o $@
#compiles nasm files to bin
%.bin: %.s
	nasm $< -f bin -o $@
#clean compiled files
clean:
	rm -rf *.bin *.dis *.o os-image.bin *.

	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o kernel/cpu/*.o libc/*.o
