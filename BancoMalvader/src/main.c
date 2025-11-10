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
static int menu(void);
static void ler_cliente_base(Conta *c);

int main(void)
{
    Conta contas[MAX_CONTAS];
    int qtd_contas = 0;
    int proximo_numero = 1;
    int op;

    do
    {
        op = menu();
        
        switch (op)
        {
        case 0:
            printf("\nEncerrando sistema...\n");
            break;
            
        case 1:
            if (qtd_contas >= MAX_CONTAS)
            {
                printf("\nLimite de contas atingido!\n");
            }
            else
            {
                Conta nova_conta;
                ler_cliente_base(&nova_conta);
                nova_conta.numero = proximo_numero++;
                nova_conta.saldo = 0.0;
                nova_conta.status = ATIVA;
                contas[qtd_contas++] = nova_conta;
                printf("\nConta criada com sucesso! Número da Conta: %d\n", nova_conta.numero);
            }
            break;
            
        case 2:
            printf("\n'Encerrar conta'.\n");
            break;
            
        case 3:
            printf("\n'Consultar dados'.\n");
            break;
            
        case 4:
            printf("\n'Alterar dados'.\n");
            break;
            
        case 5:
            printf("\n'Depositar'.\n");
            break;
            
        case 6:
            printf("\n'Sacar'.\n");
            break;
            
        case 7:
            break;
            
        case 8:
            printf("\n'Listar por conta'.\n");
            break;
            
        case 9:
            printf("\n'Consultar saldo'.\n");
            break;
            
        default:
            printf("\nOpção inválida! Tente novamente.\n");
            break;
        }
    } while (op != 0);

    return 0;
}

static void limpar_entrada(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

static int menu(void)
{
    int op;
    
    printf("\n========== Banco Malvader ==========\n");
    printf("1 - Abrir conta\n");
    printf("2 - Encerrar conta\n");
    printf("3 - Consultar dados\n");
    printf("4 - Alterar dados\n");
    printf("5 - Depositar\n");
    printf("6 - Sacar\n");
    printf("7 - Listar por nome\n");
    printf("8 - Listar por conta\n");
    printf("9 - Consultar saldo\n");
    printf("0 - Sair\n");
    printf("====================================\n");
    printf("Escolha: ");
    
    if (scanf("%d", &op) != 1)
    {
        op = 0; /* valor inválido para forçar mensagem de erro */
    }
    limpar_entrada();
    
    return op;
}

static void ler_cliente_base(Conta *c)
{
    
    printf("Agência: ");
    fgets(c->agencia, sizeof c->agencia, stdin);
    c->agencia[strcspn(c->agencia, "\n")] = 0;
    
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