#include <stdio.h>
#include <stdlib.h>

#include "utils.h"


void sparseMatVecMul(int *row, int *col, double *val, double *x, double *y, int N, int nnz, int n_iter)
{
    // Convert row array to CSR format
    int *csr = (int*) malloc((N + 1) * sizeof(int));

    csr[0] = 0;
    for (int r = 1, j = 0; r < N + 1; r++) {
        // csr[r] is the first index j where row[j] != r
        while (row[j] == r && j < nnz) {
            j++;
        }
        csr[r] = j;
    }


    // Perform matrix-vector multiplication
    for (int k = 0; k < n_iter; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = csr[i]; j < csr[i + 1]; j++) {
                y[i] += val[j] * x[col[j] - 1];
            }
        }

        // Set output as next input
        if (k < n_iter - 1) {
            for (int i = 0; i < N; i++) {
                x[i] = y[i];
                y[i] = 0.0;
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
