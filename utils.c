#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

double random_double(double min, double max) {
    return min + (rand() / (RAND_MAX / (max - min)));
}


void carregar_dados_investidor(Investidor *investidor, const char *cpf) {
  FILE *arquivo = fopen("investidores.txt", "r");

  if (!arquivo) {
    printf("Erro ao abrir o arquivo de investidores.\n");
    return;
  }

  while (fscanf(arquivo, "%[^,],%[^,],%[^,],%lf,%lf,%lf,%lf\n", investidor->nome, investidor->cpf, investidor->senha, &investidor->saldo, &investidor->bitcoin, &investidor->ethereum, &investidor->ripple) != EOF) {
    if (strcmp(investidor->cpf, cpf) == 0) {
      fclose(arquivo);
      return;
    }
  }

  fclose(arquivo);
  investidor->cpf[0] = '\0';  
}


void salvar_dados_investidor(const Investidor *investidor) {
  FILE *arquivo, *temp;
  Investidor inv;

  arquivo = fopen("investidores.txt", "r");
  temp = fopen("temp.txt", "w");
  if (!arquivo || !temp) {
    printf("Erro ao abrir os arquivos para salvar dados do investidor.\n");
    return;
  }

  while (fscanf(arquivo, "%[^,],%[^,],%[^,],%lf,%lf,%lf,%lf\n", inv.nome, inv.cpf, inv.senha, &inv.saldo, &inv.bitcoin, &inv.ethereum, &inv.ripple) != EOF) {
    if (strcmp(inv.cpf, investidor->cpf) == 0) {
      fprintf(temp, "%s,%s,%s,%.2f,%.4f,%.4f,%.4f\n", investidor->nome, investidor->cpf, investidor->senha, investidor->saldo, investidor->bitcoin, investidor->ethereum, investidor->ripple);
    } else {
      fprintf(temp, "%s,%s,%s,%.2f,%.4f,%.4f,%.4f\n", inv.nome, inv.cpf, inv.senha, inv.saldo, inv.bitcoin, inv.ethereum, inv.ripple);
    }
  }

  fclose(arquivo);
  fclose(temp);

  remove("investidores.txt");
  rename("temp.txt", "investidores.txt");
}


    void salvar_transacao(const char *cpf, const char *tipo, double valor) {
      char filename[20];
      FILE *arquivo;
      snprintf(filename, sizeof(filename), "%s_extrato.txt", cpf);
      arquivo = fopen(filename, "a");
      if (!arquivo) {
        printf("Erro ao abrir o arquivo de extrato.\n");
        return;
      }
      time_t t = time(NULL);
      struct tm tm = *localtime(&t);
      fprintf(arquivo, "%02d/%02d/%04d %02d:%02d:%02d - %s: R$%.2f\n",
              tm.tm_mday, tm.tm_mon +1, tm.tm_year + 1900,
              tm.tm_hour, tm.tm_min, tm.tm_sec, tipo, valor);
      fclose(arquivo);
    }




