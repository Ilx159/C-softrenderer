#ifndef IMATH_H
#define IMATH_H
#include "Itypes.h"
#define SIN_LENGTH 360
#define PI (355.0f/113.0f)

void imath_init(void);
float Isin(u16 a);
float Icos(u16 a);

static inline float clampf(float x, float min, float max){
  if(x < min) return min;
  if(x > max) return max;
  return x;
}

static inline u8 clampi(u8 x, u8 min, u8 max){
  if(x < min) return min;
  if(x > max) return max;
  return x;
}

static inline float absf(float x){
  return x < 0 ? -x : x;
}

void interpolate(vec2i vec1, vec2i vec2, u16 *x, u16 size);
#endif
