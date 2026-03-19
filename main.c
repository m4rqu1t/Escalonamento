#include <stdio.h>
#include <stdlib.h>

typedef struct tarefa{
    char nome[5];
    int periodo;
    int cpuBurst;
}tarefa;

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

    int tempoTotal;
    if(fscanf(arquivo, "%d", &tempoTotal) != 1){

        printf("ERRO AO LER O TEMPO TOTAL NO INICIO DO ARQUIVO\n");
        fclose(arquivo);
        return 1;

    }

    printf("TEMPO DEFINIDO : %d\n", tempoTotal);




    return 0;
}
