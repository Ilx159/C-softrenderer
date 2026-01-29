#include "shader.h"

u32 packer(vec3f col){ //mudar para argb32_t
  col.x = clampf(col.x, 0, 1);
  col.y = clampf(col.y, 0, 1);
  col.z = clampf(col.z, 0, 1);
  argb32_t color;
  color.c.a = 255;
  color.c.b = (u8)(col.z*255);
  color.c.r = (u8)(col.x*255);
  color.c.g = (u8)(col.y*255);
return color.data;
}

void render(framebuffer * restrict FB, double t){

 u32 * restrict pixel_ptr = FB->data;
 float invW = 1.0f/FB->w;
 float invH = 1.0f/FB->h;

 for(u16 j = 0; j < FB->h; j++){
    for(u16 i = 0; i < FB->w; i++){
      
      float x = invW * (i + 0.5f);
      float y = invH * (j + 0.5f);

      param p;
      *pixel_ptr = packer(shade(x, y, t, p));
      pixel_ptr++; 
    }
  }
}
