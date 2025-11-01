#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include "Headers/checks.h"
#include "Headers/db.h"

void main_menu();

void stop_program() {
	
	printf ("\nFinalizando o programa\n");
	sleep(1);
        exit(0);

}


const char *filename = "dbfile";
FILE *file;

int check_file() {

        if (access(filename, F_OK) != 0) {
                printf ("Arquivo usado como banco de dados não existe. Saindo...\n");
                sleep(1);
                exit(1);
        }

        file = fopen(filename, "a");
        if (file == NULL){
                printf("Erro ao abrir o arquivo usado como banco de dados. Entre em contato com o administrador do sistema.\n");
                printf("Saindo...\n");
                exit(1);
        }

        fclose(file);   
return 0;
}

void cash_sale() {
        //short options;
        printf ("\nMENU VENDA A VISTA\n");

        
        char descriptionPeca[250];
        float pricePeca;
        char clientName[50];

        printf ("Digite o ID da peça: ");
        getchar();
        int idPeca = intValidation();

        printf ("Digite a descrição: ");
        stringValidation(descriptionPeca, 250);
        
        printf ("Digite o valor da peça: ");
        scanf ("%f", &pricePeca);
        getchar();
        
        printf ("Digite o nome do cliente: ");
        //scanf ("%[^\n]%*c", clientName);
        fgets (clientName, 50, stdin);
        clientName[strcspn(clientName, "\n")] = '\0';

        //printf ("\nDADOS DA VENDA\n O ID: %d.\n Descrição: %s.\n Valor: %.2f.\n Cliete: %s.\n", idPeca, descriptionPeca, pricePeca, clientName);

        insert_cache_sale_db(filename, file, idPeca, descriptionPeca, pricePeca, clientName);

        short options;
        printf ("\n0 - Voltar ao menu principal\n");
        printf ("10 - Finalizar o programa\n");
        scanf("%hi", &options);

        switch (options) {
                case 0: 
                        main_menu();
		case 10: 
			stop_program();
			break;
                default:
                        printf("Escolha uma opção válida. Voltando ao menu principal\n");
                        sleep(1);
                        main_menu();
                        break;
        }


}

void credit_sale() {

        printf ("\nMENU VENDA PARCELADA\n");

        char descriptionPeca[250];
        float pricePeca;
        char clientName[50];

        printf ("Digite o ID da peça: ");
        getchar();
        int idPeca = intValidation();

        printf ("Digite a descrição: ");
        stringValidation(descriptionPeca, 250);
        
        printf ("Digite o valor da peça: ");
        scanf ("%f", &pricePeca);
        //getchar();

        printf ("Digite a quantidade de parcelas: ");
        int installments = intValidation();

        float installmentsValue = pricePeca / installments;

        printf ("Digite o nome do cliente: ");
        //scanf ("%[^\n]%*c", clientName);
        fgets (clientName, 50, stdin);
        clientName[strcspn(clientName, "\n")] = '\0';

        insert_credit_sale_db(filename, file, idPeca, descriptionPeca, pricePeca, installments, installmentsValue, clientName);

        short options;
        printf ("\n0 - Voltar ao menu principal\n");
        printf ("10 - Finalizar o programa\n");
        scanf("%hi", &options);

        switch (options) {
                case 0: 
                        main_menu();
		case 10: 
			stop_program();
			break;
                default:
                        printf("Escolha uma opção válida. Voltando ao menu principal\n");
                        sleep(1);
                        main_menu();
                        break;
        }

}

void sales_menu() {

        short options;
        printf ("\nMENU DO CONTROLE DE VENDAS\n");
        printf ("1 - Venda a vista\n");
        printf ("2 - Venda a prazo\n");
        printf ("0 - Voltar ao menu principal\n");
	printf ("10 - Finalizar o programa\n");

        scanf("%hi", &options);

        switch (options) {
                case 0:
                        main_menu();
                case 1: 
                        cash_sale();
                case 2:
                        credit_sale();
		case 10: 
			stop_program();
                        break;
                default:
                       printf("Escolha uma opção válida\n");
                       sleep(1);
                       sales_menu();

        }
}

void main_menu() {
        
        check_file();
        short options;
        
        while (1) {
                
                printf ("\nMENU PRINCIPAL\n");
                printf ("Eslha a opção desejada\n");
                printf ("1 - Nova Venda\n");
                //printf ("2 - Registrar parcela paga\n");
	        printf ("10 - Finalizar o programa\n");
                scanf ("%hi", &options);


                switch (options) {
                        case 1:
                                sales_menu();
                                break;
                        /*case 2:
                                printf ("Opção AINDA não existe. Voltando ao menu principal\n");
                                sleep(1);
                                main_menu();
                                break;
		        */case 10: 
			        stop_program();
                        default:
                                printf("Escolha uma opção válida. Voltando ao menu principal\n");
                                sleep(1);
                                break;
                }
        }
}

int main() {

        printf ("CONTROLE DE VENDA ESSENZA - By Lucas Araujo\n");
        main_menu();
return 0;
}