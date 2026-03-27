#!/bin/bash

set -euo pipefail

IFS=$'\n\t'

dir_script="$(cd "$(dirname "$0")" && pwd)"
arquivo_db="dbfile"
dir_caminho_arquivo_db="$(realpath "$dir_script/../../database/$arquivo_db")"

validar_db () {
   
    if [ ! -e "$dir_caminho_arquivo_db" ]; then
        echo "Problemas ao inserir dados no banco. Arquivo de banco de dados não existe"
        return 1
    fi   
}


inserir_db () {

    if [ $# -ne 9 ]; then 
        echo "Erro: parâmetros insuficientes"   
        return 1
    fi
    
    (printf '%s' \
    "ID da Peça: $1;" \
    "Nome do Cliente: $2;" \
    "Descrição: $3;" \
    "Preço: $4;" \
    "Metodo de Pagamento: $5;" \
    "Quantidade de Parcelas: $6;" \
    "Parcelas Pagas: $7;" \
    "Valor das Parcelas: $8;" \
    "Valor restante a pagar: $9;" \
    ) >> "$dir_caminho_arquivo_db"
    printf '\n' >> "$dir_caminho_arquivo_db"
    echo "Dados inseridos no banco"
    return 0
    
}

validar_db
inserir_db "$1" "$2" "$3" "$4" "$5" "$6" "$7" "$8" "$9"