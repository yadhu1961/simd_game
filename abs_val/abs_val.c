#define ABS_MASK(input) (input >> ((sizeof(input) * 8) - 1)) // is MSB bit is one(i.e input is -ve), mask

#define ABS(input) (input + ABS_MASK(input)) ^ ABS_MASK(input) // XOR here toggles the bits so that 1's complement in case of -ve number is reversed

int main()
{
    printf("abs of %d is %d\n", -10, ABS(-10));
    printf("abs of %d is %d\n", 10, ABS(10));
    return 0;
}