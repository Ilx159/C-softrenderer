#ifndef RASTER_H
#define RASTER_H

#include "../core/Itypes.h"
#include "../core/Imath.h"
#include "framebuffer.h"

typedef struct{

  vec2i points[3];
  argb32_t color;

} triangle;

typedef struct{

  vec2i points[2];
  argb32_t color;

} rectangle;

void draw_rectangle(framebuffer *FB ,rectangle *rec);
void draw_triangle(framebuffer *FB ,triangle *tri);
void lowLine(framebuffer *FB,u32 x1, u32 y1, u32 x2, u32 y2, u32 color);
void highLine(framebuffer *FB,int x1, int y1, int x2, int y2, u32 color);
void line(framebuffer *FB,int x1, int y1, int x2, int y2, u32 color);

#endif
