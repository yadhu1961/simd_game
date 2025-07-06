#include <complex.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define EXP 2.718f
#define PI M_PI
#define FFT_SIZE 8

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

int main(void)
{
    float signal[] = {-1, 1, 2, 1, 4, -2, 6, -8};
    float complex output[] = {0, 0, 0, 0, 0, 0, 0, 0};

    dtft(signal, FFT_SIZE, output);

    printComplexArray(output, FFT_SIZE);
    return EXIT_SUCCESS;
}
