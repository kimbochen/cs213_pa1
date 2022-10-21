#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"


void sparseMatVecMul(
    int *row, int *col, double *val, double *x, double *y,
    int N, int nnz, int n_iter
)
{
    // Convert row array to CSR format
    int *csr = calloc(N + 1, sizeof(int));

    // Count the number of elements in each column: column i at col[i+1]
    for (int i = 0; i < nnz; i++) {
        csr[row[i]]++;
    }
    // Perform cumulative sum
    for (int i = 2; i < N + 1; i++) {
        csr[i] += csr[i - 1];
    }

#pragma omp parallel
    {
        for (int k = 0; k < n_iter; k++) {
            // Perform matrix-vector multiplication
#pragma omp for
            for (int i = 0; i < N; i++) {
                for (int j = csr[i]; j < csr[i + 1]; j++) {
                    y[i] += val[j] * x[col[j] - 1];
                }
            }

            // Set output as next input and zero-out output vector
            if (k < n_iter - 1) {
#pragma omp for
                for (int i = 0; i < N; i++) {
                    x[i] = y[i];
                    y[i] = 0.0;
                }
            }
        }
    }

    free(csr);  // Free memory for CSR array
}


int main(int argc, char **argv)
{
    execute(argc, argv, &sparseMatVecMul);
    return 0;
}
