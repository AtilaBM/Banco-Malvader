#include "quicksort.h"
#include <string.h>
static void trocar(Cliente *a, Cliente *b)
{
    Cliente t = *a;
    *a = *b;
    *b = t;
}
static int part_nome(Cliente v[], int l, int r)
{
    Cliente p = v[r];
    int i = l;
    for (int j = l; j < r; j++)
    {
        if (strcmp(v[j].nome, p.nome) <= 0)
        {
            trocar(&v[i], &v[j]);
            i++;
        }
    }
    trocar(&v[i], &v[r]);
    return i;
}
void quicksort_nome(Cliente v[], int l, int r)
{
    if (l < r)
    {
        int p = part_nome(v, l, r);
        quicksort_nome(v, l, p - 1);
        quicksort_nome(v, p + 1, r);
    }
}
static int part_conta(Cliente v[], int l, int r)
{
    Cliente p = v[r];
    int i = l;
    for (int j = l; j < r; j++)
    {
        if (strcmp(v[j].conta, p.conta) <= 0)
        {
            trocar(&v[i], &v[j]);
            i++;
        }
    }
    trocar(&v[i], &v[r]);
    return i;
}
void quicksort_conta(Cliente v[], int l, int r)
{
    if (l < r)
    {
        int p = part_conta(v, l, r);
        quicksort_conta(v, l, p - 1);
        quicksort_conta(v, p + 1, r);
    }
}
