/*
* @Author: Yadu
* @Date:   2018-02-17 20:04:34
* @Last Modified by:   yadu
* @Last Modified time: 2018-02-18 02:16:57
*/

#include <stdio.h>
#include <pmmintrin.h>
#include <immintrin.h>
#include <xmmintrin.h>
#include <time.h>

#define SIZE 512

void print_matrix(float mat[SIZE][SIZE])
{
  printf("Matrix is: \n");
    for (int c = 0; c < SIZE; c++) 
    {
      for (int d = 0; d < SIZE; d++)
        printf("%4f ", mat[c][d]);
      printf("\n");
    }
}


float AVX2_dot_product(float *a, float *b);

int main()
{
    printf("Welcome to matrix multiplication program with simd\n");
    // printf("size of float %u\n",sizeof(float));
    int c, d, k, sum = 0;
    float first[SIZE][SIZE], second[SIZE][SIZE], multiply[SIZE][SIZE];
    float *temp1,*temp2;

    clock_t start,end;

    //Filling the matrix with values in here.
    for(c = 0;c < SIZE;c++)
    {
        for(d = 0;d < SIZE;d++)
        {
            first[c][d] = d;
            second[d][c] = d;
        }
    }

    // print_matrix(first);
    // print_matrix(second);

    // temp1 = (char *)first + SIZE * sizeof(float);
    // temp2 = (char *)second + 4;
    // temp1 = (char *)first;
    // temp2 = (char *)second;

    // for(int i = 0;i<SIZE;i++)
    //     printf("%f ",temp1[i]);
    // printf("\n");

    start  = clock();
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            temp1 = (char *)first + SIZE * sizeof(float)*i;
            temp2 = (char *)second + 4*j;
            multiply[i][j] = AVX2_dot_product(temp1,temp2);
        }
    }
    end = clock() - start;
    double time_taken = ((double)end)/CLOCKS_PER_SEC;
    //clock_gettime(CLOCK_REALTIME, &end);
    //printf("time taken %lf\n",((end.tv_nsec-start.tv_nsec)/1000.0));
    printf("time taken %lf\n",time_taken);
    printf("product value = %lf\n",multiply[15][15]);

    // printf("product value = %lf\n",AVX2_dot_product(first,second));
}

inline float AVX2_dot_product(float *a, float *b)
{
    // printf("%s\n",__func__);
    // for(int i = 0;i<SIZE;i++)
    //     printf("%f ",a[i]);
    // printf("\n");

    // for(int i = 0;i<SIZE;i++)
    //     printf("%f ",b[i]);
    // printf("\n");

    // __m256i vindex = _mm256_set_epi32 (56, 48, 40, 32, 24, 16, 8, 0);

    float total;
    int i;
    __m256 num1, num2, num3;
    __m128 top,bot;
    int indexes = SIZE/2;
    num3 = _mm256_setzero_ps();  //sets sum to zero
    for(i=0; i<SIZE; i+=8)
    {
        __m256i vindex = _mm256_set_epi32 (indexes*(7+i), indexes*(6+i), indexes*(5+i), indexes*(4+i), indexes*(3+i), indexes*(2+i), indexes*(1+i), i*indexes);
        num1 = _mm256_loadu_ps(a+i);   //loads unaligned array a into num1  
        //num1= a[7] a[6] a[5] a[4] a[3]  a[2]  a[1]  a[0]
        // num2 = _mm256_loadu_ps(b);   //loads unaligned array b into num2
        num2 = _mm256_i32gather_ps(b,vindex,8);
        //num2= b[7] b[6] b[5] b[4] b[3]   b[2]   b[1]  b[0]
        num3 = _mm256_fmadd_ps(num1, num2, num3); //performs multiplication and vertical addition  
        //num3 = a[7]*b[7]+num3[7]  a[6]*b[6]+num3[6]  a[5]*b[5]+num3[5]  a[4]*b[4]+num3[4] 
        //       a[3]*b[3]+num3[3]  a[2]*b[2]+num3[2]  a[1]*b[1]+num3[1]  a[0]*b[0]+num3[0]
    }
    num3= _mm256_hadd_ps(num3, num3); //performs horizontal addition
    //For example, if num3 is filled with: 7 6 5 4 3 2 1 0
    //then num3 = 13 9 13 9 5 1 5 1

    //extracting the __m128 from the __m256 datatype
    top = _mm256_extractf128_ps(num3,1);   //top = 13 9 13 9
    bot = _mm256_extractf128_ps(num3,0);   //bot = 5 1 5 1

    //completing the reduction
    top = _mm_add_ps(top,bot);    //top = 14 10 14 10
    top = _mm_hadd_ps(top,top);   //top = 24 24 24 24

    _mm_store_ss(&total,top); //Storing the result in total

    return total;
}