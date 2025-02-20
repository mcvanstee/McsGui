#ifndef UTILS_UTILS_ARRAY_H_
#define UTILS_UTILS_ARRAY_H_

#include <stdint.h>
#include <stddef.h>
#include <math.h>

void utils_array_addUint8(uint8_t *p_array, const uint8_t data, const int32_t index);
void utils_array_addUint16(uint8_t *p_array, const uint16_t data, const int32_t index);
void utils_array_addUint32(uint8_t *p_array, const uint32_t data, const int32_t index);
void utils_array_addInt16(uint8_t *p_array, const int16_t data, const int32_t index);
void utils_array_addFloat(uint8_t *p_array, float_t number, int32_t position);

uint32_t utils_array_getUint32(const uint8_t *p_array, const int32_t index);
uint16_t utils_array_getUint16(const uint8_t *p_array, const int32_t index);
uint8_t utils_array_getUint8(const uint8_t *p_array, const int32_t index);
int16_t utils_array_getInt16(const uint8_t *p_array, const int32_t index);
float_t utils_array_getFloat(const uint8_t *p_array, const int32_t index);

void utils_array_cpy(uint8_t *p_dst, const uint8_t *p_src, const int32_t dstIndex, const int32_t srcIndex, const int32_t length);

uint8_t *utils_array_reverse(uint8_t *p_array, size_t length);

#endif /* UTILS_UTILS_ARRAY_H_ */
