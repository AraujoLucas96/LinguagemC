#include <stdio.h>
#include <stdlib.h>
#include "../include/db.h"

int insert_db(
    const char *idPeca, 
    const char *clientName, 
    const char *descriptionPeca, 
    float pricePeca, 
    const char *paymentMethod, 
    int installments, 
    int paidInstallments, 
    float installmentsValue, 
    float remaining) {

    char comando[512];

    snprintf(comando, sizeof(comando),
        "./scripts/database/insert.sh \"%s\" \"%s\" \"%s\" \"%f\" \"%s\" \"%d\" \"%d\" \"%f\" \"%f\"",
        idPeca, clientName, descriptionPeca, pricePeca,
        paymentMethod, installments, paidInstallments,
        installmentsValue, remaining
    );

    int returnCode = system(comando);

    if (returnCode != 0) {
        return 1;
    }

    return 0;
}