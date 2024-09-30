#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para armazenar os dados da conta
typedef struct {
  double saldo;
  double bitcoin;
  double ethereum;
  double ripple;
  double cotacao_bitcoin;
  double cotacao_ethereum;
  double cotacao_ripple;
} Conta;

// Funções
void exibir_menu(Conta *conta);
void consultar_saldo(Conta *conta);
void ver_extrato();
double depositar(Conta *conta);
double sacar(Conta *conta);
void comprar_criptomoedas(Conta *conta);
void vender_criptomoedas(Conta *conta);
void atualizar_cotacao(Conta *conta);
void sair();
void autenticacao();
void salvar_transacao(const char *tipo, const char *detalhes);
void carregar_saldo(Conta *conta);
void reescrever_no_txt(Conta *conta);
void escrever_no_extrato(const char *extrato);

// Função para gerar um valor aleatório entre min e max
double random_double(double min, double max) {
  return min + (rand() / (RAND_MAX / (max - min)));
}

// Função para carregar o saldo da conta a partir de um arquivo
void carregar_saldo(Conta *conta) {
  FILE *arquivo = fopen("saldo.txt", "r");
  if (arquivo == NULL) {
    // Cria o arquivo com valores padrão se não existir
    conta->saldo = 0.0;
    conta->bitcoin = 0.0;
    conta->ethereum = 0.0;
    conta->ripple = 0.0;
    conta->cotacao_bitcoin = 320000;
    conta->cotacao_ethereum = 15000;
    conta->cotacao_ripple = 2.62;

    arquivo = fopen("saldo.txt", "w");
    fprintf(arquivo, "%.2f\n%.4f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n", conta->saldo,
            conta->bitcoin, conta->ethereum, conta->ripple,
            conta->cotacao_bitcoin, conta->cotacao_ethereum,
            conta->cotacao_ripple);
  } else {
    fscanf(arquivo, "%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n", &conta->saldo,
          &conta->bitcoin, &conta->ethereum, &conta->ripple,
          &conta->cotacao_bitcoin, &conta->cotacao_ethereum,
          &conta->cotacao_ripple);
  }
  fclose(arquivo);
}

// Função para reescrever os dados da conta no arquivo após transações
void reescrever_no_txt(Conta *conta) {
  FILE *arquivo = fopen("saldo.txt", "w");
  fprintf(arquivo, "%.2f\n%.4f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n", conta->saldo,
          conta->bitcoin, conta->ethereum, conta->ripple,
          conta->cotacao_bitcoin, conta->cotacao_ethereum,
          conta->cotacao_ripple);
  fclose(arquivo);
}

// Função para salvar as transações no extrato
void escrever_no_extrato(const char *extrato) {
  FILE *arquivo = fopen("extrato.txt", "a");
  fprintf(arquivo, "%s\n", extrato);
  fclose(arquivo);
}

// Função para salvar transações em um arquivo
void salvar_transacao(const char *tipo, const char *detalhes) {
  char transacao[256];
  time_t agora = time(NULL);
  struct tm *t = localtime(&agora);
  snprintf(transacao, sizeof(transacao), "[%02d/%02d/%d %02d:%02d:%02d] %s: %s",
          t->tm_mday, t->tm_mon + 1, t->tm_year + 1900, t->tm_hour, t->tm_min,
          t->tm_sec, tipo, detalhes);
  escrever_no_extrato(transacao);
}

// Função para exibir o menu com as opçoes 
void exibir_menu(Conta *conta) {
  int escolha;
  printf("\n--- MENU ---\n");
  printf("1. Consultar saldo\n");
  printf("2. Ver extrato\n");
  printf("3. Depositar\n");
  printf("4. Sacar\n");
  printf("5. Comprar criptomoedas\n");
  printf("6. Vender criptomoedas\n");
  printf("7. Atualizar cotação\n");
  printf("8. Sair\n");

  printf("Digite sua opção: ");
  scanf("%d", &escolha);

  switch (escolha) {
  case 1:
    consultar_saldo(conta);
    break;
  case 2:
    ver_extrato();
    break;
  case 3:
    conta->saldo = depositar(conta);
    reescrever_no_txt(conta);
    break;
  case 4:
    conta->saldo = sacar(conta);
    reescrever_no_txt(conta);
    break;
  case 5:
    comprar_criptomoedas(conta);
    reescrever_no_txt(conta);
    break;
  case 6:
    vender_criptomoedas(conta);
    reescrever_no_txt(conta);
    break;
  case 7:
    atualizar_cotacao(conta);
    break;
  case 8:
    sair();
    break;
  default:
    printf("Opção inválida. Tente novamente.\n");
    exibir_menu(conta);
  }
}

// Função para consultar o saldo
void consultar_saldo(Conta *conta) {
  printf("Reais: R$%.2f\n", conta->saldo);
  printf("Bitcoin: %.6f\n", conta->bitcoin);
  printf("Ethereum: %.6f\n", conta->ethereum);
  printf("Ripple: %.6f\n", conta->ripple);
  exibir_menu(conta);
}

// Função para ver extrato
void ver_extrato(Conta *conta) {
  FILE *arquivo = fopen("extrato.txt", "r");
  char linha[256];

  if (arquivo == NULL) {
    printf("Nenhum extrato encontrado.\n");
  } else {
    printf("\n--- EXTRATO ---\n");
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
      printf("%s", linha);
    }
    fclose(arquivo);
  }

  exibir_menu(conta);
}

// Funçao deposito
double depositar(Conta *conta) {
  double dep;
  printf("Digite o valor a ser depositado: R$");
  scanf("%lf", &dep);

  if (dep <= 0) {
    printf("Deposito invalido, depositar um valor maior que zero.\n");
  } else {
    conta->saldo += dep;
    printf("Depósito de R$%.2f realizado com sucesso.\n", dep);
    salvar_transacao("Depósito", "Depósito realizado");
  }

  exibir_menu(conta); 
  return conta->saldo;
}

// Função saque
double sacar(Conta *conta) {
  double saque;
  printf("Digite o valor a ser sacado: R$");
  scanf("%lf", &saque);

  if (saque <= 0) {
    printf("Saque invalido, sacar um valor maior que zero.\n");
  } else if (saque > conta->saldo) {
    printf("Saque invalido, você está sem saldo.\n");
  } else {
    conta->saldo -= saque;
    printf("Saque de R$%.2f realizado com sucesso.\n", saque);
    salvar_transacao("Saque", "Saque realizado");
  }

  exibir_menu(conta); 
  return conta->saldo;
}

// Função compra cripto
void comprar_criptomoedas(Conta *conta) {
    int coins;
    double valor_investido;

    printf("\n--- COMPRA DE CRIPTOMOEDAS ---\n");
    printf("1. Bitcoin\n");
    printf("2. Ethereum\n");
    printf("3. Ripple\n");
    printf("Digite o código da criptomoeda que você deseja comprar: ");
    scanf("%d", &coins);

    printf("Digite o valor em reais que você quer investir: R$");
    scanf("%lf", &valor_investido);

    if (valor_investido > conta->saldo) {
        printf("Saldo insuficiente para essa compra.\n");
        return;
    }

    conta->saldo -= valor_investido;  

    if (coins == 1) {
        conta->bitcoin += (valor_investido * 0.98) / conta->cotacao_bitcoin;
        printf("Quantidade de Bitcoin comprada: %.6f\n", conta->bitcoin);
        salvar_transacao("Compra", "Bitcoin");
    } else if (coins == 2) {
        conta->ethereum += (valor_investido * 0.99) / conta->cotacao_ethereum;
        printf("Quantidade de Ethereum comprada: %.6f\n", conta->ethereum);
        salvar_transacao("Compra", "Ethereum");
    } else if (coins == 3) {
        conta->ripple += (valor_investido * 0.99) / conta->cotacao_ripple;
        printf("Quantidade de Ripple comprada: %.6f\n", conta->ripple);
        salvar_transacao("Compra", "Ripple");
    } else {
        printf("Criptomoeda inválida.\n");
    }
}

// Função venda cripto
void vender_criptomoedas(Conta *conta) {
    int coins;
    double qtd_vender;

    printf("\n--- VENDA DE CRIPTOMOEDAS ---\n");
    printf("1. Bitcoin\n");
    printf("2. Ethereum\n");
    printf("3. Ripple\n");
    printf("Digite o código da criptomoeda que você deseja vender: ");
    scanf("%d", &coins);

    if (coins == 1) {
        printf("Digite a quantidade de Bitcoin a ser vendida: ");
        scanf("%lf", &qtd_vender);
        if (qtd_vender <= conta->bitcoin) {
            conta->bitcoin -= qtd_vender;
            conta->saldo += (qtd_vender * conta->cotacao_bitcoin) * 0.98;
            printf("Venda de Bitcoin realizada.\n");
            salvar_transacao("Venda", "Bitcoin");
        } else {
            printf("Quantidade de Bitcoin insuficiente.\n");
        }
    } else if (coins == 2) {
        printf("Digite a quantidade de Ethereum a ser vendida: ");
        scanf("%lf", &qtd_vender);
        if (qtd_vender <= conta->ethereum) {
            conta->ethereum -= qtd_vender;
            conta->saldo += (qtd_vender * conta->cotacao_ethereum) * 0.99;
            printf("Venda de Ethereum realizada.\n");
            salvar_transacao("Venda", "Ethereum");
        } else {
            printf("Quantidade de Ethereum insuficiente.\n");
        }
    } else if (coins == 3) {
        printf("Digite a quantidade de Ripple a ser vendida: ");
        scanf("%lf", &qtd_vender);
        if (qtd_vender <= conta->ripple) {
            conta->ripple -= qtd_vender;
            conta->saldo += (qtd_vender * conta->cotacao_ripple) * 0.99;
            printf("Venda de Ripple realizada.\n");
            salvar_transacao("Venda", "Ripple");
        } else {
            printf("Quantidade de Ripple insuficiente.\n");
        }
    } else {
        printf("Criptomoeda inválida.\n");
    }
}

// Função para atualizar a cotação das criptomoedas
void atualizar_cotacao(Conta *conta) {
    conta->cotacao_bitcoin = random_double(250000, 350000);
    conta->cotacao_ethereum = random_double(12000, 18000);
    conta->cotacao_ripple = random_double(1.8, 3.5);
    printf("Cotações atualizadas:\n");
    printf("Bitcoin: R$%.2f\n", conta->cotacao_bitcoin);
    printf("Ethereum: R$%.2f\n", conta->cotacao_ethereum);
    printf("Ripple: R$%.2f\n", conta->cotacao_ripple);
    salvar_transacao("Cotação", "Cotações atualizadas");
}