#ifndef ITYPES_H
#define ITYPES_H

#include <stdint.h>

typedef uint16_t u16;
typedef uint32_t u32;
typedef uint8_t u8;
typedef uint64_t u64;

typedef union {
u32 data;
struct {
  u8 b;
  u8 g;
  u8 r;
  u8 a;
} c;
}argb32_t;

typedef struct {
  u16 x, y;
} vec2i;

typedef struct {
  float x, y;
}vec2f;

typedef struct {
  float x, y, z;
} vec3f;

typedef struct {
  u16 x, y, z;
} vec3i;

typedef struct {
  u16 w, x, y, z;
} vec4i;

typedef struct {
  float w, x, y, z;
} vec4f;

#endif
