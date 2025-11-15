#include <libpq-fe.h>
#include <string.h>


void insert_db(
        const char *idPeca, 
        const char *clientName, 
        const char *descriptionPeca, 
        float pricePeca, 
        const char *paymentMethod, 
        int installments, 
        int paidInstallments, 
        float installmentsValue, 
        float remaining) {
        
        /*file = fopen(filename, "a");
        fprintf(file, "%d;%s;%.2f;%d;%.2f;%s\n", idPeca, descriptionPeca, pricePeca, installments, installmentsValue, clientName);
        fclose(file);
        printf ("\nDADOS DA VENDA\n O ID: %d.\n Descrição: %s.\n Valor: %.2f.\n Parcelas: %d\n Valor da Parcela: %.2f\n Cliete: %s.\n", idPeca, descriptionPeca, pricePeca, installments, installmentsValue, clientName);
        printf ("Dados inseridos no banco de dados\n");*/

        //printf ("\nDADOS DA VENDA\n O ID: %d.\n Cliete: %s.\n Descrição: %s.\n Valor: %.2f.\n Forma de Pagamento: %s.\n Parcelas: %d.\n Parcelas Pagas: %d.\n Valor da Parcela: %.2f.\n Saldo Devedor: %.2f.\n", idPeca, clientName, descriptionPeca, pricePeca, paymentMethod, installments, paidInstallments, installmentsValue, remaining);
        //exit (1);
    
        char *conninfo = "dbname=essenza user=postgres password=essenza host=localhost port=5432";

        // Create a connection
        PGconn *conn = PQconnectdb(conninfo);

        // Check if the connection is successful
        if (PQstatus(conn) != CONNECTION_OK) {
                printf("Error while connecting to the database server: %s\n", PQerrorMessage(conn));
                PQfinish(conn);
                exit(1);
        }
        
        // 1. Convertendo todos os valores numéricos para strings (const char *)
        // Buffer para armazenar as strings numéricas. O tamanho 50 é geralmente seguro.
        char pricePeca_str[50];
        char installments_str[50];
        char paidInstallments_str[50];
        char installmentsValue_str[50];
        char remaining_str[50];
        
        // Usamos snprintf/sprintf para converter int/float para string
        sprintf(pricePeca_str, "%.2f", pricePeca);
        sprintf(installments_str, "%d", installments);
        sprintf(paidInstallments_str, "%d", paidInstallments);
        sprintf(installmentsValue_str, "%.2f", installmentsValue);
        sprintf(remaining_str, "%.2f", remaining);

        // 2. Preparando a Query SQL com Marcadores Posicionais ($1, $2, etc.)
        const char *sql_insert = 
                "INSERT INTO VendasSemijoias (id_da_peca, nome_cliente, tipo_semijoia, valor, forma_pagamento, quantidade_parcelas, parcelas_pagas, valor_parcela, restante) "
                "VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9)";

        // 3. Montando o Array de Valores (na ordem correta dos marcadores)
        const int nParams = 9;

        const char *paramValues[nParams];
        paramValues[0] = idPeca;             // $1 (id_da_peca: INT/NUMERIC)
        paramValues[1] = clientName;             // $2 (nome_cliente: TEXT/VARCHAR)
        paramValues[2] = descriptionPeca;        // $3 (tipo_semijoia: TEXT/VARCHAR)
        paramValues[3] = pricePeca_str;          // $4 (valor: NUMERIC/FLOAT)
        paramValues[4] = paymentMethod;          // $5 (forma_pagamento: TEXT/VARCHAR)
        paramValues[5] = installments_str;       // $6 (quantidade_parcelas: INT)
        paramValues[6] = paidInstallments_str;   // $7 (parcelas_pagas: INT)
        paramValues[7] = installmentsValue_str;  // $8 (valor_parcela: NUMERIC/FLOAT)
        paramValues[8] = remaining_str;          // $9 (restante: NUMERIC/FLOAT)

        // 4. Executando a Query com PQexecParams
        PGresult *res = NULL;
        res = PQexecParams(
                conn,
                sql_insert,
                nParams,     
                NULL,        // paramTypes: NULL (para formato texto/deixar PG inferir)
                paramValues, 
                NULL,        // paramLengths: NULL (para strings terminadas em NUL)
                NULL,        // paramFormats: NULL (para formato texto)
                0            // resultFormat: 0 (retorno em texto)
        );

        // 5. Verificação do Resultado
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
                printf("Insert into table failed: %s\n", PQresultErrorMessage(res));
        } else {
                printf ("Dados inseridos no banco de dados com sucesso!\n");
        }
        
        PQclear(res);
        PQfinish(conn);

        printf ("\nDADOS DA VENDA\n O ID: %s.\n Cliente: %s.\n Descrição: %s.\n Valor: %.2f.\n Forma de Pagamento: %s.\n Parcelas: %d.\n Parcelas Pagas: %d.\n Valor da Parcela: %.2f.\n Saldo Devedor: %.2f.\n", idPeca, clientName, descriptionPeca, pricePeca, paymentMethod, installments, paidInstallments, installmentsValue, remaining);
}

void insert_cache_sale_db(const char *filename, FILE *file, int idPeca, char descriptionPeca [250], float pricePeca, char clientName[50]) {
        
    file = fopen(filename, "a");
        fprintf(file, "%d;%s;%.2f;%s\n", idPeca, descriptionPeca, pricePeca, clientName);
        fclose(file);
        printf ("\nDADOS DA VENDA\n O ID: %d.\n Descrição: %s.\n Valor: %.2f.\n Cliete: %s.\n", idPeca, descriptionPeca, pricePeca, clientName);
        printf ("Dados inseridos no banco de dados\n");
}

