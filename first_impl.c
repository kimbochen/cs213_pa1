#include <stdio.h>
#include <stdlib.h>


void sparseMatrixVectorMul(int *row, int *col, double *val, int m, double *x, double *y)
{
    for (int i = 0; i < m; i++) {
        int start = row[i];
        int end = row[i + 1];

        for (int j = start; j < end; j++) {
            y[i] += val[j] * x[col[j]];
        }
    }
}


void readMatrixCSR(FILE *fptr, int *row, int *col, double *val, int nnz, int m)
{
    int j = 1;

    row[0] = 0;

    for (int i = 0; i < nnz; i++) {
        int r, c;
        fscanf(fptr, "%d %d %lf", &r, &c, &val[i]);

        col[i] = c - 1;

        while (j < r) {
            row[j + 1] = row[j];
            j++;
        }
        row[j]++;
    }

    for (int i = j + 1; i < m + 1; i++) {
        row[i] = row[i - 1];
    }
}


int main(int argc, char **argv)
{
    // Check command line arguments
    if (argc != 4) {
        printf("Expected 4 arguments, got %d.\n", argc);
        exit(1);
    }

    // open file
    FILE *fptr = fopen(argv[1], "r");

    if (fptr == NULL) {
        puts("File IO error.");
        exit(1);
    }

    // Read dimensions and allocate memory
    int m, n, nnz;

    fscanf(fptr, "%d %d %d", &m, &n, &nnz);

    int *row = (int*) malloc((m + 1) * sizeof(int));
    int *col = (int*) malloc(nnz * sizeof(int));
    double *val = (double*) malloc(nnz * sizeof(double));

    // Read matrix
    readMatrixCSR(fptr, row, col, val, nnz, m);

    // close file
    fclose(fptr);

    // Init vectors and do calculations
    double *x = (double*) malloc(n * sizeof(double));
    double *y = (double*) malloc(m * sizeof(double));

    for (int i = 0; i < n; i++) {
        x[i] = 1.0;
    }
    for (int i = 0; i < m; i++) {
        y[i] = 0.0;
    }
    sparseMatrixVectorMul(row, col, val, m, x, y);

    // Save answer
    FILE *fout_ptr = fopen("CSRVec1.txt", "w+");
    for (int i = 0; i < m; i++) {
        fprintf(fout_ptr, "%lf\n", y[i]);
    }
    fclose(fout_ptr);

    // free memory
    free(row);
    free(col);
    free(val);
    free(x);
    free(y);

    return 0;
}
