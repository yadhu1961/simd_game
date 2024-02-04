#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Useful macros
#define BYTE_SIZE 8
#define TOP_BIT 0x80

// Related to polynomial with degree 8
#define POLYNOMIAL8 0x137 // (x^8 + x^5 + x^4 + x^2 + x + 1) Polynomial is of degree 8, hence 8 bit CRC bits \
                          //   0001 0011 0111
#define DEGREE8 8

// Related to polynomial with degree 3
#define POLYNOMIAL3 0xBu // (x^3 + 0 x^2 + x + 1) polynomian of degree 3, hence 3 bit CRC, 0000 1011 (0x0B)
#define DEGREE3 3
#define POLYNOMIAL3_MSB (POLYNOMIAL3 << (BYTE_SIZE - DEGREE3 - 1))

uint8_t crcCalc(uint8_t data[], uint8_t len)
{
    uint8_t remainder = 0;
    for (uint8_t dataIndex = 0; dataIndex < len; ++dataIndex)
    {
        remainder = remainder ^ data[dataIndex];
        for (uint8_t count = 0; count < BYTE_SIZE; ++count)
        {
            if (remainder & TOP_BIT)
                remainder = remainder ^ POLYNOMIAL3_MSB;
            remainder = remainder << 1;
        }
        //printf("calculated intermediate CRC(3 MSB bits) %x\n", remainder);
    }
    remainder = remainder >> (BYTE_SIZE - DEGREE3);
    //printf("calculated CRC %x\n", remainder);
    return remainder;
}

uint8_t crcTable[256] = {0};
// CRC init for precalculation
void crcInit()
{
    for (int byteValue = 0; byteValue <= UCHAR_MAX; ++byteValue)
    {
        uint8_t remainder = byteValue;
        for (uint8_t bitIndex = 0; bitIndex < BYTE_SIZE; ++bitIndex)
        {
            if (remainder & TOP_BIT)
                remainder = remainder ^ POLYNOMIAL3_MSB;
            remainder = remainder << 1;
        }
        //Store 3 MSB bits in a lookup table, since it contains CRC.
        crcTable[byteValue] = remainder >> (BYTE_SIZE - DEGREE3);
    }
}

// fast crc calculator, uses lookup table and processes 8 bits at a time.
// hence faster than a naive crcCalc impl.
uint8_t fastCrc(uint8_t data[], uint8_t len)
{
    uint8_t remainder = 0;
    for (uint8_t dataIndex = 0; dataIndex < len; ++dataIndex)
    {
        uint8_t byteValue = data[dataIndex]; // read data byte by byte
        uint8_t crc = crcTable[byteValue ^ remainder];
        // 3 bit CRC from table is moved to MSB as prep to next iteration
        remainder = (crc << (BYTE_SIZE - DEGREE3));
    }
    remainder = remainder >> (BYTE_SIZE - DEGREE3);
    //printf("calculated fast CRC %x\n", remainder);
    return remainder;
}

int main()
{
    crcInit();
    printf("Crc of %x from crcTable is: %x\n", 0xD3, crcTable[0xD3]);

    printf("Crc of %x from crcTable is: %x\n", 0xB3, crcTable[0xB3]);

    uint8_t data[] = {0xD3, 0xD3, 0xD3};
    printf("crcCalc: crc of %x is %x\n", 0xD3, crcCalc(data, 2));

    printf("fastCrc: crc of %x is %x\n", 0xD3, fastCrc(data, 2));

    return 0;
}