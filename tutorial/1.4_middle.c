#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_DIM 590
#define N_ITER 10

int main(int argc, char **argv)
{
    int i, j, k;
    double sum;
    double start, end; // used for timing
    double A[MAX_DIM][MAX_DIM], B[MAX_DIM][MAX_DIM], C[MAX_DIM][MAX_DIM];
    int N = MAX_DIM;
    
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = j*1;
            B[i][j] = i*j+2;
            C[i][j] = j-i*2;
        }
    }
    
    double time_sum = 0.0;

    for (int it = 0; it < N_ITER; it++) {
        start = omp_get_wtime(); //start time measurement
        for (i = 0; i < N; i++) {
#pragma omp parallel default(none) shared(A, B, C, N, i)
            {
#pragma omp for private(j, k, sum)
                for (j = 0; j < N; j++) {
                    sum = 0;
                    for (k=0; k < N; k++) {
                        sum += A[i][k]*B[k][j];
                    }
                    C[i][j] = sum;
                }
            }
        }
        end = omp_get_wtime(); //end time measurement

        time_sum += end - start;
    }

    printf("Time of computation: %f seconds\n", time_sum / N_ITER);

    return(0);
}
