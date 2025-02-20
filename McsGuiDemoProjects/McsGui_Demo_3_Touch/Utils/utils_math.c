#include "utils_math.h"

int32_t utils_math_ipow(int32_t base, uint32_t exp)
{
    int32_t result = 1;

    while (exp)
    {
        if (exp & 1)
        {
            result *= base;
        }

        exp >>= 1;
        base *= base;
    }

    return result;
}
