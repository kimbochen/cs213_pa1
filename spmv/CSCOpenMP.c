#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"


void sparseMatVecMul(
    int *row, int *col, double *val, double *x, double *y,
    int N, int nnz, int n_iter
)
{
#ifdef PROF
    double tic, toc;
#endif


#ifdef PROF
    tic = omp_get_wtime();
#endif
    // Convert col array to CSC format
    int *csc = calloc(N + 1, sizeof(int));

    // Count the number of elements in each column: column i at col[i+1]
    for (int i = 0; i < nnz; i++) {
        csc[col[i]]++;
    }

    // Perform cumulative sum
    for (int i = 2; i < N + 1; i++) {
        csc[i] += csc[i - 1];
    }

    // Create a column major order row array
    int *row_t = (int*) malloc(nnz * sizeof(int));
    double *val_t = (double*) malloc(nnz * sizeof(double));
#ifdef PROF
    toc = omp_get_wtime();
    printf("CSC conversion: %.5lf\n", toc - tic);
#endif


#ifdef PROF
    tic = omp_get_wtime();
#endif

    for (int c = 1, idx = 0; c < N + 1; c++) {
#pragma omp parallel
        {
#pragma omp for
            for (int i = 0; i < nnz; i++) {
                if (col[i] == c) {
#pragma omp critical
                    {
                        row_t[idx] = row[i] - 1;
                        val_t[idx] = val[i];
                        idx++;
                    }
                }
            }
        }
    }


#ifdef PROF
    toc = omp_get_wtime();
    printf("Create row_t val_t arrays: %.5lf\n", toc - tic);
#endif


#ifdef PROF
    tic = omp_get_wtime();
#endif

    for (int k = 0; k < n_iter; k++) {
        // Perform matrix-vector multiplication
        for (int c = 0; c < N; c++) {
            for (int j = csc[c]; j < csc[c + 1]; j++) {
                y[row_t[j]] += val_t[j] * x[c];
            }
        }

        // Set output as next input and zero-out output vector
        if (k < n_iter - 1) {
#pragma omp parallel for
            for (int i = 0; i < N; i++) {
                x[i] = y[i];
                y[i] = 0.0;
            }
        }
    }

#ifdef PROF
    toc = omp_get_wtime();
    printf("Matrix vector multiplication: %.5lf\n", toc - tic);
#endif


    free(csc);    // Free memory for CSC array
    free(row_t);  // Free memory for row_t array 
    free(val_t);  // Free memory for val_t array 
}


int main(int argc, char **argv)
{
    execute(argc, argv, &sparseMatVecMul);
    return 0;
}
