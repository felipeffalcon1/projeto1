#ifndef UTILS_H
#define UTILS_H

typedef struct {
    char nome[100];
    char cpf[12];
    char senha[7];
    double saldo;
    double bitcoin;
    double ethereum;
    double ripple;
} Investidor;

void carregar_dados_investidor(Investidor *investidor, const char *cpf);
void salvar_dados_investidor(const Investidor *investidor);
void salvar_transacao(const char *cpf, const char *tipo, double valor);

#endif
