#ifndef SHADER_H
#define SHADER_H
#include "../core/Itypes.h"
#include "framebuffer.h"
#include "../core/Imath.h"


u32 packer(vec3f col);
vec3f shade(float x, float y, double t);
void render(framebuffer * FB, double t);

#endif
