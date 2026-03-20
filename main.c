#include <stdio.h>
#include <stdlib.h>

typedef struct tarefa{

    char nome[5];
    int periodo;
    int cpuBurst;
    int tempoRestante;
    int deadLineAtual;
    int execucoesCompletas;
    int deadLinesPerdidos;
    int morto;

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
    while (fscanf(arquivo, "%4s %d %d",arrayTarefas[i].nome, &arrayTarefas[i].periodo, &arrayTarefas[i].cpuBurst) == 3) {

        i++;

    }

    printf("MEMORIA ALOCADA PERFEITAMENTE PARA  %d TAREFAS!\n", qtdTarefa);

    for (int j = 0; j < qtdTarefa; j++) {

        arrayTarefas[j].tempoRestante = arrayTarefas[j].cpuBurst;
        arrayTarefas[j].deadLineAtual = arrayTarefas[j].periodo;
        arrayTarefas[j].execucoesCompletas = 0;
        arrayTarefas[j].deadLinesPerdidos = 0;
        arrayTarefas[j].morto = 0;

    }

    for (int j = 0; j < qtdTarefa; j++) {
        printf("Tarefa %s | Tempo Restante: %d | Deadline: %d\n", arrayTarefas[j].nome, arrayTarefas[j].tempoRestante, arrayTarefas[j].deadLineAtual);
            }



        printf("--- TESTANDO ---\n");
        for (int j = 0; j < qtdTarefa; j++) {

            printf("Tarefa %d: Nome: %s | Periodo: %d | Burst: %d\n", j+1, arrayTarefas[j].nome, arrayTarefas[j].periodo, arrayTarefas[j].cpuBurst);

                }
        printf("---------------------------------------\n");



        free(arrayTarefas);
        fclose(arquivo);

    return 0;
}
