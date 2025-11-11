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
    int numero; 
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char agencia[TAM_AGENCIA];
    char telefone[TAM_TELEFONE];
    double saldo;
    int status; 
} Conta;                                 

static void limpar_entrada(void);
static int menu(void);
static void ler_cliente_base(Conta *c);


int encontrar_conta_por_numero(const Conta contas[], int qtd, int numero)
{
    for (int i = 0; i < qtd; i++)
    {
        if (contas[i].numero == numero)
        {
            return i;
        }
    }
    return -1;
}


int encontrar_conta_por_cpf(const Conta contas[], int qtd, const char* cpf)
{
    for (int i = 0; i < qtd; i++)
    {
      
        if (contas[i].status == ATIVA && strcmp(contas[i].cpf, cpf) == 0)
        {
            return i;
        }
    }
    return -1;
}


int abrir_conta(Conta contas[], int* qtd, int proximo_numero,
               const char* nome, const char* cpf,
               const char* agencia, const char* telefone)
{
   
    if (*qtd >= MAX_CONTAS)
    {
        return -2;
    }

   
    if (encontrar_conta_por_cpf(contas, *qtd, cpf) != -1)
    {
        return -1; 
    }

    Conta* nova = &contas[*qtd];
    

    (*nova).numero = proximo_numero;
    
    strcpy((*nova).nome, nome);
    strcpy((*nova).cpf, cpf);
    strcpy((*nova).agencia, agencia);
    strcpy((*nova).telefone, telefone);
    
    (*nova).saldo = 0.0; 
    (*nova).status = ATIVA; 

 
    (*qtd)++; 
    return (*nova).numero; 
}


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
            {Conta nova_conta_temp;
                printf("\n--- Abertura de Conta ---\n");
                ler_cliente_base(&nova_conta_temp); 
                
                int resultado = abrir_conta(contas, &qtd_contas, proximo_numero,
                                            nova_conta_temp.nome, nova_conta_temp.cpf,
                                            nova_conta_temp.agencia, nova_conta_temp.telefone);

                if (resultado > 0) 
                {
                    printf("\nConta criada com sucesso! Número da Conta: %d\n", resultado);
                    proximo_numero++; 
                }
                else 
                {
                    if (resultado == -2)
                        printf("\nERRO: Limite de contas atingido! Nenhuma conta aberta.\n");
                    else if (resultado == -1)
                        printf("\nERRO: CPF já cadastrado em uma conta ativa. Nenhuma conta aberta.\n");
                    else
                        printf("\nERRO: Falha desconhecida ao abrir a conta.\n");
                }
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
        op = 0; 
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
