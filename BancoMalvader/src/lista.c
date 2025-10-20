#include "lista.h"
#include <stdlib.h>
#include <string.h>
static int lista_expand(Lista *L)
{
    size_t nova = L->cap ? L->cap * 2 : 4;
    Cliente *t = realloc(L->dados, nova * sizeof *t);
    if (!t)
        return 0;
    L->dados = t;
    L->cap = nova;
    return 1;
}
void lista_init(Lista *L)
{
    L->dados = NULL;
    L->tam = 0;
    L->cap = 0;
}
void lista_free(Lista *L)
{
    free(L->dados);
    L->dados = NULL;
    L->tam = L->cap = 0;
}
int lista_add(Lista *L, Cliente c)
{
    if (L->tam == L->cap && !lista_expand(L))
        return 0;
    L->dados[L->tam++] = c;
    return 1;
}
int lista_find_conta(const Lista *L, const char *conta)
{
    for (size_t i = 0; i < L->tam; i++)
    {
        if (L->dados[i].ativo && strcmp(L->dados[i].conta, conta) == 0)
            return (int)i;
    }
    return -1;
}
int lista_remove_at(Lista *L, size_t idx)
{
    if (idx >= L->tam)
        return 0;
    for (size_t i = idx + 1; i < L->tam; i++)
        L->dados[i - 1] = L->dados[i];
    L->tam--;
    return 1;
}
