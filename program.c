#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include "Headers/control.h"
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

void cash_sale_menu() {
        //short options;
        printf ("\nMENU VENDA A VISTA\n");

        char idPeca [250];
        char descriptionPeca[250];
        float pricePeca;
        char clientName[50];

        getchar();
        printf ("Digite o ID da peça: ");
        //int idPeca = int_validation();
        fgets (idPeca, 250, stdin);
        idPeca[strcspn(idPeca, "\n")] = '\0';

        printf ("Digite o nome do cliente: ");
        //scanf ("%[^\n]%*c", clientName);
        fgets (clientName, 50, stdin);
        clientName[strcspn(clientName, "\n")] = '\0';
        to_lower_string(clientName);

        printf ("Digite a descrição: ");
        string_validation(descriptionPeca, 250);
        to_lower_string(descriptionPeca);
        
        printf ("Digite o valor da peça: ");
        scanf ("%f", &pricePeca);
        getchar();

        //printf ("\nDADOS DA VENDA\n O ID: %d.\n Descrição: %s.\n Valor: %.2f.\n Cliete: %s.\n", idPeca, descriptionPeca, pricePeca, clientName);

        short installments = 1;
        float installmentsValue = pricePeca;
        char paymentMethod [11] = "a vista";
        int paidInstallments = 1;
        short remaining = 0;

        insert_db(idPeca, clientName, descriptionPeca, pricePeca, paymentMethod, installments, paidInstallments, installmentsValue, remaining);

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

void credit_sale_menu() {

        printf ("\nMENU VENDA PARCELADA\n");

        char idPeca [250];
        char descriptionPeca[250];
        float pricePeca;
        char clientName[50];
        
        getchar();
        printf ("Digite o ID da peça: ");
        fgets (idPeca, 250, stdin);
        idPeca[strcspn(idPeca, "\n")] = '\0';

        printf ("Digite o nome do cliente: ");
        //scanf ("%[^\n]%*c", clientName);
        fgets (clientName, 50, stdin);
        clientName[strcspn(clientName, "\n")] = '\0';
        to_lower_string(clientName);

        printf ("Digite a descrição da peça: ");
        string_validation(descriptionPeca, 250);
        to_lower_string(descriptionPeca);
        
        printf ("Digite o valor da peça: ");
        scanf ("%f", &pricePeca);
        //getchar();

        printf ("Digite a quantidade de parcelas: ");
        short installments = int_validation();

        float installmentsValue = pricePeca / installments;
        char paymentMethod [11] = "parcelado";
        int paidInstallments = 0;
        float remaining = pricePeca;

        //printf ("Saldo devedor: %.2f", remaining);

        insert_db(idPeca, clientName, descriptionPeca, pricePeca, paymentMethod, installments, paidInstallments, installmentsValue, remaining);

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
                        cash_sale_menu();
                case 2:
                        credit_sale_menu();
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