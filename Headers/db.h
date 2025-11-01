void insert_credit_sale_db(const char *filename, FILE *file, int idPeca, char descriptionPeca [250], float pricePeca, int installments, float installmentsValue, char clientName[50]) {
        
        file = fopen(filename, "a");
        fprintf(file, "%d;%s;%.2f;%d;%.2f;%s\n", idPeca, descriptionPeca, pricePeca, installments, installmentsValue, clientName);
        fclose(file);
        printf ("\nDADOS DA VENDA\n O ID: %d.\n Descrição: %s.\n Valor: %.2f.\n Parcelas: %d\n Valor da Parcela: %.2f\n Cliete: %s.\n", idPeca, descriptionPeca, pricePeca, installments, installmentsValue, clientName);
        printf ("Dados inseridos no banco de dados\n");
}

void insert_cache_sale_db(const char *filename, FILE *file, int idPeca, char descriptionPeca [250], float pricePeca, char clientName[50]) {
        
    file = fopen(filename, "a");
        fprintf(file, "%d;%s;%.2f;%s\n", idPeca, descriptionPeca, pricePeca, clientName);
        fclose(file);
        printf ("\nDADOS DA VENDA\n O ID: %d.\n Descrição: %s.\n Valor: %.2f.\n Cliete: %s.\n", idPeca, descriptionPeca, pricePeca, clientName);
        printf ("Dados inseridos no banco de dados\n");
}

