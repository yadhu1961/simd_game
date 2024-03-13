#include <stdio.h>
#include <stdint.h>

uint32_t roundPrevPowerOfTwo(uint32_t number)
{
    while ((number & (number - 1)) != 0)
    {
        number = number & (number - 1);
    }
    return number;
}

uint32_t nextPowerOfTwo(uint32_t number)
{
    if (number & (number - 1) == 0)
    {
        return number;
    }

    return roundPrevPowerOfTwo(number) << 1;
}

int main()
{
    int x = 11;
    printf("number = %d, previousPowerOfTwo %d\n", x, roundPrevPowerOfTwo(x));
    printf("number = %d, nextPowerOfTwo %d\n", x, nextPowerOfTwo(x));
    return 0;
}
