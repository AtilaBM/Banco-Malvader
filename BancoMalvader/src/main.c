#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banco.h"
#include "io.h"
#include "cliente.h"
#define ARQ_CLIENTES "data/clientes.txt"
#define ARQ_MOV "data/movimentos.txt"
static void limpar_entrada(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}
static int menu()
{
    int op;
    printf("\nBanco Malvader\n");
    printf("1 Abrir conta\n");
    printf("2 Encerrar conta\n");
    printf("3 Consultar dados\n");
    printf("4 Alterar dados\n");
    printf("5 Depositar\n");
    printf("6 Sacar\n");
    printf("7 Listar por nome\n");
    printf("8 Listar por conta\n");
    printf("9 Consultar saldo\n");
    printf("0 Sair\n");
    printf("Escolha: ");
    if (scanf("%d", &op) != 1)
    {
        op = 0;
    }
    limpar_entrada();
    return op;
}
static void ler_cliente_base(Cliente *c)
{
    cliente_padrao(c);
    printf("Agencia: ");
    fgets(c->agencia, sizeof c->agencia, stdin);
    c->agencia[strcspn(c->agencia, "\n")] = 0;
    printf("Conta: ");
    fgets(c->conta, sizeof c->conta, stdin);
    c->conta[strcspn(c->conta, "\n")] = 0;
    printf("Nome: ");
    fgets(c->nome, sizeof c->nome, stdin);
    c->nome[strcspn(c->nome, "\n")] = 0;
    printf("CPF: ");
    fgets(c->cpf, sizeof c->cpf, stdin);
    c->cpf[strcspn(c->cpf, "\n")] = 0;
    printf("Data nasc AAAA-MM-DD: ");
    fgets(c->data_nasc, sizeof c->data_nasc, stdin);
    c->data_nasc[strcspn(c->data_nasc, "\n")] = 0;
    printf("Telefone: ");
    fgets(c->telefone, sizeof c->telefone, stdin);
    c->telefone[strcspn(c->telefone, "\n")] = 0;
    printf("Endereco: ");
    fgets(c->endereco, sizeof c->endereco, stdin);
    c->endereco[strcspn(c->endereco, "\n")] = 0;
    printf("CEP: ");
    fgets(c->cep, sizeof c->cep, stdin);
    c->cep[strcspn(c->cep, "\n")] = 0;
    printf("Local: ");
    fgets(c->local, sizeof c->local, stdin);
    c->local[strcspn(c->local, "\n")] = 0;
    printf("Numero casa: ");
    fgets(c->numero_casa, sizeof c->numero_casa, stdin);
    c->numero_casa[strcspn(c->numero_casa, "\n")] = 0;
    printf("Bairro: ");
    fgets(c->bairro, sizeof c->bairro, stdin);
    c->bairro[strcspn(c->bairro, "\n")] = 0;
    printf("Cidade: ");
    fgets(c->cidade, sizeof c->cidade, stdin);
    c->cidade[strcspn(c->cidade, "\n")] = 0;
    printf("Estado UF: ");
    fgets(c->estado, sizeof c->estado, stdin);
    c->estado[strcspn(c->estado, "\n")] = 0;
    printf("Senha: ");
    fgets(c->senha, sizeof c->senha, stdin);
    c->senha[strcspn(c->senha, "\n")] = 0;
}
int main(void)
{
    Banco B;
    banco_init(&B, ARQ_CLIENTES, ARQ_MOV);
    if (!banco_carregar(&B))
    {
        fprintf(stderr, "Erro ao carregar clientes.\n");
        return 1;
    }
    for (;;)
    {
        int op = menu();
        if (op == 0)
            break;
        if (op == 1)
        {
            Cliente c;
            ler_cliente_base(&c);
            if (banco_abrir_conta(&B, &c))
                printf("Conta criada.\n");
            else
                printf("Falha ao criar.\n");
        }
        else if (op == 2)
        {
            char conta[16];
            printf("Conta: ");
            fgets(conta, sizeof conta, stdin);
            conta[strcspn(conta, "\n")] = 0;
            if (banco_encerrar_conta(&B, conta))
                printf("Encerrada.\n");
            else
                printf("Falha.\n");
        }
        else if (op == 3)
        {
            char conta[16];
            printf("Conta: ");
            fgets(conta, sizeof conta, stdin);
            conta[strcspn(conta, "\n")] = 0;
            Cliente c;
            if (banco_consultar_cliente(&B, conta, &c))
                imprimir_dados_cliente(&c);
            else
                printf("Conta nao encontrada.\n");
        }
        else if (op == 4)
        {
            char conta[16];
            printf("Conta a alterar: ");
            fgets(conta, sizeof conta, stdin);
            conta[strcspn(conta, "\n")] = 0;
            Cliente atuais;
            if (!banco_consultar_cliente(&B, conta, &atuais))
            {
                printf("Conta nao encontrada.\n");
                continue;
            }
            Cliente novos = atuais;
            printf("Novo nome (%s): ", atuais.nome);
            fgets(novos.nome, sizeof novos.nome, stdin);
            novos.nome[strcspn(novos.nome, "\n")] = 0;
            if (strlen(novos.nome) == 0)
                strcpy(novos.nome, atuais.nome);
            printf("Novo telefone (%s): ", atuais.telefone);
            fgets(novos.telefone, sizeof novos.telefone, stdin);
            novos.telefone[strcspn(novos.telefone, "\n")] = 0;
            if (strlen(novos.telefone) == 0)
                strcpy(novos.telefone, atuais.telefone);
            printf("Nova senha: ");
            fgets(novos.senha, sizeof novos.senha, stdin);
            novos.senha[strcspn(novos.senha, "\n")] = 0;
            if (strlen(novos.senha) == 0)
                strcpy(novos.senha, atuais.senha);
            if (banco_alterar_dados(&B, conta, &novos))
                printf("Dados alterados.\n");
            else
                printf("Falha na alteracao.\n");
        }
        else if (op == 5)
        {
            char conta[16];
            printf("Conta: ");
            fgets(conta, sizeof conta, stdin);
            conta[strcspn(conta, "\n")] = 0;
            double v;
            printf("Valor: ");
            if (scanf("%lf", &v) != 1)
            {
                v = 0;
            }
            limpar_entrada();
            if (banco_depositar(&B, conta, v))
                printf("Deposito ok.\n");
            else
                printf("Falha no deposito.\n");
        }
        else if (op == 6)
        {
            char conta[16];
            printf("Conta: ");
            fgets(conta, sizeof conta, stdin);
            conta[strcspn(conta, "\n")] = 0;
            double v;
            printf("Valor: ");
            if (scanf("%lf", &v) != 1)
            {
                v = 0;
            }
            limpar_entrada();
            if (banco_sacar(&B, conta, v))
                printf("Saque ok.\n");
            else
                printf("Falha no saque.\n");
        }
        else if (op == 7)
        {
            banco_listar_ordenado_por_nome(&B);
            for (size_t i = 0; i < B.clientes.tam; i++)
                if (B.clientes.dados[i].ativo)
                    printf("%s %s\n", B.clientes.dados[i].conta, B.clientes.dados[i].nome);
        }
        else if (op == 8)
        {
            banco_listar_ordenado_por_conta(&B);
            for (size_t i = 0; i < B.clientes.tam; i++)
                if (B.clientes.dados[i].ativo)
                    printf("%s %s\n", B.clientes.dados[i].conta, B.clientes.dados[i].nome);
        }
        else if (op == 9)
        {
            char conta[16];
            printf("Conta: ");
            fgets(conta, sizeof conta, stdin);
            conta[strcspn(conta, "\n")] = 0;
            Cliente c;
            if (banco_consultar_cliente(&B, conta, &c))
                printf("Saldo atual: %.2f\n", c.saldo);
            else
                printf("Conta nao encontrada.\n");
        }
        else
        {
            printf("Opcao invalida.\n");
        }
    }
    banco_free(&B);
    return 0;
}
