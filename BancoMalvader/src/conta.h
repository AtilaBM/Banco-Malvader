#ifndef CONTA_H
#define CONTA_H
#include "lista.h"
int abrir_conta(Lista *L, const Cliente *novo);
int encerrar_conta(Lista *L, const char *conta);
int depositar(Cliente *c, double valor);
int sacar(Cliente *c, double valor);
#endif
