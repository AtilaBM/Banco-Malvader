#ifndef LISTA_H
#define LISTA_H
#include "cliente.h"
#include <stddef.h>
typedef struct
{
    Cliente *dados;
    size_t tam;
    size_t cap;
} Lista;
void lista_init(Lista *L);
void lista_free(Lista *L);
int lista_add(Lista *L, Cliente c);
int lista_remove_at(Lista *L, size_t idx);
int lista_find_conta(const Lista *L, const char *conta);
#endif
