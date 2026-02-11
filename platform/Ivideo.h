#ifndef VIDEO_H
#define VIDEO_H

#include "multiboot.h"
#include <stdint.h>
#include <stdint.h>
#include "string.h"


extern void *framebuffer;
extern uint32_t screen_width;
extern uint32_t screen_height;
extern uint32_t screen_size;
extern uint32_t screen_pitch;
extern uint32_t screen_bpp;


void init_video(multiboot_info_t *mbi);
void draw_pixel(int x, int y, uint32_t color);
void draw_char(int x, int y, char c, uint32_t color);
void draw_string(int x, int y, const char *str, uint32_t color);
void clear_screen(uint32_t color);
void refresh_screen();

#endif
