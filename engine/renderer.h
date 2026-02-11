#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../gfx/framebuffer.h"


typedef struct{

  char name[64];

  framebuffer *frontbuffer;
  framebuffer *backbuffer;

  u16 ext_width;
  u16 ext_height;
  u16 int_width;
  u16 int_height;

}window;

typedef struct {

    bool (*pinit)(window *win);
    void (*pprocess)(window *win, void(*to_render)(window *win));
    void (*pstop)(window *win);

} rendererAPI;

void set_API(rendererAPI API);
void process(window *win, void(*to_render)(window *win));
bool init(window *win);
void stop(window *win);

#endif
