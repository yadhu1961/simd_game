#include <stdint.h>
#include <stdio.h>

uint8_t bitCount(uint64_t data)
{
    if (data == 0)
        return 0;
    uint8_t lastTwoBits = data & 0x3;
    return (lastTwoBits ? (lastTwoBits == 3 ? 2 : 1) : 1) + bitCount(data >> 2);
}

int main()
{
    printf("bitcount(%d): ", bitCount(0xFFFF));
    return 0;
}