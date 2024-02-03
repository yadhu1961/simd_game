#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Useful macros
#define BYTE_SIZE 8
#define TOP_BIT 0x80
#define POLYNOMIAL 0x137 // Polynomial is of degree 5 bits

uint8_t crcTable[256];

void crcInit()
{
    for (int i = 0; i < 256; ++i)
    {
        uint8_t remainder = i;
        for (uint8_t j = 0; j < BYTE_SIZE; ++j)
        {
            if (remainder & TOP_BIT)
            {
                remainder = remainder ^ POLYNOMIAL;
            }
            remainder = remainder << 1;
        }
        crcTable[i] = remainder; // Store the last 4 bits of remainder. 8 bit CRC
    }
}

int main()
{
    crcInit();
    const uint8_t data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const uint8_t dataIndex = 9;
    printf("Crc of %d : %d\n", 0xC2, crcTable[0xC2]);
    return 0;
}