#include <limits.h>
#include <stdio.h>
#include "matrixfunc.h"

#define max_razmer 100

static int chitat(int *chislo)
{
    char ch;
    int rez = scanf(" %c", &ch);
    if (rez == EOF)
        return EOF;

    int minus = ch == '-';
    int znak = ch == '-' || ch == '+';
    int tek = ch;
    if (znak)
        tek = getchar();

    long long lim = INT_MAX;
    if (minus)
        lim = -(long long)INT_MIN;

    long long num = 0;
    int est_cifra = 0;
    int err = 0;

    while (tek != EOF && tek != ' ' && tek != '\t' && tek != '\n' &&
           tek != '\r' && tek != '\v' && tek != '\f')
    {
        if (tek < '0' || tek > '9')
            err = 1;
        else if (!err)
        {
            int cifra = tek - '0';

            if (num > (lim - cifra) / 10)
                err = 1;
            else
                num = num * 10 + cifra;

            est_cifra = 1;
        }
        tek = getchar();
    }

    if (err || !est_cifra)
    {
        while (tek != EOF && tek != '\n')
            tek = getchar();
        return 0;
    }

    if (minus)
        num = -num;

    *chislo = (int)num;
    return 1;
}

static int zadat(size_t *rows, size_t *cols)
{
    int str, stolb;

    printf("Введите число строк и столбцов (от 1 до %d): ", max_razmer);
    int rez = chitat(&str);
    if (rez != 1)
        return rez;

    rez = chitat(&stolb);
    if (rez != 1)
        return rez;

    if (str < 1 || str > max_razmer || stolb < 1 || stolb > max_razmer)
        return 0;

    *rows = (size_t)str;
    *cols = (size_t)stolb;
    return 1;
}

static int zapolnit(int *mat, size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        printf("Введите элементы строки %zu: ", i);
        for (size_t j = 0; j < cols; j++)
        {
            int rez = chitat(mat + i * cols + j);
            if (rez != 1)
                return rez;
        }
    }

    return 1;
}

static void pokazat(const int *mat, size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            const int *el = mat + i * cols + j;
            printf("[%zu][%zu] = %d (%p)  ", i, j, *el, (void *)el);
        }
        printf("\n");
    }
}

int main(void)
{
    int mat[max_razmer * max_razmer];
    double sred[max_razmer];
    size_t rows = 0, cols = 0;
    size_t stroka, stolbec;
    int gotovo = 0;
    int rez = 1;
    char punkt;

    while (rez != EOF)
    {
        printf("\na    Задать размер матрицы (строки, столбцы)\n");
        printf("b    Заполнить матрицу\n");
        printf("c    Представление матрицы (значения, адреса элементов)\n");
        printf("d    Среднее арифметическое элементов каждого столбца\n");
        printf("e    Количество положительных элементов матрицы\n");
        printf("f    Индексы последнего отрицательного элемента\n");
        printf("g    Выход\n");
        printf("Выберите пункт: ");

        if (scanf(" %c", &punkt) == EOF)
            break;

        int ch = getchar();
        int lishnee = 0;
        while (ch != '\n' && ch != EOF)
        {
            if (ch != ' ' && ch != '\t' && ch != '\r')
                lishnee = 1;
            ch = getchar();
        }

        if (lishnee || punkt < 'a' || punkt > 'g')
        {
            printf("Ошибка: нет такого пункта\n");
            continue;
        }

        if (punkt == 'g')
            break;

        if (punkt == 'b' && rows == 0)
        {
            printf("Сначала задайте размер матрицы\n");
            continue;
        }

        if (punkt >= 'c' && !gotovo)
        {
            printf("Сначала заполните матрицу\n");
            continue;
        }

        switch (punkt)
        {
        case 'a':
            rez = zadat(&rows, &cols);
            if (rez == 1)
                gotovo = 0;
            else if (rez == 0)
                printf("Ошибка: неверные размеры матрицы\n");
            break;
        case 'b':
            rez = zapolnit(mat, rows, cols);
            gotovo = rez == 1;
            if (rez == 0)
                printf("Ошибка: нужно ввести целое число\n");
            break;
        case 'c':
            pokazat(mat, rows, cols);
            break;
        case 'd':
            srednee(mat, rows, cols, sred);
            for (size_t j = 0; j < cols; j++)
                printf("Столбец %zu: %.2f\n", j, *(sred + j));
            break;
        case 'e':
            printf("Количество положительных элементов: %zu\n",
                   kol_pol(mat, rows, cols));
            break;
        case 'f':
            if (posl_otr(mat, rows, cols, &stroka, &stolbec))
                printf("Строка: %zu, столбец: %zu\n", stroka, stolbec);
            else
                printf("Отрицательных элементов нет\n");
            break;
        }
    }

    return 0;
}
