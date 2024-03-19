#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

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

uint8_t countBits_BK(uint64_t input)
{
    uint8_t bitCounter = 0;
    while (input > 0)
    {
        input &= (input - 1);
        ++bitCounter;
    }
    return bitCounter;
}

/**
 * Accepts 64-bit integer and returns 0 if it is even parity
 * one if the number is of odd parity.
 */
bool parityCalc(uint64_t input)
{
    return countBits(input) & 0x01;
}

/**
 * Count trailing zeros, devise a logic to count trailing zeros
 * in logarithmic complexity.
 */
uint8_t ctz(uint8_t input)
{
    if (input == 0)
        return 16;
    uint8_t ntz = 0; // since the number 32 bits.
    if ((input & 0x0F) == 0)
    {
        ntz += 4; // If lower 2 bytes are 0, add 16 to ntz.
    }
    // input = input & 0x0000FFFF;
    if ((input & 0x33) == 0)
    {
        ntz += 2; // If lower byte is 0, add 8 to ntz
    }
    // input = input & 0x00FF00FF;
    if (!(input & 0x55))
    {
        ntz += 1;
    }
    // // input = input & 0x0F0F0F0F;
    // if ((input & 0x33333333) == 0)
    // {
    //     ntz += 2;
    // }
    // // input = input & 0x33333333;
    // if ((input & 0x1) == 0)
    // {
    //     ntz += 1;
    // }

    return ntz;

    // if (numBits == 1)
    //     return !input;
    // input = input & ((1U << numBits) - 1);

    // uint8_t newNumBits = numBits >> 1;

    // return ctz((input >> newNumBits), newNumBits) + ctz(input, (numBits >> 1));

    // uint8_t ntz = (input & 0xFFFF) == 0 ? 16 : 0;
    // input = ntz > 0 ? (input >> 16) : input & 0xFFFF; // Take only the last 16 bits if they are non zero
    // ntz += (input & 0xFF)
}

// Find number of set bits in 32-bit integer in constant time i.e O(1)
uint8_t lookup_table[256] = {0, 1, 1, 2 /*extend table for 256 values during initialization*/};
uint8_t find_num_bits_set(uint32_t input)
{
    return lookup_table[input & 0xFF] + lookup_table[(input >> 8) & 0xFF] +
           lookup_table[(input >> 16) & 0xFF] + lookup_table[(input >> 24) & 0xFF];
}

int main()
{
    printf("bitcount        (%d)\n", bitCount(0xFFFF));
    printf("countBits       (%d)\n", countBits(0xFFFF));
    printf("countBits_Bk    (%d)\n", countBits_BK(0xFFFF));
    printf("parityCalc      (%d)\n", parityCalc(0xFFFF));

    printf("bitcount        (%d)\n", bitCount(0x9));
    printf("countBits       (%d)\n", countBits(0x9));
    printf("countBits_BK    (%d)\n", countBits_BK(0x9));
    printf("parityCalc      (%d)\n", parityCalc(0x4));

    for (int i = 0; i < 8; i++)
    {
        printf("number of trailing zeros in (%d) are %d\n", i, ctz(i));
    }

    return 0;
}
