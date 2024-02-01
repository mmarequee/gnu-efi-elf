dd if=/dev/zero of=floppy.img bs=1k count=1440
mformat -i floppy.img -f 1440 ::
mmd -i floppy.img ::/EFI
mmd -i floppy.img ::/EFI/BOOT
mcopy -i floppy.img bootx64.efi ::/EFI/BOOT
mcopy -i floppy.img kernel.bin ::/

