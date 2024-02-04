#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint16_t checksum_type;

checksum_type checksum(uint8_t data[], uint64_t len)
{
    if (len == 0)
        return 0xFFFF;

    if (len == 1)
        return ~((uint16_t)(data[0] << 8));

    checksum_type checksum = 0;
    uint64_t len_even = len & ~(0x01U);
    const bool isOddLen = len & 0x01;

    for (uint64_t byteIdx = 0; byteIdx < len_even; byteIdx = byteIdx + 2)
    {
        checksum += ((uint16_t)data[byteIdx] << 8) | ((uint16_t)data[byteIdx + 1]);
    }

    if (isOddLen)
        checksum += data[len - 1];

    return ~checksum;
}

bool verify(uint8_t data[], uint64_t len, uint16_t receivedCheckSum)
{
    if (len == 0)
        return false;

    if (len == 1)
        return (receivedCheckSum + data[0]) == 0xFFFF;

    checksum_type sum = 0;
    uint64_t len_even = len & ~(0x01U);
    const bool isOddLen = len & 0x01;

    for (uint64_t byteIdx = 0; byteIdx < len_even; byteIdx = byteIdx + 2)
    {
        sum += ((uint16_t)data[byteIdx] << 8) | ((uint16_t)data[byteIdx + 1]);
    }

    if (isOddLen)
        sum += data[len - 1];

    //printf("calculatedSum: %x\n", sum);

    return (sum + receivedCheckSum) == 0xFFFF;
}

int main()
{
    uint8_t name[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    checksum_type checkSum2 = checksum(name, 2);
    checksum_type checkSum3 = checksum(name, 3);
    printf("checksum2: %x\n", checkSum2);
    printf("checksum3: %x\n", checkSum3);

    name[2] = 4; // Simulate the corruption of the data transmitted over a channel.

    printf("verify2: %s\n", verify(name, 2, checkSum2) ? "data correctly received" : "data is corrupted");
    printf("verify3: %s\n", verify(name, 3, checkSum3) ? "data correctly received" : "data is corrupted");

    name[1] = 3; // Simulate the corruption of the data transmitted over a channel.

    printf("verify2: %s\n", verify(name, 2, checkSum2) ? "data correctly received" : "data is corrupted");
    printf("verify3: %s\n", verify(name, 3, checkSum3) ? "data correctly received" : "data is corrupted");

    return 0;
}