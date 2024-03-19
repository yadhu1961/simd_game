#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Check if the processor is little endian or big endian
bool is_little_endian()
{
    uint16_t val = 0x0102;

    uint8_t *val_byte = &val;

    return *val_byte == 02;
}

int main()
{

    printf("is_little_endian: %s", is_little_endian() ? "true" : "false");

    return 0;
}