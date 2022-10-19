#include <stdio.h>
#include <stdlib.h>

#include "utils.h"


void sparseMatVecMul(
    int m, int n, int nnz, int *row, int *col, double *val, double *x, double *y, int n_thread
)
{
    int *csr = (int*) malloc((m + 1) * sizeof(int));

    csr[0] = 0;
    // csr[r] is the first index j where row[j] != r
    for (int r = 1, j = 0; r < m + 1; r++) {
        while (row[j] == r && j < nnz) {
            j++;
        }
        csr[r] = j;
    }

    for (int i = 0; i < m; i++) {
        for (int j = csr[i]; j < csr[i + 1]; j++) {
            y[i] += val[j] * x[col[j] - 1];
        }
    }

    free(csr);
}


int main(int argc, char **argv)
{
    execute(argc, argv, &sparseMatVecMul);
    return 0;
}
