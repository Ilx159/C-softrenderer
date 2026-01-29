#include "framebuffer.h"

void fb_clear(framebuffer *FB, uint32_t color){
  u32 max = FB->h * FB->w;
  for(u32 i = 0; i < max; i++){
      FB->data[i] = color;
  }
}

void sfb_set_pixel(framebuffer *FB, u32 x, u32 y, u32 color){
  if(x >= FB->w || y >= FB->h) return;
  FB->data[x + y*FB->w] = color;
};

//return 0 if you try to get a pixel that is not in the correct framebuffer's w,h  

u32 sfb_get_pixel(framebuffer *FB, u32 x, u32 y){
  if(x >= FB->w || y >= FB->h) return 0;
  return FB->data[x + y*FB->w];
};

// needs thex and y fit in the width and heigh of the framebuffer

void fb_set_pixel(framebuffer *FB, u32 x, u32 y, u32 color){
  FB->data[x + y*FB->w] = color;
};

u32 fb_get_pixel(framebuffer *FB, u32 x, u32 y){
  return FB->data[x + y*FB->w];
};
