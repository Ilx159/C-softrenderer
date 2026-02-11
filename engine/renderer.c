#include "renderer.h"

static rendererAPI gAPI;

void set_API(rendererAPI API){
  gAPI = API;
}

bool init(window *win){

  if(!gAPI.pinit(win)) return true;

   
  win->backbuffer = malloc(sizeof(framebuffer));
  win->frontbuffer = malloc(sizeof(framebuffer));

  win->backbuffer->h = (u16)win->int_height;
  win->backbuffer->w = (u16)win->int_width;
  win->frontbuffer->h = (u16)win->int_height;
  win->frontbuffer->w = (u16)win->int_width;

  win->backbuffer->data = malloc(sizeof(u32)* win->backbuffer->w * win->backbuffer->h);
  win->frontbuffer->data = malloc(sizeof(u32)* win->frontbuffer->w * win->frontbuffer->h);
  
  if(win->backbuffer->data == NULL){
    printf("erro: malloc falhou");
    return(1);
  }

  if(win->frontbuffer->data == NULL){
    printf("erro: malloc falhou");
    return(1);
  }

  return 0;

}

void stop(window *win){

  gAPI.pstop(win);

  free(win->frontbuffer->data);
  free(win->backbuffer->data);
  win->backbuffer->data = NULL;
  win->frontbuffer->data = NULL;
  free(win->frontbuffer);
  free(win->backbuffer);
}

void process(window *win, void(*to_render)(window *win)){
  gAPI.pprocess(win, to_render);
}

