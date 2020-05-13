C_SOURCES = $(wildcard kernel/*.c drivers/*.c kernel/cpu/*.c libc/*.c common/*c)
HEADERS = $(wildcard kernel/include/*.h drivers/include/*.h kernel/cpu/include/*.h libc/include/*.h common/*h)

OBJ = ${C_SOURCES:.c=.o kernel/cpu/interrupts.o} 

CC =i686-elf-gcc
GDB = i686-elf-gdb

CFLAGS = -g -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs \
		 -Wall -Wextra -Werror



kernel.bin: boot/boot.o ${OBJ}
	i686-elf-ld  $^ -T Link.ld -o kernel.bin


kernel.elf: boot/boot.o ${OBJ}
	i686-elf-ld -T Link.ld ${OBJ} -o kernel.elf

run: os-image.bin
	qemu-system-i386 -fda os-image.bin


debug: os-image.bin kernel.elf
	qemu-system-i386 -s -fda os-image.bin -d guest_errors,int &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"


%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.s
	nasm $< -f elf -o $@

%.bin: %.s
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o kernel/cpu/*.o libc/*.o
