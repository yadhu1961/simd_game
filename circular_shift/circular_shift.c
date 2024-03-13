#include <stdio.h>
#include <stdint.h>

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

void print(uint8_t input)
{
    printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(input));
    printf("\n");
}

uint8_t circular_lshift(uint8_t input, uint8_t k)
{
    return (input << k) | (input >> (sizeof(input) * 8 - 1));
}

uint8_t circular_rshift(uint8_t input, uint8_t k)
{
    return (input >> k) | (input << (sizeof(input) * 8 - 1));
}

int main()
{
    print(circular_lshift(0x81, 1));
    print(circular_rshift(0x81, 1));
    return 0;
}