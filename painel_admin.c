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

// Outras funções
void cadastrar_investidor() {
  Investidor investidor;
  FILE *arquivo = fopen("investidores.txt", "a");

  if (!arquivo) {
    printf("Erro ao abrir o arquivo de investidores.\n");
    return;
  }

  printf("Informe o nome do investidor: ");
  scanf(" %[^\n]", investidor.nome);
  printf("Informe o CPF do investidor: ");
  scanf("%11s", investidor.cpf);
  printf("Informe a senha de 6 dígitos: ");
  scanf("%6s", investidor.senha);

  investidor.saldo = 0;
  investidor.bitcoin = 0;
  investidor.ethereum = 0;
  investidor.ripple = 0;

  fprintf(arquivo, "%s,%s,%s,%.2f,%.4f,%.4f,%.4f\n", investidor.nome,
          investidor.cpf, investidor.senha, investidor.saldo,
          investidor.bitcoin, investidor.ethereum, investidor.ripple);
  fclose(arquivo);

  printf("Investidor cadastrado com sucesso.\n");
}
void excluir_investidor() {
  char cpf[12];
  char confirma;
  Investidor investidor;
  FILE *arquivo, *temp;

  printf("Informe o CPF do investidor a ser excluído: ");
  scanf("%11s", cpf);

  carregar_dados_investidor(&investidor, cpf);
  if (strlen(investidor.cpf) == 0) {
    printf("Investidor não encontrado.\n");
    return;
  }

  printf("Confirma a exclusão de %s (CPF: %s)? (s/n): ", investidor.nome,
         investidor.cpf);
  scanf(" %c", &confirma);

  if (confirma == 's') {
    arquivo = fopen("investidores.txt", "r");
    temp = fopen("temp.txt", "w");

    while (fscanf(arquivo, "%[^,],%[^,],%[^,],%lf,%lf,%lf,%lf\n",
                  investidor.nome, investidor.cpf, investidor.senha,
                  &investidor.saldo, &investidor.bitcoin, &investidor.ethereum,
                  &investidor.ripple) != EOF) {
      if (strcmp(investidor.cpf, cpf) != 0) {
        fprintf(temp, "%s,%s,%s,%.2f,%.4f,%.4f,%.4f\n", investidor.nome,
                investidor.cpf, investidor.senha, investidor.saldo,
                investidor.bitcoin, investidor.ethereum, investidor.ripple);
      }
    }

    fclose(arquivo);
    fclose(temp);

    remove("investidores.txt");
    rename("temp.txt", "investidores.txt");

    printf("Investidor excluído com sucesso.\n");
  } else {
    printf("Operação cancelada.\n");
  }
}
