# --------- CONFIGS ---------
gccparams = -m32 -ffreestanding -nostdlib -fno-builtin \
         -fno-stack-protector -fno-pic \
         -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables

nasmparams = -f elf32
ldparams   = -m elf_i386

src_dir = src
obj_dir = obj
out_dir = out

objs = \
	$(obj_dir)/kernel-entry.o \
	$(obj_dir)/kernel.o \
	$(obj_dir)/port.o \
	$(obj_dir)/video.o \
	$(obj_dir)/time.o \
	$(obj_dir)/speaker.o \
	$(obj_dir)/tiles.o \
	$(obj_dir)/render.o \
	$(obj_dir)/string.o \
	$(obj_dir)/text.o \
	$(obj_dir)/gui.o \
	$(obj_dir)/stdlib.o \

# --------- TARGET RULES ---------
compile:
	rm -rf $(out_dir) $(obj_dir)
	mkdir -p $(out_dir) $(obj_dir)

	# assemble kernel entrypoint
	nasm $(nasmparams) $(src_dir)/kernel-entry.asm -o $(obj_dir)/kernel-entry.o

	# assemble stage1 MBR (raw bin)
	nasm -f bin -i $(src_dir)/ $(src_dir)/mbr.asm -o $(out_dir)/mbr.bin

	# assemble stage2 bootloader
	nasm -f bin -i $(src_dir)/ $(src_dir)/stage2.asm -o $(out_dir)/stage2.bin

	# compile c files
	gcc $(gccparams) -c $(src_dir)/kernel.c -o $(obj_dir)/kernel.o
	gcc $(gccparams) -c $(src_dir)/port.c -o $(obj_dir)/port.o
	gcc $(gccparams) -c $(src_dir)/time.c -o $(obj_dir)/time.o
	gcc $(gccparams) -c $(src_dir)/video.c -o $(obj_dir)/video.o
	gcc $(gccparams) -c $(src_dir)/speaker.c -o $(obj_dir)/speaker.o
	gcc $(gccparams) -c $(src_dir)/tiles.c -o $(obj_dir)/tiles.o
	gcc $(gccparams) -c $(src_dir)/render.c -o $(obj_dir)/render.o
	gcc $(gccparams) -c $(src_dir)/string.c -o $(obj_dir)/string.o
	gcc $(gccparams) -c $(src_dir)/text.c -o $(obj_dir)/text.o
	gcc $(gccparams) -c $(src_dir)/gui.c -o $(obj_dir)/gui.o
	gcc $(gccparams) -c $(src_dir)/stdlib.c -o $(obj_dir)/stdlib.o

	# link into ELF
	ld $(ldparams) -T linker.ld -o $(out_dir)/kernel.elf $(objs)

	# flatten to binary
	objcopy -O binary -j .text -j .rodata -j .data out/kernel.elf out/kernel.bin

	# pad kernel to 512-sector align
	@actual_size=$$(stat -c%s $(out_dir)/kernel.bin); \
	pad_size=$$(( (512 - ($$actual_size % 512)) % 512 )); \
	dd if=/dev/zero bs=1 count=$$pad_size >> $(out_dir)/kernel.bin 2>/dev/null

	# pad kernel to 512-sector align
	@actual_size=$$(stat -c%s $(out_dir)/stage2.bin); \
	pad_size=$$(( (512 - ($$actual_size % 512)) % 512 )); \
	dd if=/dev/zero bs=1 count=$$pad_size >> $(out_dir)/stage2.bin 2>/dev/null

	# combine mbr + stage2 + kernel
	cat $(out_dir)/mbr.bin $(out_dir)/stage2.bin $(out_dir)/kernel.bin > $(out_dir)/os-image.img

# --------- RUNNING ---------
run: compile 
	qemu-system-i386 -drive format=raw,file=$(out_dir)/os-image.img -M pc -serial stdio -no-reboot -no-shutdown


# --------- CLEAN ---------
clean:
	rm -rf $(obj_dir) $(out_dir)
