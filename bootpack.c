#include "bootpack.h"

void Main(void) {
  struct BOOTINFO *binfo = (struct BOOTINFO *)ADR_BOOTINFO;
  char s[40], mcursor[256];
  int my = (binfo->scrny - 16) / 2;
  int mx = (binfo->scrnx - 28 - 16) / 2;

  init_gdtidt();
  init_pic();
  io_sti();

  init_palette();
  init_screen(binfo->vram, binfo->scrnx, binfo->scrny);

  mysprintf(s, "(%d, %d) %d", binfo->scrnx, binfo->scrny, 4);
  putfonts8_asc(binfo->vram, binfo->scrnx, 8, 32, COL8_000000, s);
  putfonts8_asc(binfo->vram, binfo->scrnx, 8, 8, COL8_000000, "ABC 123.");
  init_mouse_cursor8(mcursor, COL8_008484);
  putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);

  io_out8(PIC0_IMR, 0xf9);  // PIC1/keyboard 11111001)
  io_out8(PIC1_IMR, 0xef);  // mouse 11101111

  for (;;) {
    io_hlt();
  }
}
