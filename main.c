#include "core/Itypes.h"
#include "core/Imath.h"
#include "gfx/raster.h"
#include "gfx/shader.h"
#include "engine/renderer.h"
#include "platform/sdl_window.h"

void to_render(window *win);

int main(){
  printf("main() started\n");

  window win;

  win.ext_height = 600;
  win.ext_width = 800;
  win.int_height = win.ext_height/4;
  win.int_width = win.ext_width/4;
  rendererAPI API = {
    .pprocess = SDLprocess,
    .pinit = SDLinit,
    .pstop = SDLstop,
  };

  set_API(API);

  printf("API seted.\n");
  
  
  imath_init();
  printf("imath_init().\n");

  init(&win);
  printf("init(&win).\n");
  





//
        
 //   double time = SDL_GetTicks();

 



  process(&win, to_render); 

  stop(&win);

  return 0;
}

void to_render(window *win){

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

  render(win->backbuffer, 0.0f);
  draw_triangle(win->backbuffer, &tri1);
  draw_triangle(win->backbuffer, &tri2);
  draw_triangle(win->backbuffer, &tri3);
};
