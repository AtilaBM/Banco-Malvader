# 🏦 Banco Malvader

## Sobre o Projeto

O **Banco Malvader** é um sistema bancário desenvolvido em linguagem C que simula as operações de um banco real. O projeto permite gerenciar contas de clientes e realizar transações financeiras básicas através de uma interface de terminal.

Este é o trabalho final da disciplina de **Estrutura de Dados e Algoritmos**, desenvolvido em grupo de 5 alunos.

## O que o Sistema Faz

### Gerenciamento de Contas
- Abrir novas contas de clientes
- Encerrar contas existentes
- Consultar informações de clientes
- Alterar dados cadastrais

### Operações Bancárias
- Consultar saldo
- Realizar depósitos
- Realizar saques
- Visualizar extrato de movimentações

### Relatórios
- Listar clientes por ordem alfabética
- Listar clientes por número de conta

## Informações Cadastradas

Cada cliente possui as seguintes informações:
- Agência
- Número da Conta
- Nome completo
- CPF
- Data de nascimento
- Telefone
- Endereço completo (rua, CEP, número, bairro, cidade, estado)
- Senha
- Saldo

## Como Usar

1. Execute o programa no terminal
2. Escolha a operação desejada no menu principal
3. Siga as instruções na tela
4. Os dados são salvos automaticamente

## Armazenamento de Dados

O sistema salva todas as informações em arquivos de texto:
- **clientes.txt**: armazena os dados de todos os clientes
- **movimentos.txt**: registra todas as transações realizadas

Os dados são mantidos mesmo após fechar o programa.

## Regras Importantes

- Só é possível encerrar uma conta se o saldo estiver zerado
- Não é permitido sacar mais dinheiro do que há disponível na conta
- Cada número de conta é único no sistema
- Todas as operações são registradas automaticamente no histórico

---

## 👥 Contributors

<a href="https://github.com/seu-usuario/BancoMalvader/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=AtilaBM/BancoMalvader" />
</a>

---

**Disciplina**: Estrutura de Dados e Algoritmos

**Instituição**: Universidade Católica de Brasília

**Ano**: 2025
