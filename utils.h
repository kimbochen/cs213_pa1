#ifndef UTILS_H
#define UTILS_H

// Arguments:
// int m, int n, int nnz, int *row, int *col, double *val,
// double *x, double *y, int n_thread
typedef void (*SPMVFunc)(int, int, int, int*, int*, double*, double*, double*, int);

void execute(int, char**, SPMVFunc);

int safe_strtol(char*);

void print_double_arr(double*, int);

void print_int_arr(int*, int);

#endif
