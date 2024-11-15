#include <stdio.h>
#include <stdlib.h>
#include "painel_admin.h"
#include "painel_investidor.h"

void painel_inicial() {
    int escolha;

    printf("\n--- SISTEMA DE INVESTIMENTOS ---\n");
    printf("1. Painel Administrador\n");
    printf("2. Painel Investidor\n");
    printf("Escolha uma opção: ");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            login_administrador();
            break;
        case 2:
            login_investidor();
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
    }
}

int main() {
    srand(time(NULL));
    painel_inicial();
    return 0;
}
