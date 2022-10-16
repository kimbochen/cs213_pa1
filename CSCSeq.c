#include <stdio.h>
#include <stdlib.h>

#include "utils.h"


void sparseMatVecMul(
    int m, int n, int nnz, int *row, int *col, double *val, double *x, double *y, int n_thread
)
{
    int *row_t = col;
    int *col_t = row;
    int *csc = (int*) malloc((m + 1) * sizeof(int));

    csc[0] = 0;
    // csc[c] is the first index j where col_t[j] != c
    for (int c = 1, j = 0; c < m + 1; c++) {
        while (col_t[j] == c && j < nnz) {
            j++;
        }
        csc[c] = j;
    }

    for (int i = 0; i < m; i++) {
        for (int j = csc[i]; j < csc[i + 1]; j++) {
            y[i] += val[j] * x[row_t[j] - 1];
        }
    }

}


int main(int argc, char **argv)
{
    execute(argc, argv, &sparseMatVecMul);
    return 0;
}
