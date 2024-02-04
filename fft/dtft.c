#include <complex.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define EXP 2.718f
#define PI 3.1459f

void dtft(const float signal[], const uint32_t N, float complex output[])
{
    for (uint32_t n = 0; n < N; ++n)
    {
        output[n] = 0;
        for (uint32_t k = 0; k < N; ++k)
        {
            const double theta = (-2 * PI * k * n / (float)N);
            output[n] += signal[k] * (cos(theta) + sin(theta) * I);
        }
    }
}

void printComplexArray(float complex output[], uint32_t len)
{
    for (uint32_t n = 0; n < len; ++n)
    {
        // printf("%f, %f", creal(output[n]), cimag(output[n]));
        printf("(%.1f, %.1fi), ", creal(output[n]), cimag(output[n]));
    }
    printf("\n");
}

int main()
{
    float signal[] = {-1, 1, 0, 1};
    float complex output[] = {0, 0, 0, 0};

    dtft(signal, 4, output);

    printComplexArray(output, 4);
    return EXIT_SUCCESS;
}
