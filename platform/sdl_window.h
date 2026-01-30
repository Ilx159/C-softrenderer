#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include "../core/Itypes.h"
#include "../gfx/framebuffer.h"

typedef struct{

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  SDL_Event event;
  
  char name[64];

  framebuffer *frontbuffer;
  framebuffer *backbuffer;

  u16 ext_width;
  u16 ext_height;
  u16 int_width;
  u16 int_height;

}window;

void process_events(window *win);

bool init(window *win);

void stop(window *win);


#endif
