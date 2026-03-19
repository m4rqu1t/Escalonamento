#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[]){

    if(argc != 2){

        printf("ERRO: NUMERO INVALIDO DE ARGUMENTOS\n");
        return 1;

    }

    FILE *arquivo = fopen(argv[1], "r");
    if(arquivo == NULL){

        printf("ERRO: ARQUIVO NAO EXISTE OU NAO PODE SER ABERTO\n");
        return 1;
    }



    return 0;
}
