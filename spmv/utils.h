#ifndef UTILS_H
#define UTILS_H

// Arguments:
// int *row, int *col, double *val, double *x, double *y, 
// int N, int nnz, int n_iter
typedef void (*SPMVFunc)(int*, int*, double*, double*, double*, int, int, int);

void execute(int, char**, SPMVFunc);

int safe_strtol(char*);

void print_double_arr(double*, int);

void print_int_arr(int*, int);

#endif
