# 🏦 Banco Malvader

## Sobre o Projeto
O **Banco Malvader** é um sistema bancário desenvolvido em linguagem C que simula as operações de um banco real. O projeto permite gerenciar contas de clientes e realizar transações financeiras básicas através de uma interface de terminal.

Este é o trabalho final da disciplina de **Estrutura de Dados e Algoritmos**, desenvolvido em grupo de 5 alunos.

## O que o Sistema Faz

### Gerenciamento de Contas
- Abrir novas contas de clientes
- Encerrar contas existentes (apenas com saldo zerado)
- Consultar informações de contas por CPF ou número
- Atualizar telefone e agência

### Operações Bancárias
- Consultar saldo e dados da conta
- Realizar depósitos
- Realizar saques (com validação de saldo)
- Realizar transferências entre contas
- Baixar dados da conta em arquivo

### Relatórios
- Listar todas as contas cadastradas no sistema

## Informações Cadastradas
Cada conta possui as seguintes informações:
- Número da Conta (gerado automaticamente)
- Nome completo
- CPF (único no sistema)
- Agência (gerada automaticamente)
- Telefone
- Saldo
- Status (Ativa/Encerrada)

## Como Usar
1. Compile o programa:
```bash
   gcc main.c -o main
```
2. Execute o programa no terminal:
```bash
   ./main
```
3. Escolha a operação desejada no menu principal (0-9)
4. Siga as instruções na tela

## Funcionalidades do Menu
- **1. Abrir conta**: Cadastrar nova conta bancária
- **2. Depositar**: Adicionar valores à conta
- **3. Sacar**: Retirar valores da conta
- **4. Transferir**: Transferir valores entre contas
- **5. Consultar saldo e dados**: Buscar por CPF ou número da conta
- **6. Atualizar telefone e agência**: Modificar dados cadastrais
- **7. Listar contas**: Exibir todas as contas do sistema
- **8. Encerrar conta**: Desativar conta (apenas com saldo zero)
- **9. Baixar dados para arquivo**: Salvar dados da conta em arquivo
- **0. Encerrar sistema**: Sair do programa

## Armazenamento de Dados
O sistema salva os dados das contas em arquivo de texto:
- **data/clientes.txt**: armazena os dados da conta consultada

## Regras Importantes
- Só é possível encerrar uma conta se o saldo estiver zerado
- Não é permitido sacar mais dinheiro do que há disponível na conta
- Cada CPF pode ter apenas uma conta ativa no sistema
- Cada número de conta é único e gerado automaticamente
- Contas encerradas não podem realizar operações bancárias
- O sistema suporta até 100 contas simultâneas

## Estrutura do Projeto
```
BancoMalvader/
├── src/
│   └── main.c          # Código principal do sistema
├── data/
│   └── clientes.txt    # Arquivo de saída com dados das contas
└── README.md           # Documentação do projeto
```

## Contas Pré-cadastradas (Para Teste)
O sistema já inicia com 3 contas cadastradas:
- **Conta 1001**: Alice Silva (CPF: 118.901.011-21) - Saldo: R$ 500,00
- **Conta 1002**: Bruno Mendes (CPF: 222.122.933-22) - Saldo: R$ 2.000,50
- **Conta 1003**: Carlos Neto (CPF: 596.309.933-23) - Encerrada

---

## 👥 Contributors
<a href="https://github.com/AtilaBM/Banco-Malvader/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=AtilaBM/Banco-Malvader" />
</a>

---

**Disciplina**: Estrutura de Dados e Algoritmos  
**Instituição**: Universidade Católica de Brasília  
**Ano**: 2025
