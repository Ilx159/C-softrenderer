#include "video.h"
#include "multiboot.h"

extern unsigned char _binary_src_drivers_font_psf_start[];
#define _binary_font_psf_start _binary_src_drivers_font_psf_start
typedef struct {
  uint32_t magic, version, headersize, flags, numglyph, bytesperglyph, height,
      width;
} PSF2_header;
typedef struct {
  uint16_t magic;
  uint8_t mode, charsize
} PSF1_header;

void init_video(multiboot_info_t *mbi){

  framebuffer = (uint32_t *)(mbi->framebuffer_addr);
  screen_width = mbi->framebuffer_width;
  screen_height = mbi->framebuffer_height;
  screen_size = screen_pitch * screen_height;
  screen_bpp = mbi->framebuffer_bpp;
  screen_pitch = mbi->framebuffer_pitch;
}

void draw_pixel(int x, int y, uint32_t color) {
  if (x <  0 || x >= screen_width || y < 0 || y >= screen_height)
    return;
  uint32_t bytespp = screen_bpp / 8;
  uint8_t* row = (uint8_t*)framebuffer + y * screen_pitch;
  *(uint32_t*)(row + x * bytespp) = color;
}

void draw_char(int x, int y, char c, uint32_t color) {
  unsigned char *glyph;
  uint32_t height, width, bpl;
  PSF2_header *font2 = (PSF2_header *)_binary_font_psf_start;
  if (font2->magic == 0x864ab572) {
    height = font2->height;
    width = font2->width;
    bpl = (width + 7) / 8;
    glyph = _binary_font_psf_start + font2->headersize +
            ((unsigned char)c * font2->bytesperglyph);
  } else {
    PSF1_header *font1 = (PSF1_header *)_binary_font_psf_start;
    height = font1->charsize;
    width = 8;
    bpl = 1;
    glyph = _binary_font_psf_start + sizeof(PSF1_header) +
            ((unsigned char)c * font1->charsize);
  }
  for (uint32_t cy = 0; cy < height; cy++) {
    for (uint32_t cx = 0; cx < width; cx++) {
      if (glyph[cy * bpl + cx / 8] & (0x80 >> (cx % 8)))
        draw_pixel(x + cx, y + cy, color);
    }
  }
}

void draw_string(int x, int y, const char *str, uint32_t color) {
  int sx = x;
  while (*str) {
    if (*str == '\n') {
      x = sx;
      y += 16;
    } else {
      draw_char(x, y, *str, color);
      x += 8;
    }
    str++;
  }
}

void refresh_screen(uint32_t *FB) {
if (!framebuffer)
    return;

  uint8_t* dst = (uint8_t*)framebuffer;
  uint8_t* src = (uint8_t*)FB;

  uint32_t row_bytes = screen_width * (screen_bpp / 8);

  for (uint32_t y = 0; y < screen_height; y++) {
    memcpy(dst + y * screen_pitch,
           src + y * row_bytes,
           row_bytes);
  }
}

void video_clear(uint32_t color) {
    if (!framebuffer) return;

    uint32_t* fb;
    for (uint32_t y = 0; y < screen_height; y++) {
        fb = (uint32_t*)((uint8_t*)framebuffer + y * screen_pitch);
        for (uint32_t x = 0; x < screen_width; x++) {
            fb[x] = color;
        }
    }
}

