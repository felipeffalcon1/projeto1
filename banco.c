#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para armazenar os dados do investidor
typedef struct {
  char nome[100];
  char cpf[12];
  char senha[7];
  double saldo;
  double bitcoin;
  double ethereum;
  double ripple;
} Investidor;

// Estrutura para armazenar as informações de criptomoeda
typedef struct {
  char nome[20];
  double cotacao;
  double taxa_compra;
  double taxa_venda;
} Criptomoeda;

// Funções
void painel_inicial();
void menu_administrador();
void menu_investidor(Investidor *investidor);
void login_administrador();
void login_investidor();
void cadastrar_investidor();
void excluir_investidor();
void consultar_saldo_investidor();
void consultar_extrato_investidor(Investidor *investidor);
void consultar_extrato_admin();
void cadastrar_criptomoeda();
void excluir_criptomoeda();
void atualizar_cotacao();
void carregar_dados_investidor(Investidor *investidor, const char *cpf);
void salvar_dados_investidor(const Investidor *investidor);
void salvar_transacao(const char *cpf, const char *tipo, double valor);
double random_double(double min, double max);
void depositar(Investidor *investidor);
void sacar(Investidor *investidor);
void comprar_criptomoeda(Investidor *investidor);
void vender_criptomoeda(Investidor *investidor);

// Função para gerar um valor aleatório entre min e max
double random_double(double min, double max) {
  return min + (rand() / (RAND_MAX / (max - min)));
}

// Função inicial para escolher o painel de acesso
void painel_inicial() {
  int escolha;

  printf("\n--- SISTEMA DE INVESTIMENTOS ---\n");
  printf("1. Painel Administrador\n");
  printf("2. Painel Investidor\n");
  printf("3. Cadastrar Novo Investidor\n");
  printf("Escolha uma opção: ");
  scanf("%d", &escolha);

  switch (escolha) {
    case 1:
      login_administrador();
      break;
    case 2:
      login_investidor();
      break;
    case 3:
      cadastrar_investidor();
      painel_inicial();
      break;
    default:
      printf("Opção inválida. Tente novamente.\n");
      painel_inicial();
  }
}
// Função de login do administrador com login fixo
void login_administrador() {
  char cpf[12], senha[7];

  printf("Insira seu CPF de administrador: ");
  scanf("%11s", cpf);
  printf("Insira sua senha de administrador: ");
  scanf("%6s", senha);

  if (strcmp(cpf, "12345678900") == 0 && strcmp(senha, "123456") == 0) {
    printf("Login de administrador bem-sucedido.\n");
    menu_administrador();
  } else {
    printf("CPF ou senha de administrador inválidos.\n");
    painel_inicial();
  }
}

// Função de login do investidor
void login_investidor() {
  char cpf[12], senha[7];
  Investidor investidor;

  printf("Insira seu CPF: ");
  scanf("%11s", cpf);
  printf("Insira sua senha de 6 dígitos: ");
  scanf("%6s", senha);

  carregar_dados_investidor(&investidor, cpf);

  if (strlen(investidor.cpf) != 0 && strcmp(investidor.senha, senha) == 0) {
    printf("Login de investidor bem-sucedido.\n");
    menu_investidor(&investidor);
  } else {
    printf("CPF ou senha de investidor inválidos.\n");
    painel_inicial();
  }
}

// Função para exibir o menu do administrador
void menu_administrador() {
  int opcao;

  while (1) {
    printf("\n--- MENU ADMINISTRADOR ---\n");
    printf("1. Cadastrar novo investidor\n");
    printf("2. Excluir investidor\n");
    printf("3. Consultar saldo de um investidor\n");
    printf("4. Consultar extrato de um investidor\n");
    printf("5. Cadastrar nova criptomoeda\n");
    printf("6. Excluir criptomoeda\n");
    printf("7. Atualizar cotação das criptomoedas\n");
    printf("8. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
      case 1:
        cadastrar_investidor();
        break;
      case 2:
        excluir_investidor();
        break;
      case 3:
        consultar_saldo_investidor();
        break;
      case 4:
        consultar_extrato_admin();
        break;
      case 5:
        cadastrar_criptomoeda();
        break;
      case 6:
        excluir_criptomoeda();
        break;
      case 7:
        atualizar_cotacao();
        break;
      case 8:
        printf("Saindo...\n");
        exit(0);
      default:
        printf("Opção inválida.\n");
    }
  }
}
// Função para exibir o menu do investidor
void menu_investidor(Investidor *investidor) {
  int opcao;

  while (1) {
    printf("\n--- MENU INVESTIDOR ---\n");
    printf("1. Consultar saldo\n");
    printf("2. Consultar extrato\n");
    printf("3. Depositar\n");
    printf("4. Sacar\n");
    printf("5. Comprar criptomoedas\n");
    printf("6. Vender criptomoedas\n");
    printf("7. Atualizar cotação\n");
    printf("8. Sair\n");

    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
      case 1:
        printf("Saldo atual: R$%.2f\n", investidor->saldo);
        break;
      case 2:
        consultar_extrato_investidor(investidor);
        break;
      case 3:
        depositar(investidor);
        break;
      case 4:
        sacar(investidor);
        break;
      case 5:
        comprar_criptomoeda(investidor);
        break;
      case 6:
        vender_criptomoeda(investidor);
        break;
      case 7:
        atualizar_cotacao();
        break;
      case 8:
        printf("Saindo do painel de investidor...\n");
        painel_inicial();
        break;
      default:
        printf("Opção inválida.\n");
    }
  }
}

// Função para depositar dinheiro na conta do investidor
void depositar(Investidor *investidor) {
  double valor;
  printf("Informe o valor a ser depositado: ");
  scanf("%lf", &valor);
  if (valor > 0) {
    investidor->saldo += valor;
    salvar_dados_investidor(investidor);
    salvar_transacao(investidor->cpf, "Depósito", valor);
    printf("Depósito de R$%.2f realizado com sucesso.\n", valor);
  } else {
    printf("Valor inválido para depósito.\n");
  }
}
