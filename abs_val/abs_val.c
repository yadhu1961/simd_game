#include <stdio.h>

// is MSB bit is one(i.e input is -ve), mask
#define ABS_MASK(input) ((input >> ((sizeof(input) * 8)) - 1))

// XOR here toggles the bits so that 1's complement in case of -ve number is reversed
// here ABS_MASK(input) is nothing but -1 when the number is negative.
#define ABS(input) (input + ABS_MASK(input)) ^ ABS_MASK(input)

int main()
{
    printf("abs of %d is %d, with abs_mask %x\n", -10, ABS(-10), ABS_MASK(-10));
    printf("abs of %d is %d, , with abs_mask %x\n", 10, ABS(10), ABS_MASK(10));
    return 0;
}