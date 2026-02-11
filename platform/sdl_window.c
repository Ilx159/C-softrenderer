#include "sdl_window.h"
  
SDL_Window *gwindow;
SDL_Renderer *grenderer;
SDL_Texture *gtexture;
SDL_Event gevent;
bool running = 0;


void SDLprocess(window *win, void(*to_render)(window *win)){

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
      double fps = frames/ acc;
      printf("FPS: %.1f\n", fps);
      acc = 0.0;
      frames = 0;
    }


    while (SDL_PollEvent(&gevent)) {
        if (gevent.type == SDL_QUIT) {
            running = false;
        }
    }

    to_render(win);

    u32 *temp = win->backbuffer->data;
    win->backbuffer->data = win->frontbuffer->data;
    win->frontbuffer->data = temp;
        
    SDL_UpdateTexture(gtexture, NULL, win->frontbuffer->data, win->int_width * sizeof(u32));
    SDL_RenderCopy(grenderer, gtexture, NULL, NULL);
    SDL_RenderPresent(grenderer);

}return;
}



bool SDLinit(window *win){

  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    printf("erro: %s\n", SDL_GetError());
    return(false);
  }

  gwindow = SDL_CreateWindow("?", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, win->ext_width, win->ext_height, SDL_WINDOW_SHOWN);

  if(gwindow == NULL) {
    printf("erro: %s\n", SDL_GetError());
    return(false);
  }

  grenderer = SDL_CreateRenderer(gwindow, -1, 0);

  if(grenderer == NULL){
    printf("erro: %s\n", SDL_GetError());
    return(false);
  }

  gtexture = SDL_CreateTexture(grenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, win->int_width, win->int_height);

  if(gtexture == NULL){
    printf("erro: %s\n", SDL_GetError());
    return(false);
  }
  
  running = 1;
  return true;
}

void SDLstop(window *win){

  
  SDL_DestroyTexture(gtexture);
  SDL_DestroyRenderer(grenderer);

  SDL_DestroyWindow(gwindow);
  gwindow = NULL;

  SDL_Quit();
}



