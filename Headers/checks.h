int intValidation() {
        
        int value;
        char input[100]; // Variable to buffer user input as a string      
        getchar();
        while (fgets(input, sizeof(input), stdin)) {
                if (sscanf(input, "%d", &value) == 1){
                        break;
                } else {
                        printf("Valor inválido. Use apenas números: ");
                }
        }
return value;
}

void stringValidation(char *value, int maxSize) {
    char input[250];
    int check;
    
    while (fgets(input, sizeof(input), stdin)) {
        // Remove quebra de linha
        input[strcspn(input, "\n")] = '\0';
        
        check = 1;
        
        // Verifica se não está vazio e se cabe no value
        if (strlen(input) == 0 || strlen(input) > maxSize) {
            check = 0;
        }
        
        // Verifica se todos os caracteres são letras ou espaços
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isalpha(input[i]) && input[i] != ' ') {
                check = 0;
                break;
            }
        }
        
        if (check) {
            strcpy(value, input);
            break;
        } else {
            printf("Valor inválido. Use apenas letras: ");
        }
    }
}