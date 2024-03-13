#include <stdio.h>
#include <stdint.h>

long pow(int x, int n)
{
    long pow = 1L;

    while (n)
    {
        if (n & 1)
        {
            pow *= x;
        }
        n = n >> 1;
        x *= x;
    }
    return pow;
}

int main()
{
    printf("pow(%d, %d) = %ld\n", 3, 5, pow(3, 5));
    return 0;
}