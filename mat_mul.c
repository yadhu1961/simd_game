#include <stdio.h>
#include <time.h>

const int m = 512, n = 512;

void print_matrix(float mat[m][n],int p,int q)
{
  printf("Matrix is: \n");
    for (int c = 0; c < p; c++) 
    {
      for (int d = 0; d < q; d++)
        printf("%4f ", mat[c][d]);
      printf("\n");
    }
}


int main()
{

  int c, d, k, sum = 0;
  double first[m][n], second[m][n], multiply[m][n];
  
  clock_t start,end;

  for(c = 0;c < m;c++)
    for(d = 0;d < n;d++)
    {
      first[c][d] = d;
      second[d][c] = d;
    }

  // print_matrix(first,m,n);
  // print_matrix(second,m,n);
  
  //clock_gettime(CLOCK_REALTIME, &start);
  start  = clock();
  for (c = 0; c < m; c++) {
    for (d = 0; d < n; d++) {
      for (k = 0; k < m; k++) {
        sum = sum + first[c][k]*second[k][d];
      }
      multiply[c][d] = sum;
      sum = 0;
    }
  }
  end = clock() - start;
  double time_taken = ((double)end)/CLOCKS_PER_SEC;
  //clock_gettime(CLOCK_REALTIME, &end);
  //printf("time taken %lf\n",((end.tv_nsec-start.tv_nsec)/1000.0));
  printf("time taken %lf\n",time_taken);

  printf("Product of the matrices: %lf\n",multiply[m-1][n-1]);
  // print_matrix(multiply,m,n);

  return 0;
}