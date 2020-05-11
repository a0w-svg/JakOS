    OBJECTS =kmain.o boot.o  common.o screen.o utils.o  isr.o idt.o interrupts.o
    CC = i686-elf-gcc
    CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
             -nostartfiles -nodefaultlibs -Wall  -Wextra  -c
    LDFLAGS = -T Link.ld -melf_i386
    AS = nasm
    ASFLAGS = -f elf

    all: kernel.bin

    kernel.bin: $(OBJECTS)
		ld $(LDFLAGS) $(OBJECTS) -o kernel.bin
 
    run: kernel.bin
		qemu-system-i386 -kernel kernel.bin

    %.o: %.c
		$(CC) $(CFLAGS)  $< -o $@

    %.o: %.s
		$(AS) $(ASFLAGS) $< -o $@

    clean:
		rm -rf *.o kernel.bin 
