#ifndef matrixfunc_h
#define matrixfunc_h

#include <stddef.h>

void srednee(const int *mat, size_t rows, size_t cols,
                     double *sred);
size_t kol_pol(const int *mat, size_t rows, size_t cols);
int posl_otr(const int *mat, size_t rows, size_t cols,
                          size_t *stroka, size_t *stolbec);

#endif
