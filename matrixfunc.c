#include "matrixfunc.h"

void srednee(const int *mat, size_t rows, size_t cols,
                     double *sred)
{
    for (size_t j = 0; j < cols; j++)
    {
        double summa = 0;

        for (size_t i = 0; i < rows; i++)
            summa += *(mat + i * cols + j);

        *(sred + j) = summa / rows;
    }
}

size_t kol_pol(const int *mat, size_t rows, size_t cols)
{
    size_t kol = 0;
    const int *konec = mat + rows * cols;

    for (const int *el = mat; el < konec; el++)
        if (*el > 0)
            kol++;

    return kol;
}

int posl_otr(const int *mat, size_t rows, size_t cols,
                          size_t *stroka, size_t *stolbec)
{
    size_t nomer = rows * cols;

    while (nomer > 0)
    {
        nomer--;
        if (*(mat + nomer) < 0)
        {
            *stroka = nomer / cols;
            *stolbec = nomer % cols;
            return 1;
        }
    }

    return 0;
}
