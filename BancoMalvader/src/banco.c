#include "banco.h"
#include "io.h"
#include "conta.h"
#include "quicksort.h"
#include <string.h>
void banco_init(Banco *B, const char *ac, const char *am)
{
    lista_init(&B->clientes);
    strncpy(B->arquivo_clientes, ac, sizeof B->arquivo_clientes);
    B->arquivo_clientes[sizeof B->arquivo_clientes - 1] = 0;
    strncpy(B->arquivo_mov, am, sizeof B->arquivo_mov);
    B->arquivo_mov[sizeof B->arquivo_mov - 1] = 0;
}
void banco_free(Banco *B) { lista_free(&B->clientes); }
int banco_carregar(Banco *B) { return carregar_clientes(B->arquivo_clientes, &B->clientes); }
int banco_salvar(const Banco *B) { return salvar_clientes(B->arquivo_clientes, &B->clientes); }
int banco_buscar_idx_por_conta(const Banco *B, const char *conta) { return lista_find_conta(&B->clientes, conta); }
int banco_consultar_cliente(const Banco *B, const char *conta, Cliente *out)
{
    int idx = banco_buscar_idx_por_conta(B, conta);
    if (idx < 0)
        return 0;
    if (out)
        *out = B->clientes.dados[idx];
    return 1;
}
int banco_abrir_conta(Banco *B, const Cliente *novo)
{
    int ok = abrir_conta(&B->clientes, novo);
    if (!ok)
        return 0;
    return banco_salvar(B);
}
int banco_encerrar_conta(Banco *B, const char *conta)
{
    int ok = encerrar_conta(&B->clientes, conta);
    if (!ok)
        return 0;
    return banco_salvar(B);
}
int banco_alterar_dados(Banco *B, const char *conta, const Cliente *novos)
{
    int idx = banco_buscar_idx_por_conta(B, conta);
    if (idx < 0)
        return 0;
    Cliente *c = &B->clientes.dados[idx];
    Cliente novo = *c;
    strncpy(novo.nome, novos->nome, sizeof novo.nome);
    strncpy(novo.cpf, novos->cpf, sizeof novo.cpf);
    strncpy(novo.data_nasc, novos->data_nasc, sizeof novo.data_nasc);
    strncpy(novo.telefone, novos->telefone, sizeof novo.telefone);
    strncpy(novo.endereco, novos->endereco, sizeof novo.endereco);
    strncpy(novo.cep, novos->cep, sizeof novo.cep);
    strncpy(novo.local, novos->local, sizeof novo.local);
    strncpy(novo.numero_casa, novos->numero_casa, sizeof novo.numero_casa);
    strncpy(novo.bairro, novos->bairro, sizeof novo.bairro);
    strncpy(novo.cidade, novos->cidade, sizeof novo.cidade);
    strncpy(novo.estado, novos->estado, sizeof novo.estado);
    strncpy(novo.senha, novos->senha, sizeof novo.senha);
    *c = novo;
    return banco_salvar(B);
}
int banco_depositar(Banco *B, const char *conta, double valor)
{
    int idx = banco_buscar_idx_por_conta(B, conta);
    if (idx < 0)
        return 0;
    if (!depositar(&B->clientes.dados[idx], valor))
        return 0;
    if (!registrar_mov(B->arquivo_mov, conta, "DEPOSITO", valor, B->clientes.dados[idx].saldo))
        return 0;
    return banco_salvar(B);
}
int banco_sacar(Banco *B, const char *conta, double valor)
{
    int idx = banco_buscar_idx_por_conta(B, conta);
    if (idx < 0)
        return 0;
    if (!sacar(&B->clientes.dados[idx], valor))
        return 0;
    if (!registrar_mov(B->arquivo_mov, conta, "SAQUE", valor, B->clientes.dados[idx].saldo))
        return 0;
    return banco_salvar(B);
}
void banco_listar_ordenado_por_nome(Banco *B)
{
    if (B->clientes.tam == 0)
        return;
    quicksort_nome(B->clientes.dados, 0, (int)B->clientes.tam - 1);
}
void banco_listar_ordenado_por_conta(Banco *B)
{
    if (B->clientes.tam == 0)
        return;
    quicksort_conta(B->clientes.dados, 0, (int)B->clientes.tam - 1);
}
