#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include "../core/Itypes.h"
#include "../gfx/framebuffer.h"
#include "../engine/renderer.h"

void SDLprocess(window *win, void(*to_render)(window *win));

bool SDLinit(window *win);

void SDLstop(window *win);

#endif
