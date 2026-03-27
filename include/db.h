#ifndef DB_H
#define DB_H

int inserir_db(
    const char *idPeca, 
    const char *clientName, 
    const char *descriptionPeca, 
    float pricePeca, 
    const char *paymentMethod, 
    int installments, 
    int paidInstallments, 
    float installmentsValue, 
    float remaining
);

#endif