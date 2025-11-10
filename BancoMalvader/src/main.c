#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CONTAS 100
#define TAM_NOME 100
#define TAM_CPF 15
#define TAM_AGENCIA 10
#define TAM_TELEFONE 20
#define ATIVA 1
#define ENCERRADA 0

typedef struct
{
    int numero; /* número único da conta */
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char agencia[TAM_AGENCIA];
    char telefone[TAM_TELEFONE];
    double saldo;
    int status; /* ATIVA ou ENCERRADA */
} Conta;

static void limpar_entrada(void);
static int menu();

static void ler_cliente_base(Conta *c);

// int encontrar_conta_por_numero(const Conta contas[], int qtd, int numero);
// int encontrar_conta_por_cpf(const Conta contas[], int qtd, const char *cpf);

// int abrir_conta(Conta contas[], int *qtd, int proximo_numero,
//                 const char *nome, const char *cpf,
//                 const char *agencia, const char *telefone);

// int depositar(Conta contas[], int qtd, int numero, double valor);
// int sacar(Conta contas[], int qtd, int numero, double valor);
// int transferir(Conta contas[], int qtd, int origem, int destino, double valor);

// int atualizar_contato(Conta contas[], int qtd, int numero,
//                       const char *novo_telefone, const char *nova_agencia);

// int encerrar_conta(Conta contas[], int qtd, int numero);

// void listar_contas(const Conta contas[], int qtd, int filtro_status); /* ATIVA, ENCERRADA ou ambos */
// void mostrar_dados(const Conta *c);

int main(void)
{

    int op = menu();

    switch (op == 1)
    {
    case 0:
        break;
    case 1:
        // printf("Digite o seu CPF:");
        // fgets(cpf, TAM_CPF, stdin);
         Conta c;
            ler_cliente_base(&c);
        
        break;

    default:
        break;
    }
}

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

static void ler_cliente_base(Conta *c)
{
    cliente_padrao(c);
    printf("Agencia: ");
    fgets(c->agencia, sizeof c->agencia, stdin);
    c->agencia[strcspn(c->agencia, "\n")] = 0;
    printf("Conta: ");
    printf("Nome: ");
    fgets(c->nome, sizeof c->nome, stdin);
    c->nome[strcspn(c->nome, "\n")] = 0;
    printf("CPF: ");
    fgets(c->cpf, sizeof c->cpf, stdin);
    c->cpf[strcspn(c->cpf, "\n")] = 0;
    printf("Telefone: ");
    fgets(c->telefone, sizeof c->telefone, stdin);
    c->telefone[strcspn(c->telefone, "\n")] = 0;
}
