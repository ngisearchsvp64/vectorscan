#ifndef PRINT_SIMD_H
#define PRINT_SIMD_H

#include <stdio.h>
#include <stdint.h>
/*
static inline void print_u8x8_nocr(const char *label, __m128i vec) {
  int i;
  uint8_t __attribute__((aligned(16))) data[8];
  vst1_u8(data, vec);
  printf("%20s: ", label);
  for(i=7; i >=0; i--)
    printf("%02x ", data[i]);
}

static inline void print_u16x4_nocr(const char *label, __m128i vec) {
  int i;
  uint16_t __attribute__((aligned(16))) data[4];
  vst1_u16(data, vec);
  printf("%20s: ", label);
  for(i=3; i >= 0; i--)
    printf("%04x ", data[i]);
}

static inline void print_u32x2_nocr(const char *label, uint32x2_t vec) {
  int i;
  uint32_t __attribute__((aligned(16))) data[2];
  vst1_u32(data, vec);
  printf("%20s: ", label);
  for(i=1; i >= 0; i--)
    printf("%08x ", data[i]);
}

static inline void print_u64x1_nocr(const char *label, uint64x1_t vec) {
  uint64_t __attribute__((aligned(16))) data[1];
  vst1_u64(data, vec);
  printf("%20s: ", label);
  printf("%016lx ", data[0]);
}*/

static inline void print_u8x16_nocr(const char *label, __m128i vec) {
  int i;
  uint8_t __attribute__((aligned(16))) data[16];
  _mm_store_si128((__m128i*) data, vec);
  printf("%20s: ", label);
  for(i=15; i >=0; i--)
    printf("%02x ", data[i]);
}


static inline void print_u16x8_nocr(const char *label, __m128i vec) {
  int i;
  uint16_t __attribute__((aligned(16))) data[8];
  _mm_store_si128((__m128i*) data, vec);
  printf("%20s: ", label);
  for(i=7; i >= 0; i--)
    printf("%04x ", data[i]);
}

static inline void print_u32x4_nocr(const char *label, __m128i vec) {
  int i;
  uint32_t __attribute__((aligned(16))) data[4];
  _mm_store_si128((__m128i*) data, vec);
  printf("%20s: ", label);
  for(i=3; i >= 0; i--)
    printf("%08x ", data[i]);
}

static inline void print_u64x2_nocr(const char *label, __m128i vec) {
  int i;
  uint64_t __attribute__((aligned(16))) data[2];
  _mm_store_si128((__m128i*) data, vec);
  printf("%20s: ", label);
  for(i=1; i >= 0; i--)
    printf("%016lx ", data[i]);
}
/*
static inline void print_u8x8(const char *label, __m128i vec) {
  print_u8x8_nocr(label, (uint8x8_t)vec);
  printf("\n");
}

static inline void print_u16x4(const char *label, uint16x4_t vec) {
  print_u16x4_nocr(label, (uint16x4_t)vec);
  printf("\n");
}

static inline void print_u32x2(const char *label, uint32x2_t vec) {
  print_u32x2_nocr(label, (uint32x2_t)vec);
  printf("\n");
}

static inline void print_u64x1(const char *label, uint64x1_t vec) {
  print_u64x1_nocr(label, (uint64x1_t)vec);
  printf("\n");
}*/

static inline void print_u8x16(const char *label, __m128i vec) {
  print_u8x16_nocr(label, vec);
  printf("\n");
}

static inline void print_u16x8(const char *label, __m128i vec) {
  print_u16x8_nocr(label, vec);
  printf("\n");
}

static inline void print_u32x4(const char *label, __m128i vec) {
  print_u32x4_nocr(label, vec);
  printf("\n");
}

static inline void print_u64x2(const char *label, __m128i vec) {
  print_u64x2_nocr(label, vec);
  printf("\n");
}
/*
static inline void print_s8x8_nocr(const char *label, int8x8_t vec) {
  print_u8x8_nocr(label, vec);
}
static inline void print_s16x4_nocr(const char *label, int16x4_t vec) {
  print_u16x4_nocr(label, (uint16x4_t)vec);
}
static inline void print_s32x2_nocr(const char *label, int32x2_t vec) {
  print_u32x2_nocr(label, (uint32x2_t)vec);
}
static inline void print_s64x1_nocr(const char *label, int64x1_t vec) {
  print_u64x1_nocr(label, (uint64x1_t)vec);
}*/

static inline void print_s8x16_nocr(const char *label, __m128i vec) {
  print_u8x16_nocr(label, vec);
}
static inline void print_s16x8_nocr(const char *label, __m128i vec) {
  print_u16x8_nocr(label, vec);
}
static inline void print_s32x4_nocr(const char *label, __m128i vec) {
  print_u32x4_nocr(label, vec);
}
static inline void print_s64x2_nocr(const char *label, __m128i vec) {
  print_u64x2_nocr(label, vec);
}
/*
static inline void print_s8x8(const char *label, int8x8_t vec) {
  print_u8x8(label, (uint8x8_t)vec);
}
static inline void print_s16x4(const char *label, int16x4_t vec) {
  print_u16x4(label, (uint16x4_t)vec);
}
static inline void print_s32x2(const char *label, int32x2_t vec) {
  print_u32x2(label, (uint32x2_t)vec);
}
static inline void print_s64x1(const char *label, int64x1_t vec) {
  print_u64x1(label, (uint64x1_t)vec);
}*/

static inline void print_s8x16(const char *label, __m128i vec) {
  print_u8x16(label, vec);
}
static inline void print_s16x8(const char *label, __m128i vec) {
  print_u16x8(label, vec);
}
static inline void print_s32x4(const char *label, __m128i vec) {
  print_u32x4(label, vec);
}
static inline void print_s64x2(const char *label, __m128i vec) {
  print_u64x2(label, vec);
}

#endif // PRINT_SIMD_H
