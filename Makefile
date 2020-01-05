CC     = g++
LD     = ld
NASM   = nasm
CFLAGS = -g -m32 -ffreestanding -Ikernel -fno-pie -fno-stack-protector 
OUT    = out

LOW_LEVEL  = $(OUT)/string.o $(OUT)/print.o $(OUT)/keys.o 
HIGH_LEVEL = $(OUT)/ddprint.o $(OUT)/ddstring.o $(OUT)/ddobject.o

############
# ALL
#
all: disk.img

run: disk.img
	qemu-system-i386 -drive file=$<,format=raw

debug: disk.img
	qemu-system-i386 -fda $< -S -s &
		gdb $(OUT)/kernel.bin  \
		-ex 'target remote localhost:1234' \
		-ex 'layout src' \
		-ex 'layout reg' \
		-ex 'break main' \
		-ex 'continue'
############

############
# IMAGE
#
disk.img: $(OUT)/bootloader.bin $(OUT)/kernel.bin
	@echo "IMAGE " $@
	@dd if=/dev/zero of=$@ bs=512 count=2880 > /dev/null 2>&1
	@dd if=$(OUT)/bootloader.bin of=$@ bs=512 conv=notrunc > /dev/null 2>&1
	@dd if=$(OUT)/kernel.bin of=$@ bs=512 seek=1 conv=notrunc > /dev/null 2>&1
	@fdisk -l $@
############

############
# KERNEL
#
$(OUT)/kernel.bin: $(OUT)/entry.o $(LOW_LEVEL) $(HIGH_LEVEL) $(OUT)/kernel.o
	@echo "LD    " $@
	@mkdir -p $(OUT)
	@$(LD) -Ttext 0x1000 -T link.ld --oformat binary -m elf_i386 -o $@ $^
	@ls -al $@

$(OUT)/%.o: kernel/%.cpp
	@echo "CC    " $@
	@mkdir -p $(OUT)
	@$(CC) -c $^ -o $@ $(CFLAGS)

$(OUT)/entry.o: kernel/entry.asm
	@echo "NASM  " $@
	@mkdir -p $(OUT)
	@$(NASM) $^ -f elf -o $@

$(OUT)/%.o: kernel/%.c
	@echo "CC    " $@
	@mkdir -p $(OUT)
	@$(CC) -c $^ -o $@ $(CFLAGS)
############

############
# BOOTLOADER
#
$(OUT)/bootloader.bin: bootloader/bootloader.asm
	@echo "NASM  " $@
	@mkdir -p $(OUT)
	@$(NASM) $^ -f bin -o $@
	@ls -al $@
############

############
# CLEAN
#
clean:
	@echo "CLEAN  " $(OUT)/kernel.bin $(OUT)/entry.o $(OUT)/kernel.o $(LOW_LEVEL) $(HIGH_LEVEL)
	@rm -f  $(OUT)/kernel.bin $(OUT)/entry.o $(OUT)/kernel.o $(LOW_LEVEL) $(HIGH_LEVEL)
	@echo "CLEAN  " $(OUT)/bootloader.bin
	@rm -f $(OUT)/bootloader.bin
	@echo "CLEAN  " disk.img
	@rm -f disk.img
############
