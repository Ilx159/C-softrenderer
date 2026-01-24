#include "Imath.h"
#include "math.h"
#include "Itypes.h"

static float sin_lut[SIN_LENGHT];

void imath_init(void){
  for(int i = 0; i < SIN_LENGHT; i++)
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
