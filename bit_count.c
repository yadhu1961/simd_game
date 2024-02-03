#include <stdint.h>
#include <stdio.h>

uint8_t bitCount(uint64_t data)
{
    if (data == 0)
        return 0;
    uint8_t lastTwoBits = data & 0x3;
    return (lastTwoBits ? (lastTwoBits == 3 ? 2 : 1) : 1) + bitCount(data >> 2);
}

uint8_t countBits(uint64_t data)
{
    uint8_t bitCounter = 0;
    while (data > 0)
    {
        uint8_t lastTwoBits = data & 0x3;
        bitCounter += (lastTwoBits) > 0 ? (lastTwoBits == 3 ? 2 : 1) : 0;
        data = data >> 2;
    }
    return bitCounter;
}

int main()
{
    printf("bitcount(%d)\n", bitCount(0xFFFF));
    printf("countBits(%d)\n", countBits(0xFFFF));

    printf("bitcount(%d)\n", bitCount(0x9));
    printf("countBits(%d)\n", countBits(0x9));
    return 0;
}
