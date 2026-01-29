#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "../core/Itypes.h"

typedef struct {
  
  u32 *data;
  u16 w, h;

} framebuffer;

void fb_clear(framebuffer *FB, uint32_t color);

void fb_set_pixel(framebuffer *FB, u32 x, u32 y, u32 color);

u32 fb_get_pixel(framebuffer *FB, u32 x, u32 y);

void sfb_set_pixel(framebuffer *FB, u32 x, u32 y, u32 color);

u32 sfb_get_pixel(framebuffer *FB, u32 x, u32 y);
#endif
