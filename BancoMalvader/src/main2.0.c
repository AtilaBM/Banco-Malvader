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
void imprimir_dados_conta(const Conta *c);


int encontrar_conta_por_numero(const Conta contas[], int qtd, int numero);
int encontrar_conta_por_cpf(const Conta contas[], int qtd, const char *cpf);
int abrir_conta(Conta contas[], int *qtd, int proximo_numero,
                 const char *nome, const char *cpf,
                 const char *agencia, const char *telefone);
int depositar(Conta contas[], int qtd, int numero_conta, double valor);
int sacar(Conta contas[], int qtd, int numero_conta, double valor);
int transferir(Conta contas[], int qtd, int origem, int destino, double valor);
int consultar_conta(const Conta contas[], int qtd, int numero);
int atualizar_dados(Conta contas[], int qtd, int numero,
                     const char *nova_agencia, const char *novo_telefone);



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

int encontrar_conta_por_cpf(const Conta contas[], int qtd, const char *cpf)
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


int abrir_conta(Conta contas[], int *qtd, int proximo_numero,
                 const char *nome, const char *cpf,
                 const char *agencia, const char *telefone)
{
    if (*qtd >= MAX_CONTAS)
    {
        return -2; 
    }
    if (encontrar_conta_por_cpf(contas, *qtd, cpf) != -1)
    {
        return -1; 
    }

    Conta *nova = &contas[*qtd];
    nova->numero = proximo_numero;
    strcpy(nova->nome, nome);
    strcpy(nova->cpf, cpf);
    strcpy(nova->agencia, agencia);
    strcpy(nova->telefone, telefone);
    nova->saldo = 0.0;
    nova->status = ATIVA;

    (*qtd)++;
    return nova->numero;
}


int depositar(Conta contas[], int qtd, int numero_conta, double valor)
{
    if (valor <= 0)
    {
        return -2; 
    }
    int indice = encontrar_conta_por_numero(contas, qtd, numero_conta);

    if (indice == -1) return -1; 
    if (contas[indice].status == ENCERRADA) return -3; 

    contas[indice].saldo += valor;
    return 0; 
}


int sacar(Conta contas[], int qtd, int numero_conta, double valor)
{
    if (valor <= 0)
    {
        return -2;
    }
    int indice = encontrar_conta_por_numero(contas, qtd, numero_conta);

    if (indice == -1) return -1; 
    if (contas[indice].status == ENCERRADA) return -3;  
    if (contas[indice].saldo < valor) return -4; 

    contas[indice].saldo -= valor;
    return 0; 
}


int transferir(Conta contas[], int qtd, int origem, int destino, double valor)
{
    if (valor <= 0) return -2; 

    int indice_origem = encontrar_conta_por_numero(contas, qtd, origem);
    int indice_destino = encontrar_conta_por_numero(contas, qtd, destino);

    if (indice_origem == -1 || indice_destino == -1) return -1; 
    if (origem == destino) return -5; 
    if (contas[indice_origem].status == ENCERRADA || contas[indice_destino].status == ENCERRADA) return -3; 
    if (contas[indice_origem].saldo < valor) return -4; 

    contas[indice_origem].saldo -= valor;
    contas[indice_destino].saldo += valor;
    return 0;
}


void imprimir_dados_conta(const Conta *c)
{
    printf("\n--- Dados da Conta %d ---\n", c->numero);
    printf("Status: %s\n", (c->status == ATIVA ? "ATIVA" : "ENCERRADA"));
    printf("Nome: %s\n", c->nome);
    printf("CPF: %s\n", c->cpf);
    printf("Agência: %s\n", c->agencia);
    printf("Telefone: %s\n", c->telefone);
    printf("Saldo: R$%.2lf\n", c->saldo);
    printf("---------------------------\n");
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
        {
            Conta nova_conta_temp;
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
        {
            int numero;
            double valor;
            printf("\n--- Depósito ---\n");
            printf("Número da Conta: ");
            if (scanf("%d", &numero) != 1) { limpar_entrada(); printf("\nERRO: Entrada inválida para o número da conta.\n"); break; }
            printf("Valor a depositar: ");
            if (scanf("%lf", &valor) != 1) { limpar_entrada(); printf("\nERRO: Entrada inválida para o valor.\n"); break; }
            limpar_entrada();

            int resultado = depositar(contas, qtd_contas, numero, valor);

            if (resultado == 0) printf("\nDepósito de R$%.2lf realizado com sucesso na conta %d.\n", valor, numero);
            else if (resultado == -1) printf("\nERRO: Conta número %d não encontrada.\n", numero);
            else if (resultado == -2) printf("\nERRO: Valor de depósito inválido.\n");
            else if (resultado == -3) printf("\nERRO: Não é possível depositar em uma conta encerrada.\n");
        }
        break;

        
        case 3:
        {
            int numero;
            double valor;
            printf("\n--- Saque ---\n");
            printf("Número da Conta: ");
            if (scanf("%d", &numero) != 1) { limpar_entrada(); printf("\nERRO: Entrada inválida para o número da conta.\n"); break; }
            printf("Valor a sacar: ");
            if (scanf("%lf", &valor) != 1) { limpar_entrada(); printf("\nERRO: Entrada inválida para o valor.\n"); break; }
            limpar_entrada();

            int resultado = sacar(contas, qtd_contas, numero, valor);

            if (resultado == 0) printf("\nSaque de R$%.2lf realizado com sucesso na conta %d.\n", valor, numero);
            else if (resultado == -1) printf("\nERRO: Conta número %d não encontrada.\n", numero);
            else if (resultado == -2) printf("\nERRO: Valor de saque inválido.\n");
            else if (resultado == -3) printf("\nERRO: Não é possível sacar de uma conta encerrada.\n");
            else if (resultado == -4) printf("\nERRO: Saldo insuficiente para realizar o saque.\n");
        }
        break;

        
        case 4:
        {
            int origem, destino;
            double valor;
            printf("\n--- Transferência ---\n");
            printf("Número da Conta de Origem: ");
            if (scanf("%d", &origem) != 1) { limpar_entrada(); printf("\nERRO: Entrada inválida para o número da conta de origem.\n"); break; }
            printf("Número da Conta de Destino: ");
            if (scanf("%d", &destino) != 1) { limpar_entrada(); printf("\nERRO: Entrada inválida para o número da conta de destino.\n"); break; }
            printf("Valor a transferir: ");
            if (scanf("%lf", &valor) != 1) { limpar_entrada(); printf("\nERRO: Entrada inválida para o valor.\n"); break; }
            limpar_entrada();

            int resultado = transferir(contas, qtd_contas, origem, destino, valor);

            if (resultado == 0) printf("\nTransferência de R$%.2lf realizada com sucesso da conta %d para a conta %d.\n", valor, origem, destino);
            else if (resultado == -1) printf("\nERRO: Uma ou ambas as contas não foram encontradas.\n");
            else if (resultado == -2) printf("\nERRO: Valor de transferência inválido.\n");
            else if (resultado == -3) printf("\nERRO: Uma ou ambas as contas estão encerradas.\n");
            else if (resultado == -4) printf("\nERRO: Saldo insuficiente na conta de origem.\n");
            else if (resultado == -5) printf("\nERRO: Contas de origem e destino não podem ser a mesma.\n");
        }
        break;
        
        case 5: 
        {
            int tipbusca;
            int idx = -1;
            char c_cpf[TAM_CPF];
            int c_num;

            printf("CONSULTA DE DADOS \n");
            printf("1. Buscar por CPF\n");
            printf("2. Buscar por Número da Conta\n");
            
            if (scanf("%d", &tipbusca) != 1) {
            printf("\nOpção de busca inválida.\n");
            limpar_entrada();
            break; 
            }
            
            limpar_entrada(); 

            if (tipbusca == 1) { 
            printf("Digite o CPF: ");
            if (fgets(c_cpf, TAM_CPF, stdin) == NULL) break;
            c_cpf[strcspn(c_cpf, "\n")] = 0;
        
            idx = encontrar_conta_por_cpf(contas, qtd_contas, c_cpf); 
            }
    
            else if (tipbusca == 2) { 
            printf("Digite o Numero da Conta: ");
            if (scanf("%d", &c_num) != 1) {
            printf("\nERRO: Entrada inválida para o número da conta.\n");
            limpar_entrada();
            break;
            }
            
            limpar_entrada(); 

            idx = encontrar_conta_por_numero(contas, qtd_contas, c_num);
            } 

            else {
            printf("\nOpção de busca não reconhecida. Escolha 1 ou 2.\n");
            break;
            }
    
            if (idx != -1) {
            imprimir_dados_conta(&contas[idx]);
            } else {
            printf("\nERRO: Conta não encontrada no sistema.\n");
            }
    
            break;
        }
        
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

    printf("\nMenu\n");
    printf("0. Encerrar sistema\n");
    printf("1. Abrir conta\n");
    printf("2. Depositar\n");
    printf("3. Sacar\n");
    printf("4. Transferir\n");
    printf("5. Consultar saldo e dados\n");
    printf("6. Atualizar telefone e agencia\n");
    printf("7. Listar contas\n");
    printf("8. Encerrar conta\n");
    printf("9. Sair (Encerrar Sistema)\n");
    printf("Escolha: ");

    if (scanf("%d", &op) != 1)
    {
        op = -1;
    }
    limpar_entrada();

    if (op == 9) op = 0;

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