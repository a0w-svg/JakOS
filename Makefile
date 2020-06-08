#Sources files compile
C_SOURCES = $(wildcard kernel/*.c drivers/*.c kernel/cpu/*.c  libc/*.c common/*.c kernel/mm/*.c drivers/ports/*.c kernel/time/*.c)
#Headers files list
HEADERS = $(wildcard kernel/include/*.h drivers/include/*.h kernel/cpu/include/*.h libc/include/*.h common/*.h boot/*.h kernel/mm/include/*.h drivers/ports/include/*.h kernel/time/include/*.h)
#compiled files .o
OBJ = ${C_SOURCES:.c=.o kernel/cpu/interrupts.o} 
#add macro to the cross compiler
CC =i686-elf-gcc
#add macro to the debugger
GDB = i686-elf-gdb
#GCC flags
CFLAGS = -g -ffreestanding -Wall -Wextra -fno-exceptions -m32

#create bootable file 
kernel.bin: boot/boot.o ${OBJ}
	i686-elf-ld  $^ -T Link.ld -o kernel.bin

#create file
kernel.elf: boot/boot.o ${OBJ}
	i686-elf-ld -T Link.ld ${OBJ} -o kernel.elf

#run compiled image
run: kernel.bin
	qemu-system-i386 -kernel kernel.bin -soundhw pcspk -serial file:CON

#debug compiled image
run-iso: 
		qemu-system-i386 -cdrom JakOS.iso -soundhw pcspk -serial file:CON
build-iso: kernel.bin menu.lst
	mkdir -p iso/boot/grub              # create the folder structure
	cp stage2_eltorito iso/boot/grub/   # copy the bootloader
	cp kernel.bin iso/boot/     
	cp menu.lst iso/boot/grub           # copy the grub configuration file
	mkisofs -R                              \
	  -b boot/grub/stage2_eltorito    \
	  -no-emul-boot                   \
	  -boot-load-size 4               \
	  -A os                           \
	  -input-charset utf8             \
	  -quiet                          \
	 -boot-info-table                \
	  -o JakOS.iso                       \
	  iso
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
	rm -rf *.bin *.dis *.o JakOS.iso *.

	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o kernel/cpu/*.o libc/*.o kernel/mm/*.o
