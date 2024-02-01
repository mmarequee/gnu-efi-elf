#include <efi/efi.h>
#include <efi/efilib.h>
#include <stdbool.h>
#include "zxfont.h"

typedef struct 
{
  EFI_SYSTEM_TABLE *system;
  //EFI_PHYSICAL_ADDRESS framebuffer;
  VOID *framebuffer;
  UINT32 width;
  UINT32 height;
} BootInfo;

void put_pixel(BootInfo *boot, int x, int y, UINTN color)
{
  *(UINTN *)(boot->framebuffer + 4 * boot->width * y + 4 * x) = color;
}

void kernel_main(BootInfo *boot) 
{
  
  unsigned int x, y, i, j, k;

  for (y = 0; y < boot->height; y++) 
    for (x = 0; x < boot->width; x++) 
      put_pixel(boot, x, y, 0x588888);

  for(k = 0; k < 96; k++) 
    for(i = 0; i < 8; i++)
      for(j = 0; j < 8; j++)
        if((*(unsigned char *)(_font + i + (k << 3)) >> j) & 0x01)
          put_pixel(boot, 8 - j + (k << 3), i, 0x103c08); 
  
  for (x = 0; x < boot->width; x++) 
      put_pixel(boot, x, 2, 0x103c08);
  
  __asm__ __volatile__ ("cli;");
  while (1) __asm__ volatile("hlt");
}
