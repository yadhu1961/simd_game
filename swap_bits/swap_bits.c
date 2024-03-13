#include <stdio.h>
#include <stdint.h>
#include <math.h>

// MASK to extract a bit at position pos
#define POS_MASK(pos) (1U << pos)

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)         \
    ((byte) & 0x80 ? '1' : '0'),     \
        ((byte) & 0x40 ? '1' : '0'), \
        ((byte) & 0x20 ? '1' : '0'), \
        ((byte) & 0x10 ? '1' : '0'), \
        ((byte) & 0x08 ? '1' : '0'), \
        ((byte) & 0x04 ? '1' : '0'), \
        ((byte) & 0x02 ? '1' : '0'), \
        ((byte) & 0x01 ? '1' : '0')

/**
 * Swaps the bits of number at a given bit positions
 */
uint8_t swap_bits(uint8_t input, uint8_t pos1, uint8_t pos2)
{
    if (((input & POS_MASK(pos1)) >> pos1) != (((input & POS_MASK(pos2)) >> pos2)))
        return (input ^ POS_MASK(pos1)) ^ POS_MASK(pos2);
    return input;
}

void print(uint8_t input)
{
    printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(input));
    printf("\n");
}

int main()
{
    uint8_t x = 0b00001001;
    // after swapping it should be 0b0000'0011
    print(swap_bits(x, 3, 1));
    x = 0b00001001;
    // after swapping it should be 0b0000'1100
    print(swap_bits(x, 2, 0));

    return 0;
}