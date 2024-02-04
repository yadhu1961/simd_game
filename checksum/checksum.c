#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint16_t checksum_block_type;

checksum_block_type checksum(uint8_t *data, uint64_t len)
{
    size_t lenInBlockSize = len >> 1;
    size_t remainingBytes = len & 0x1;

    checksum_block_type checksum = 0;
    for (uint64_t index = 0; index < (len - 1); index = index + 2)
    {
        uint16_t combinedValue = ((checksum_block_type)data[index] << 8) | ((checksum_block_type)data[index + 1]);
        printf("16 bit value %20x\n", combinedValue);
        checksum += combinedValue;
    }
    printf("checksum %24x\n(~checksum + checksum) %10x\n\n\n", checksum, (~checksum + checksum));
}

int main()
{
    uint8_t name[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    checksum(name, 11);

    return 0;
}