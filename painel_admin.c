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

void consultar_saldo_investidor() {
  char cpf[12];
  Investidor investidor;

  printf("Informe o CPF do investidor: ");
  scanf("%11s", cpf);

  carregar_dados_investidor(&investidor, cpf);
  if (strlen(investidor.cpf) == 0) {
    printf("Investidor não encontrado.\n");
    return;
  }

  printf("Saldo de %s (CPF: %s): R$%.2f\n", investidor.nome, investidor.cpf,
         investidor.saldo);
}

void consultar_extrato_admin() {
  char cpf[12];
  char linha[256];
  FILE *arquivo;

  printf("Informe o CPF do investidor: ");
  scanf("%11s", cpf);

  char filename[20];
  snprintf(filename, sizeof(filename), "%s_extrato.txt", cpf);
  arquivo = fopen(filename, "r");

  if (arquivo == NULL) {
    printf("Extrato não encontrado para o CPF informado.\n");
    return;
  }

  printf("\n--- EXTRATO DE %s ---\n", cpf);
  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    printf("%s", linha);
  }
  fclose(arquivo);
}

void cadastrar_criptomoeda() {
  Criptomoeda cripto;
  FILE *arquivo = fopen("criptomoedas.txt", "a");

  if (!arquivo) {
    printf("Erro ao abrir o arquivo de criptomoedas.\n");
    return;
  }

  printf("Informe o nome da criptomoeda: ");
  scanf("%19s", cripto.nome);
  printf("Informe a cotação inicial: ");
  scanf("%lf", &cripto.cotacao);
  printf("Informe a taxa de compra (em decimal, ex: 0.02 para 2%%): ");
  scanf("%lf", &cripto.taxa_compra);
  printf("Informe a taxa de venda (em decimal, ex: 0.02 para 2%%): ");
  scanf("%lf", &cripto.taxa_venda);

  fprintf(arquivo, "%s,%.2f,%.2f,%.2f\n", cripto.nome, cripto.cotacao,
          cripto.taxa_compra, cripto.taxa_venda);
  fclose(arquivo);

  printf("Criptomoeda cadastrada com sucesso.\n");
}
