#include "utils_array.h"

#include <string.h>

void utils_array_addUint8(uint8_t *p_array, const uint8_t data, const int32_t index)
{
    memcpy(&p_array[index], &data, sizeof(uint8_t));
}

void utils_array_addUint16(uint8_t *p_array, const uint16_t data, const int32_t index)
{
    memcpy(&p_array[index], (uint8_t *)&data, sizeof(uint16_t));
}

void utils_array_addUint32(uint8_t *p_array, const uint32_t data, const int32_t index)
{
    memcpy(&p_array[index], (uint8_t *)&data, sizeof(uint32_t));
}

void utils_array_addInt16(uint8_t *p_array, const int16_t data, const int32_t index)
{
    memcpy(&p_array[index], (uint8_t *)&data, sizeof(int16_t));
}

void utils_array_addFloat(uint8_t *p_array, float_t number, int32_t position)
{
    memcpy(&p_array[position], (uint8_t *)&number, sizeof(float_t));
}

uint32_t utils_array_getUint32(const uint8_t *p_array, const int32_t index)
{
    uint32_t number = 0;
    memcpy((uint8_t *)&number, &p_array[index], sizeof(uint32_t));

    return number;
}

uint16_t utils_array_getUint16(const uint8_t *p_array, const int32_t index)
{
    uint16_t number = 0;
    memcpy((uint8_t *)&number, &p_array[index], sizeof(uint16_t));

    return number;
}

uint8_t utils_array_getUint8(const uint8_t *p_array, const int32_t index)
{
    return p_array[index];
}

int16_t utils_array_getInt16(const uint8_t *p_array, const int32_t index)
{
    int16_t number = 0;
    memcpy(&number, &p_array[index], sizeof(int16_t));

    return number;
}

float_t utils_array_getFloat(const uint8_t *p_array, const int32_t index)
{
    float_t number = 0;
    memcpy((uint8_t *)&number, &p_array[index], sizeof(float_t));

    return number;
}

void utils_array_cpy(uint8_t *p_dst, const uint8_t *p_src, const int32_t dstIndex, const int32_t srcIndex, const int32_t length)
{
    memcpy(&p_dst[dstIndex], &p_src[srcIndex], (size_t)length);
}

uint8_t *utils_array_reverse(uint8_t *p_array, size_t length)
{
    uint8_t *p_start = p_array;
    uint8_t *p_end = p_array + length - 1;

    while (p_start < p_end)
    {
        uint8_t temp = *p_start;
        *p_start = *p_end;
        *p_end = temp;
        p_start++;
        p_end--;
    }

    return p_array;
}
