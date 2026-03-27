#include <stdio.h>
#include <stdlib.h>
#include "../include/db.h"

int inserir_db(
    const char *id_peca, 
    const char *nome_cliente, 
    const char *descricao_peca, 
    float preco_peca, 
    const char *metodo_pagamento, 
    int parcelas, 
    int parcelas_pagas, 
    float valor_parcelas, 
    float valor_restante_pagar) {

    //printf ("\nDADOS DA VENDA\n O ID: %s.\n Cliente: %s.\n Descrição: %s.\n Valor: %.2f.\n Metodo de Pagamento: %s.\n Parcelas: %d.\n Parcelas Pagas: %d.\n Valor da Parcela: %.2f.\n Restante: %.2f.\n",
     //    id_peca, nome_cliente, descricao_peca, preco_peca, metodo_pagamento, parcelas, parcelas_pagas, valor_parcelas, valor_restante_pagar);

    char comando[512];

    snprintf(comando, sizeof(comando),
        "./scripts/database/insert.sh \"%s\" \"%s\" \"%s\" \"%.2f\" \"%s\" \"%d\" \"%d\" \"%.2f\" \"%.2f\"",
        id_peca, nome_cliente, descricao_peca, preco_peca, metodo_pagamento, parcelas, parcelas_pagas, valor_parcelas, valor_restante_pagar
    );

    int returnCode = system(comando);

    if (returnCode != 0) {
        return 1;
    }

    return 0;
}