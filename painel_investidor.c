#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "painel_investidor.h"
#include "utils.h"

typedef struct {
  char nome[20];
  double cotacao;
  double taxa_compra;
  double taxa_venda;
} Criptomoeda;

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
    }
}

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
        printf("7. Sair\n");

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
                printf("Saindo do painel de investidor...\n");
                return;
            default:
                printf("Opção inválida.\n");
        }
    }
}

void consultar_extrato_investidor(Investidor *investidor) {
  char linha[256];
  FILE *arquivo;

  char filename[20];
  snprintf(filename, sizeof(filename), "%s_extrato.txt", investidor->cpf);
  arquivo = fopen(filename, "r");

  if (arquivo == NULL) {
    printf("Extrato não encontrado.\n");
    return;
  }

  printf("\n--- EXTRATO DE %s ---\n", investidor->nome);
  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    printf("%s", linha);
  }
  fclose(arquivo);
}

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

void sacar(Investidor *investidor) {
  double valor;
  printf("Informe o valor a ser sacado: ");
  scanf("%lf", &valor);
  if (valor > 0 && valor <= investidor->saldo) {
    investidor->saldo -= valor;
    salvar_dados_investidor(investidor);
    salvar_transacao(investidor->cpf, "Saque", valor);
    printf("Saque de R$%.2f realizado com sucesso.\n", valor);
  } else {
    printf("Valor inválido ou saldo insuficiente.\n");
  }
}

void comprar_criptomoeda(Investidor *investidor) {
  char nome[20];
  double quantidade;
  Criptomoeda cripto;
  FILE *arquivo;
  int found = 0;

  printf("Criptomoedas disponíveis para compra:\n");
  arquivo = fopen("criptomoedas.txt", "r");
  if (!arquivo) {
    printf("Erro ao abrir o arquivo de criptomoedas.\n");
    return;
  }

  while (fscanf(arquivo, "%[^,],%lf,%lf,%lf\n", cripto.nome, &cripto.cotacao, &cripto.taxa_compra, &cripto.taxa_venda) != EOF) {
    printf("- %s: Cotação R$%.2f\n", cripto.nome, cripto.cotacao);
  }
  fclose(arquivo);

  printf("Informe o nome da criptomoeda que deseja comprar: ");
  scanf("%19s", nome);

  arquivo = fopen("criptomoedas.txt", "r");
  if (!arquivo) {
    printf("Erro ao abrir o arquivo de criptomoedas.\n");
    return;
  }

  while (fscanf(arquivo, "%[^,],%lf,%lf,%lf\n", cripto.nome, &cripto.cotacao, &cripto.taxa_compra, &cripto.taxa_venda) != EOF) {
    if (strcmp(cripto.nome, nome) == 0) {
      found = 1;
      break;
    }
  }
  fclose(arquivo);

  if (!found) {
    printf("Criptomoeda não encontrada.\n");
    return;
  }

  printf("Cotação atual de %s: R$%.2f\n", cripto.nome, cripto.cotacao);
  printf("Informe a quantidade que deseja comprar: ");
  scanf("%lf", &quantidade);

  if (quantidade <= 0) {
    printf("Quantidade inválida.\n");
    return;
  }

  double valor_total = quantidade * cripto.cotacao * (1 + cripto.taxa_compra);
  if (investidor->saldo >= valor_total) {
    investidor->saldo -= valor_total;
    if (strcmp(cripto.nome, "bitcoin") == 0) {
      investidor->bitcoin += quantidade;
    } else if (strcmp(cripto.nome, "ethereum") == 0) {
      investidor->ethereum += quantidade;
    } else if (strcmp(cripto.nome, "ripple") == 0) {
      investidor->ripple += quantidade;
    } else {
      printf("Criptomoeda desconhecida.\n");
      return;
    }
    salvar_dados_investidor(investidor);
    salvar_transacao(investidor->cpf, "Compra de criptomoeda", valor_total);
    printf("Compra realizada com sucesso. Valor total: R$%.2f\n", valor_total);
  } else {
    printf("Saldo insuficiente.\n");
  }
}

void vender_criptomoeda(Investidor *investidor) {
  char nome[20];
  double quantidade;
  Criptomoeda cripto;
  FILE *arquivo;
  int found = 0;

  printf("Informe o nome da criptomoeda que deseja vender: ");
  scanf("%19s", nome);

  arquivo = fopen("criptomoedas.txt", "r");
  if (!arquivo) {
    printf("Erro ao abrir o arquivo de criptomoedas.\n");
    return;
  }

  while (fscanf(arquivo, "%[^,],%lf,%lf,%lf\n", cripto.nome, &cripto.cotacao, &cripto.taxa_compra, &cripto.taxa_venda) != EOF) {
    if (strcmp(cripto.nome, nome) == 0) {
      found = 1;
      break;
    }
  }
  fclose(arquivo);

  if (!found) {
    printf("Criptomoeda não encontrada.\n");
    return;
  }

  printf("Cotação atual de %s: R$%.2f\n", cripto.nome, cripto.cotacao);
  printf("Informe a quantidade que deseja vender: ");
  scanf("%lf", &quantidade);

  double quantidade_possui = 0;
  if (strcmp(cripto.nome, "bitcoin") == 0) {
    quantidade_possui = investidor->bitcoin;
  } else if (strcmp(cripto.nome, "ethereum") == 0) {
    quantidade_possui = investidor->ethereum;
  } else if (strcmp(cripto.nome, "ripple") == 0) {
    quantidade_possui = investidor->ripple;
  }

  if (quantidade <= quantidade_possui) {
    double valor_total = quantidade * cripto.cotacao * (1 - cripto.taxa_venda);
    investidor->saldo += valor_total;
    if (strcmp(cripto.nome, "bitcoin") == 0) {
      investidor->bitcoin -= quantidade;
    } else if (strcmp(cripto.nome, "ethereum") == 0) {
      investidor->ethereum -= quantidade;
    } else if (strcmp(cripto.nome, "ripple") == 0) {
      investidor->ripple -= quantidade;
    }
    salvar_dados_investidor(investidor);
    salvar_transacao(investidor->cpf, "Venda de criptomoeda", valor_total);
    printf("Venda realizada com sucesso. Valor total: R$%.2f\n", valor_total);
  } else {
    printf("Quantidade insuficiente de %s para vender.\n", cripto.nome);
  }
}

