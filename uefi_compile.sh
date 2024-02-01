gcc -Ignu-efi-dir/inc -fpic -ffreestanding -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone -maccumulate-outgoing-args -c uefihelloworld.c -o main.o
ld -shared -Bsymbolic -L/usr/lib -T/usr/lib/elf_x86_64_efi.lds /usr/lib/crt0-efi-x86_64.o main.o -o main.so -lgnuefi -lefi
objcopy -j .text -j .sdata -j .data -j .dynamic -j .dynsym  -j .rel -j .rela -j .rel.* -j .rela.* -j .reloc --target efi-app-x86_64 --subsystem=10 main.so bootx64.efi

gcc -c -Wall -Wextra -I../include -I../bin/include -nostdlib -fno-builtin -fPIE -o kernel.o main.c
ld kernel.o --entry kernel_main -Map kernel.map -pie -o kernel.bin

