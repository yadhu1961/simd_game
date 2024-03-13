#include <stdio.h>

#define SAME_SIGN(x, y) (!((x ^ y) & (0x1U << ((sizeof(x) * 8) - 1))))

int main()
{
    int x = -1, y = -2;
    printf("is_same_sign(%d, %d) = %d\n", x, y, SAME_SIGN(x, y));

    x = 1;
    printf("is_same_sign(%d, %d) = %d\n", x, y, SAME_SIGN(x, y));

    y = 2;
    printf("is_same_sign(%d, %d) = %d\n", x, y, SAME_SIGN(x, y));

    x = -1;
    printf("is_same_sign(%d, %d) = %d\n", x, y, SAME_SIGN(x, y));

    return 0;
}