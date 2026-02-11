#include "raster.h"
#include <stdlib.h> //future: remove that dependency


void draw_rectangle(framebuffer *FB ,rectangle *rec){
  
  if(rec->points[0].x > rec->points[1].x){
    u16 temp = rec->points[0].x;
    rec->points[0].x = rec->points[1].x;
    rec->points[1].x = temp;
  }

  if(rec->points[0].y > rec->points[1].y){
    u16 temp = rec->points[0].y;
    rec->points[0].y = rec->points[1].y;
    rec->points[1].y = temp;
  }

  for(u16 i = rec->points[0].y; i <= rec->points[1].y; i++){
    for(u16 j = rec->points[0].x; j <= rec->points[1].x; j++){
      sfb_set_pixel(FB, j, i, rec->color.data);
    }
  }
}

void draw_triangle(framebuffer *FB ,triangle *tri){ //raster_lr *edges add later

  if (tri->points[1].y < tri->points[0].y){
    vec2i temp = tri->points[0];
    tri->points[0] = tri->points[1];
    tri->points[1] = temp;
  }
  if (tri->points[2].y < tri->points[0].y){
    vec2i temp = tri->points[0];
    tri->points[0] = tri->points[2];
    tri->points[2] = temp;
  }
  if (tri->points[2].y < tri->points[1].y){
    vec2i temp = tri->points[1];
    tri->points[1] = tri->points[2];
    tri->points[2] = temp;
  }

  u16 x2side_size = tri->points[2].y - tri->points[0].y;
  if(x2side_size == 0){
    return;
  }
  else {
  u16 *x2side = malloc(sizeof(u16) * x2side_size);
  interpolate(tri->points[0], tri->points[2], x2side, x2side_size);
  
  u16 x1side1_size = tri->points[2].y - tri->points[1].y;
  u16 x1side2_size = tri->points[1].y - tri->points[0].y;
  
  u16 *x1side1 = malloc(sizeof(u16) * x1side1_size);
  u16 *x1side2 = malloc(sizeof(u16) * x1side2_size);

  interpolate(tri->points[1], tri->points[2], x1side1, x1side1_size);
  interpolate(tri->points[0], tri->points[1], x1side2, x1side2_size);

  u16 *x1side = malloc(sizeof(u16) * x2side_size);
 
  for(u16 i = 0; i < x1side2_size; i++){
    x1side[i] = x1side2[i];
  }
  
  for(u16 i = 0; i < x1side1_size; i++){
    x1side[i + x1side2_size] = x1side1[i];
  }

  u16 midle = (x2side_size)/2;
  u16 *xleft;
  u16 *xright;

  if(x2side[midle] < x1side[midle]){
    xleft = x2side;
    xright = x1side;
  } else {
    xleft = x1side;
    xright = x2side;
  }

  for(u16 i = 0; i < x2side_size; i++){
    for (int x = xleft[i]; x <= xright[i]; x++)
      sfb_set_pixel(FB, x, i + tri->points[0].y, tri->color.data);
    }


    free(x2side);
    free(x1side);
    free(x1side2);
    free(x1side1);

  }

}

void lowLine(framebuffer *FB,u32 x1, u32 y1, u32 x2, u32 y2, u32 color){
  int dx = x2-x1;
  int dy = y2-y1;
  int yi = 1;
  if(dy < 0){
    yi = -1;
    dy = -dy;
  }
  int De = 2*dy - dx;
  int y = y1;
  for(int i = x1; i != x2; i += (x1 < x2) ? 1 : -1){
    sfb_set_pixel(FB, i, y, color);
    if(De > 0){
      y += yi;
      De += 2*(dy-dx);
    } else
      De += 2*dy;
  }
}

void highLine(framebuffer *FB,int x1, int y1, int x2, int y2, u32 color){
  int dx = x2-x1;
  int dy = y2-y1;
  int xi = 1;
  if(dx<0){
    xi = -1;
    dx = -dx;
  }
  int De = 2*dx - dy;
  int x = x1;
  for(int i = y1; i != y2; i += (y1 < y2) ? 1 : -1){
    sfb_set_pixel(FB, x, i, color);
    if(De > 0){
      x += xi;
      De += 2*(dx-dy);
    } else
      De += 2*dx;
  }
}
void line(framebuffer *FB,int x1, int y1, int x2, int y2, u32 color){
  if((y2-y1) < (x2 - x1)){
    if(x1 > x2)
      lowLine(FB,x2,y2,x1,y1,color);
    else
     lowLine(FB,x1,y1,x2,y2,color);
  }
  else {
    if(y1 > y2)
      highLine(FB,x2,y2,x1,y1,color);
    else
      highLine(FB,x1,y1,x2,y2,color);
  }
}
