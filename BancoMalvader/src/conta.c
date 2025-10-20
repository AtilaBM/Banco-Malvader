#include "conta.h"
#include <string.h>
int abrir_conta(Lista *L, const Cliente *novo)
{
    if (!L || !novo)
        return 0;
    if (lista_find_conta(L, novo->conta) != -1)
        return 0;
    return lista_add(L, *novo);
}
int encerrar_conta(Lista *L, const char *conta)
{
    int idx = lista_find_conta(L, conta);
    if (idx < 0)
        return 0;
    if (L->dados[idx].saldo != 0.0)
        return 0;
    L->dados[idx].ativo = 0;
    return 1;
}
int depositar(Cliente *c, double v)
{
    if (!c || v <= 0)
        return 0;
    c->saldo += v;
    return 1;
}
int sacar(Cliente *c, double v)
{
    if (!c || v <= 0)
        return 0;
    if (v > c->saldo)
        return 0;
    c->saldo -= v;
    return 1;
}
