#ifndef NPG_XORROSHIRO128_H_
#define NPG_XORROSHIRO128_H_

#include <stdint.h>



static inline uint16_t Rotl(const uint16_t x, int k);
void Seed(uint16_t seed);
uint16_t Next(void);
void GenerateRandomArray(uint16_t array_size, uint16_t random_array[]);

#endif  // XOROSHIRO128_H
