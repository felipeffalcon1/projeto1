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