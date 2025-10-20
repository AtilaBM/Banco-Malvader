#include "io.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
void ler_linha(char *buf, size_t tam)
{
    if (fgets(buf, (int)tam, stdin))
        buf[strcspn(buf, "\n")] = 0;
}
int salvar_clientes(const char *arq, const Lista *L)
{
    FILE *f = fopen(arq, "w");
    if (!f)
        return 0;
    for (size_t i = 0; i < L->tam; i++)
    {
        const Cliente *c = &L->dados[i];
        if (!c->ativo)
            continue;
        fprintf(f, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%.2f;%d\n",
                c->agencia, c->conta, c->nome, c->cpf, c->data_nasc, c->telefone,
                c->endereco, c->cep, c->local, c->numero_casa, c->bairro, c->cidade,
                c->estado, c->senha, c->saldo, c->ativo);
    }
    fclose(f);
    return 1;
}
int carregar_clientes(const char *arq, Lista *L)
{
    FILE *f = fopen(arq, "r");
    if (!f)
        return 1;
    char linha[1024];
    while (fgets(linha, sizeof linha, f))
    {
        Cliente c = {0};
        linha[strcspn(linha, "\n")] = 0;
        int ativo_tmp = 1;
        if (sscanf(linha,
                   "%7[^;];%15[^;];%99[^;];%14[^;];%10[^;];%19[^;];%119[^;];%9[^;];%59[^;];%9[^;];%59[^;];%59[^;];%2[^;];%19[^;];%lf;%d",
                   c.agencia, c.conta, c.nome, c.cpf, c.data_nasc, c.telefone,
                   c.endereco, c.cep, c.local, c.numero_casa, c.bairro, c.cidade,
                   c.estado, c.senha, &c.saldo, &ativo_tmp) == 16)
        {
            c.ativo = ativo_tmp;
            if (!lista_add(L, c))
            {
                fclose(f);
                return 0;
            }
        }
    }
    fclose(f);
    return 1;
}
int registrar_mov(const char *arq, const char *conta, const char *tipo, double valor, double saldo)
{
    FILE *f = fopen(arq, "a");
    if (!f)
        return 0;
    time_t t = time(NULL);
    struct tm *tmv = localtime(&t);
    fprintf(f, "%04d-%02d-%02d;%s;%s;%.2f;saldo=%.2f\n",
            tmv->tm_year + 1900, tmv->tm_mon + 1, tmv->tm_mday, conta, tipo, valor, saldo);
    fclose(f);
    return 1;
}
