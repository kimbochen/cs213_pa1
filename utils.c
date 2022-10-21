#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"


void execute(int argc, char **argv, SPMVFunc spmvFn)
{
    // Check command line arguments
    if (argc != 4) {
        printf("Expected 4 arguments, got %d.\n", argc);
        exit(1);
    }

    // Read file data
    FILE *fin = fopen(argv[1], "r");  // Open file
    if (fin == NULL) {
        puts("File name error.");
        exit(1);
    }

    int m, n, nnz;
    if (fscanf(fin, "%d %d %d", &m, &n, &nnz) != 3) {
        puts("Cannot read matrix dimensions.");
        exit(1);
    }
    if (m != n) {
        puts("Invalid dimensions: input should be a square matrix.");
        exit(1);
    }

    int *row = (int*) malloc(nnz * sizeof(int));
    int *col = (int*) malloc(nnz * sizeof(int));
    double *val = (double*) malloc(nnz * sizeof(double));

    for (int i = 0; i < nnz; i++) {
        if (fscanf(fin, "%d %d %lf", &row[i], &col[i], &val[i]) != 3) {
            puts("Failed to read a matrix entry.");
            exit(1);
        }
    }
    
    fclose(fin);  // Close file

    // Initialize vectors
    double *x = (double*) malloc(n * sizeof(double));
    double *y = (double*) malloc(m * sizeof(double));

    for (int i = 0; i < n; i++) {
        x[i] = 1.0;
    }
    for (int i = 0; i < m; i++) {
        y[i] = 0.0;
    }

    // Perform computation
    int n_iter = safe_strtol(argv[2]);
    int n_thread = safe_strtol(argv[3]);

    omp_set_num_threads(n_thread);

#ifdef PROF
    double tic = omp_get_wtime();
#endif
    spmvFn(row, col, val, x, y, n, nnz, n_iter);
#ifdef PROF
    double toc = omp_get_wtime();
    printf("Elapsed: %.5lf seconds\n", toc - tic);
#endif

#ifndef PROF
    // Print result
    for (int i = 0; i < m; i++) {
        printf("%.8lf\n", y[i]);
    }
#endif

    // free memory
    free(row);
    free(col);
    free(val);
    free(x);
    free(y);
}


int safe_strtol(char *arg)
{
    char *p;
    errno = 0;
    int num = strtol(arg, &p, 10);

    if (*p != '\0' || errno != 0) {
        printf("Cannot convert argument '%s' to number\n", arg);
        exit(1);
    }

    return num;
}


void print_double_arr(double *arr, int size)
{
    for (int i = 0; i < size; i++) {
        printf("%lf ", arr[i]);
    }
    puts("");
}

void print_int_arr(int *arr, int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    puts("");
}
