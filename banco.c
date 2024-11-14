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
