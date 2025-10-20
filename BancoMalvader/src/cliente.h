#ifndef CLIENTE_H
#define CLIENTE_H
#include <stddef.h>
typedef struct{
    char agencia[8];
    char conta[16];
    char nome[100];
    char cpf[15];
    char data_nasc[11];
    char telefone[20];
    char endereco[120];
    char cep[10];
    char local[60];
    char numero_casa[10];
    char bairro[60];
    char cidade[60];
    char estado[3];
    char senha[20];
    double saldo;
    int ativo;
} Cliente;
void cliente_padrao(Cliente* c);
int  cliente_cmp_nome(const Cliente* a,const Cliente* b);
int  cliente_cmp_conta(const Cliente* a,const Cliente* b);
void imprimir_dados_cliente(const Cliente* c);
#endif
