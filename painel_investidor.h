#ifndef PAINEL_INVESTIDOR_H
#define PAINEL_INVESTIDOR_H

#include "utils.h"

void login_investidor();
void menu_investidor(Investidor *investidor);
void consultar_extrato_investidor(Investidor *investidor);
void depositar(Investidor *investidor);
void sacar(Investidor *investidor);
void comprar_criptomoeda(Investidor *investidor);
void vender_criptomoeda(Investidor *investidor);

#endif
