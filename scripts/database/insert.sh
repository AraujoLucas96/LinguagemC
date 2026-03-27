#!/bin/bash

set -eu pipefail

file_database_name="dbfile"
file_database="../database/$file_database_name"

insert_into_file_db () {

    if [ $# -ne 9 ]; then 
        echo "Erro: parâmetros insuficientes"   
        return 1
    fi
    
    local data=(
        "$1" #idPeca
        "$2" #clientName
        "$3" #descriptionPeca
        "$4" #pricePeca
        "$5" #paymentMethod
        "$6" #installments
        "$7" #paidInstallments
        "$8" #installmentsValue
        "$9" #remaining
    )
    
    printf '%s\n' "${data[@]}" >> "$file_database"
}