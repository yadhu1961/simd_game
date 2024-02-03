#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(const int8_t sequence[], uint8_t len)
{
    for (uint8_t index = 0; index < len; ++index)
    {
        printf("%d ", sequence[index]);
    }
    printf("\n");
}
/**
 * Accepts two input sequences and their lengths by reference and calculates the convolution of
 * two sequences writes to output sequence reference
 * returns length of the output sequence.
*/
int8_t convolution(const int8_t sig_x[], const uint8_t len_x,
                   const int8_t sig_y[], const uint8_t len_y,
                   int8_t sig_z[])
{
    const uint8_t len_z = len_x + len_y - 1;
    printf("sequence x: \n");
    print(sig_x, len_x);
    printf("sequence y: \n");
    print(sig_y, len_y);

    // convolution calculator
    for (uint8_t n = 0; n < len_z; ++n)
    {
        for (uint8_t k = 0; k <= n; ++k)
        {
            int8_t sig_k = (k >= len_x) ? 0 : sig_x[k];
            int8_t sig_hk = (n - k >= len_y) ? 0 : sig_y[n - k];

            sig_z[n] += sig_k * sig_hk;
        }
    }

    printf("output sequence: \n");
    print(sig_z, len_z);

    return len_z;
}

int main()
{
    int8_t seq_x[] = {-1, 1, 0, 1, 2}, seq_y[] = {0, 2, -1};

    size_t len_x = sizeof(seq_x) / sizeof(seq_x[0]);
    size_t len_y = sizeof(seq_y) / sizeof(seq_y[0]);

    int8_t seq_z[len_x + len_y - 1]; // resulting sequence is stored here
    memset(seq_z, 0, len_x + len_y - 1);

    convolution(seq_x, len_x, seq_y, len_y, seq_z);

    return EXIT_SUCCESS;
}