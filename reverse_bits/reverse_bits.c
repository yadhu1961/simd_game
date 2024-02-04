#include <stdint.h>
#include <stdio.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)       \
    ((byte)&0x80 ? '1' : '0'),     \
        ((byte)&0x40 ? '1' : '0'), \
        ((byte)&0x20 ? '1' : '0'), \
        ((byte)&0x10 ? '1' : '0'), \
        ((byte)&0x08 ? '1' : '0'), \
        ((byte)&0x04 ? '1' : '0'), \
        ((byte)&0x02 ? '1' : '0'), \
        ((byte)&0x01 ? '1' : '0')

void print(uint8_t input)
{
    printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(input));
    printf("\n");
}

// Reversing bits with logarithmic complexity O(log(n));
uint64_t reverseBits(uint8_t input)
{
    const uint8_t MASK1 = 0b11110000, MASK2 = 0b00001111,
                  MASK3 = 0b11001100, MASK4 = 0b00110011,
                  MASK5 = 0b10101010, MASK6 = 0b01010101;

    printf("input:  ");
    print(input);
    // exchange top 4 bits with lower 4 bits
    input = (input & MASK1) >> 4 | (input & MASK2) << 4;
    // exchange 2 bits within each group of 4 bits
    input = (input & MASK3) >> 2 | (input & MASK4) << 2;
    // exchange 1 bits within each pair of bits
    input = (input & MASK5) >> 1 | (input & MASK6) << 1;
    printf("output: ");
    print(input);

    return input;
}

int main()
{
    reverseBits(0b10110110);
    reverseBits(0b1);

    return 0;
}