#include "sdl_window.h"

void process_events(window *win);

bool init(window *win){

  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    printf("erro: %s\n", SDL_GetError());
    return(1);
  }

  win->window = SDL_CreateWindow("?", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, win->ext_width, win->ext_height, SDL_WINDOW_SHOWN);

  if(win->window == NULL) {
    printf("erro: %s\n", SDL_GetError());
    return(1);
  }

  win->renderer = SDL_CreateRenderer(win->window, -1, 0);

  if(win->renderer == NULL){
    printf("erro: %s\n", SDL_GetError());
    return(1);
  }

  win->texture = SDL_CreateTexture(win->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, win->int_width, win->int_height);

  if(win->texture == NULL){
    printf("erro: %s\n", SDL_GetError());
    return(1);
  }
 
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

  free(win->frontbuffer->data);
  free(win->backbuffer->data);
  win->backbuffer->data = NULL;
  win->frontbuffer->data = NULL;
  
  SDL_DestroyTexture(win->texture);
  SDL_DestroyRenderer(win->renderer);

  SDL_DestroyWindow(win->window);
  win->window = NULL;

  SDL_Quit();
}



