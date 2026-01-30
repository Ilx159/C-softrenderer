#include "gfx/framebuffer.h"
#include "platform/sdl_window.h"
#include "core/Itypes.h"
#include "core/Imath.h"
#include "gfx/raster.h"
#include "gfx/shader.h"

int main(){

  window win;
  win.ext_height = 600;
  win.ext_width = 800;
  win.int_height = win.ext_height/4;
  win.int_width = win.ext_width/4;
  
  imath_init();
  init(&win);
  bool running = 1;
  
  triangle tri1;
  tri1.points[0] = (vec2i){3,7};
  tri1.points[1] = (vec2i){0, 0};
  tri1.points[2] = (vec2i){0, 15};
  tri1.color.data = 0xFF00FFFF;

  triangle tri2;
  tri2.points[0] = (vec2i){3,7};
  tri2.points[1] = (vec2i){0, 0};
  tri2.points[2] = (vec2i){10, 5};
  tri2.color.data = 0xFFFFFF00;

  triangle tri3;
  tri3.points[0] = (vec2i){3,7};
  tri3.points[1] = (vec2i){0, 15};
  tri3.points[2] = (vec2i){10, 5};
  tri3.color.data = 0xFFFF00FF;


  while(running){

    u8 speed = 2;
    static u64 last = 0;
    static double acc = 0.0;
    static int frames = 0;
    u64 now = SDL_GetPerformanceCounter();
    u64 freq = SDL_GetPerformanceFrequency();
    if (!last) last = now;
    double dt = (double)(now - last) / freq;
    last = now;
    acc += dt;
    frames++;

    if (acc >= 1.0) {
      double fps = frames / acc;
      printf("FPS: %.1f\n", fps);
      acc = 0.0;
      frames = 0;
    }


    while (SDL_PollEvent(&win.event)) {
        if (win.event.type == SDL_QUIT) {
            running = false;
        }
    }
    
 //   double time = SDL_GetTicks();
    
    render(win.backbuffer, 0.0f);
    draw_triangle(win.backbuffer, &tri1);
    draw_triangle(win.backbuffer, &tri2);
    draw_triangle(win.backbuffer, &tri3);
    u32 *temp = win.backbuffer->data;
    win.backbuffer->data = win.frontbuffer->data;
    win.frontbuffer->data = temp;
        
    SDL_UpdateTexture(win.texture, NULL, win.frontbuffer->data, win.int_width * sizeof(u32));
    SDL_RenderCopy(win.renderer, win.texture, NULL, NULL);
    SDL_RenderPresent(win.renderer);

  }
  
  stop(&win);

  return 0;
}
