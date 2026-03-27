#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/control.h"
#include "../include/db.h"

void main_menu();

void stop_program() {
	
	printf ("\nFinalizando o programa\n");
	sleep(1);
        exit(0);

}


const char *filename = "database/dbfile";
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

        char id_peca [250];
        char descricao_peca[250];
        float preco_peca;
        char nome_cliente[50];

        getchar();
        printf ("Digite o ID da peça: ");
        fgets (id_peca, 250, stdin);
        id_peca[strcspn(id_peca, "\n")] = '\0';

        printf ("Digite o nome do cliente: ");
        //scanf ("%[^\n]%*c", nome_cliente);
        fgets (nome_cliente, 50, stdin);
        nome_cliente[strcspn(nome_cliente, "\n")] = '\0';
        to_lower_string(nome_cliente);

        printf ("Digite a descrição: ");
        string_validation(descricao_peca, 250);
        to_lower_string(descricao_peca);
        
        printf ("Digite o valor da peça: ");
        scanf ("%f", &preco_peca);
        getchar();

        //printf ("\nDADOS DA VENDA\n O ID: %d.\n Descrição: %s.\n Valor: %.2f.\n Cliete: %s.\n", id_peca, descricao_peca, preco_peca, nome_cliente);

        short parcelas = 1;
        float valor_parcelas = preco_peca;
        char metodo_pagamento [11] = "a vista";
        int parcelas_pagas = 1;
        short valor_restante_pagar = 0;

        inserir_db(id_peca, nome_cliente, descricao_peca, preco_peca, metodo_pagamento, parcelas, parcelas_pagas, valor_parcelas, valor_restante_pagar);

        short options;
        printf ("\n0 - Voltar ao menu principal\n");
        printf ("10 - Finalizar o programa\n");
        scanf("%hi", &options);

        switch (options) {
                case 0: 
                        main_menu();
                        break;
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

        char id_peca [250];
        char descricao_peca[250];
        float preco_peca;
        char nome_cliente[50];
        
        getchar();
        printf ("Digite o ID da peça: ");
        fgets (id_peca, 250, stdin);
        id_peca[strcspn(id_peca, "\n")] = '\0';

        printf ("Digite o nome do cliente: ");
        //scanf ("%[^\n]%*c", nome_cliente);
        fgets (nome_cliente, 50, stdin);
        nome_cliente[strcspn(nome_cliente, "\n")] = '\0';
        to_lower_string(nome_cliente);

        printf ("Digite a descrição da peça: ");
        string_validation(descricao_peca, 250);
        to_lower_string(descricao_peca);
        
        printf ("Digite o valor da peça: ");
        scanf ("%f", &preco_peca);
        //getchar();

        printf ("Digite a quantidade de parcelas: ");
        short parcelas = int_validation();

        float valor_parcelas = preco_peca / parcelas;
        char metodo_pagamento [11] = "parcelado";
        int parcelas_pagas = 0;
        float valor_restante_pagar = preco_peca;

        inserir_db(id_peca, nome_cliente, descricao_peca, preco_peca, metodo_pagamento, parcelas, parcelas_pagas, valor_parcelas, valor_restante_pagar);

        short options;
        printf ("\n0 - Voltar ao menu principal\n");
        printf ("10 - Finalizar o programa\n");
        scanf("%hi", &options);

        switch (options) {
                case 0: 
                        main_menu();
                        break;
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
                        break;
                case 1: 
                        cash_sale_menu();
                        break;
                case 2:
                        credit_sale_menu();
                        break;
		case 10: 
			stop_program();
                        break;
                default:
                       printf("Escolha uma opção válida\n");
                       sleep(1);
                       sales_menu();
                       break;

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
                                break;
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