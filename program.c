#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include "Headers/checks.h"

void mainMenu();

void stopProgram() {
	
	printf ("\nFinalizando o programa\n");
	sleep(1);
        exit(0);

}


const char *filename = "dbfile";
FILE *file;

int checkFile() {

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

void cashSale() {
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
        file = fopen(filename, "a");
        fprintf(file, "%d;%s;%.2f;%s\n", idPeca, descriptionPeca, pricePeca, clientName);
        fclose(file);
        printf ("\nDADOS DA VENDA\n O ID: %d.\n Descrição: %s.\n Valor: %.2f.\n Cliete: %s.\n", idPeca, descriptionPeca, pricePeca, clientName);
        printf ("Dados inseridos no banco de dados\n");
        
        //insertDbFile(idPeca, descriptionPeca, pricePeca, clientName);

        short options;
        printf ("\n0 - Voltar ao menu principal\n");
        printf ("10 - Finalizar o programa\n");
        scanf("%hi", &options);

        switch (options) {
                case 0: 
                        mainMenu();
		case 10: 
			stopProgram();
			break;
                default:
                        printf("Escolha uma opção válida. Voltando ao menu principal\n");
                        sleep(1);
                        mainMenu();
                        break;
        }


}

void creditSale() {

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

        int installmentsValue = pricePeca / installments;

        printf ("Digite o nome do cliente: ");
        //scanf ("%[^\n]%*c", clientName);
        fgets (clientName, 50, stdin);
        clientName[strcspn(clientName, "\n")] = '\0';

        file = fopen(filename, "a");
        fprintf(file, "%d;%s;%.2f;%d;%d;%s\n", idPeca, descriptionPeca, pricePeca, installments, installmentsValue, clientName);
        fclose(file);
        printf ("\nDADOS DA VENDA\n O ID: %d.\n Descrição: %s.\n Valor: %.2f.\n Parcelas: %d\n Valor da Parcela: %d\n Cliete: %s.\n", idPeca, descriptionPeca, pricePeca, installments, installmentsValue, clientName);
        printf ("Dados inseridos no banco de dados\n");

        short options;
        printf ("\n0 - Voltar ao menu principal\n");
        printf ("10 - Finalizar o programa\n");
        scanf("%hi", &options);

        switch (options) {
                case 0: 
                        mainMenu();
		case 10: 
			stopProgram();
			break;
                default:
                        printf("Escolha uma opção válida. Voltando ao menu principal\n");
                        sleep(1);
                        mainMenu();
                        break;
        }

}

void salesMenu() {

        short options;
        printf ("\nMENU DO CONTROLE DE VENDAS\n");
        printf ("1 - Venda a vista\n");
        printf ("2 - Venda a prazo\n");
        printf ("0 - Voltar ao menu principal\n");
	printf ("10 - Finalizar o programa\n");

        scanf("%hi", &options);

        switch (options) {
                case 0:
                        mainMenu();
                case 1: 
                        cashSale();
                case 2:
                        creditSale();
		case 10: 
			stopProgram();
                        break;
                default:
                       printf("Escolha uma opção válida\n");
                       sleep(1);
                       salesMenu();

        }
}

void mainMenu() {
        
        checkFile();
        short options;
        printf ("\nMENU PRINCIPAL\n");
        printf ("Eslha a opção desejada\n");
        printf ("1 - Nova Venda\n");
        //printf ("2 - Registrar parcela\n");
	//printf ("10 - Finalizar o programa\n");
        scanf ("%hi", &options);

        switch (options) {
                case 1:
                        salesMenu();
                        break;
                /*case 2:
                        printf ("Opção AINDA não existe. Voltando ao menu principal\n");
                        sleep(1);
                        mainMenu();
                        break;
		case 10: 
			stopProgram();
			break;
                */default:
                        printf("Escolha uma opção válida. Voltando ao menu principal\n");
                        sleep(1);
                        mainMenu();
                        break;
        }
}

int main() {

        printf ("CONTROLE DE VENDA ESSENZA - By Lucas Araujo\n");
        mainMenu();
return 0;
}