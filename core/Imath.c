#include "Imath.h"
#include "math.h"
#include "Itypes.h"

static float sin_lut[SIN_LENGTH];

void imath_init(void){
  for(int i = 0; i < SIN_LENGTH; i++)
  sin_lut[i] = sin(((float)i*PI)/180);
}

float Isin(u16 a){
  a = a % 360;
  return sin_lut[a];
}

float Icos(u16 a){
  a += 90;
  a = a % 360;  
  return sin_lut[a];
}

void interpolate(vec2i vec1, vec2i vec2, u16 *x, u16 size){
  if (size < vec2.y - vec1.y) return;
  if (vec1.y == vec2.y) return;
  float slope = ((float)(vec2.x - vec1.x)/(float)(vec2.y - vec1.y));
  for(u16 i = vec1.y, j = 0; i < vec2.y; i++, j++){
    x[j] = (u16)roundf((float)(i - vec1.y)*(slope) + (float)vec1.x); 
  }
}
