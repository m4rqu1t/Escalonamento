#include <stdio.h>
#include <stdlib.h>
#include "escalonador.h"

int main(int argc, char *argv[]) {
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

    int qtdTarefa = 0;
    char tempNome[5];
    int tempPeriodo, tempBurst;

    while (fscanf(arquivo, "%4s %d %d", tempNome, &tempPeriodo, &tempBurst) == 3) {
        qtdTarefa++;
    }

    tarefa *arrayTarefas = malloc(qtdTarefa * sizeof(tarefa));
    if (arrayTarefas == NULL) {
        printf("ERRO AO ALOCAR MEMORIA\n");
        fclose(arquivo);
        return 1;
    }

    rewind(arquivo);
    fscanf(arquivo, "%d", &tempoTotal);

    int i = 0;
    while (fscanf(arquivo, "%4s %d %d", arrayTarefas[i].nome, &arrayTarefas[i].periodo, &arrayTarefas[i].cpuBurst) == 3) {
        i++;
    }

    for (int j = 0; j < qtdTarefa; j++) {
        arrayTarefas[j].tempoRestante = arrayTarefas[j].cpuBurst;
        arrayTarefas[j].deadLineAtual = arrayTarefas[j].periodo;
        arrayTarefas[j].execucoesCompletas = 0;
        arrayTarefas[j].deadLinesPerdidos = 0;
        arrayTarefas[j].morto = 0;
    }

    char nomeArquivoSaida[50];
    #ifdef ALGO_EDF
        sprintf(nomeArquivoSaida, "edf_maolf.out");
    #else
        sprintf(nomeArquivoSaida, "rate_maolf.out");
    #endif

    FILE *saida = fopen(nomeArquivoSaida, "w");
    if (saida == NULL) {
        printf("ERRO AO CRIAR O ARQUIVO DE SAIDA\n");
        free(arrayTarefas);
        fclose(arquivo);
        return 1;
    }

    #ifdef ALGO_EDF
        fprintf(saida, "EXECUTION BY EDF\n\n");
    #else
        fprintf(saida, "EXECUTION BY RATE\n\n");
    #endif

    executar_simulacao(arrayTarefas, qtdTarefa, tempoTotal, saida);

    free(arrayTarefas);
    fclose(arquivo);
    fclose(saida);

    return 0;
}
