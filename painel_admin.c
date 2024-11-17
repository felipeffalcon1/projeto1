#include "painel_admin.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
  char nome[20];
  double cotacao;
  double taxa_compra;
  double taxa_venda;
} Criptomoeda;

void login_administrador() {
  char cpf[12], senha[7];

  printf("Insira seu CPF de administrador: ");
  scanf("%11s", cpf);
  printf("Insira sua senha de administrador: ");
  scanf("%6s", senha);

  // Verificação fixa de CPF e senha
  if (strcmp(cpf, "12345678900") == 0 && strcmp(senha, "123456") == 0) {
    printf("Login de administrador bem-sucedido.\n");
    menu_administrador();
  } else {
    printf("CPF ou senha de administrador inválidos.\n");
  }
}

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
