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



    FILE *saida = fopen("rate_maolf.out", "w");
    if (saida == NULL) {
        printf("ERRO AO CRIAR O ARQUIVO DE SAIDA\n");
        return 1;
    }
    fprintf(saida, "EXECUTION BY RATE\n\n");

    int tarefaEmExecucao = -1;
    int tempoExecutado = 0;

    for (int t = 0; t < tempoTotal; t++) {

        for (int i = 0; i < qtdTarefa; i++) {

            if (t > 0 && t == arrayTarefas[i].deadLineAtual) {

                if (arrayTarefas[i].tempoRestante > 0) {

                    arrayTarefas[i].deadLinesPerdidos++;

                    if (i == tarefaEmExecucao) {

                        fprintf(saida, "[%s] for %d units - L\n", arrayTarefas[i].nome, tempoExecutado);
                        tempoExecutado = 0;
                        tarefaEmExecucao = -1;

                    }
                }
                arrayTarefas[i].tempoRestante = arrayTarefas[i].cpuBurst;
                arrayTarefas[i].deadLineAtual += arrayTarefas[i].periodo;
            }
        }

        int tarefaEscolhida = -1;
        int menorPeriodo = 9999999;

        for (int i = 0; i < qtdTarefa; i++) {

            if (arrayTarefas[i].tempoRestante > 0) {

                if (arrayTarefas[i].periodo < menorPeriodo) {

                    menorPeriodo = arrayTarefas[i].periodo;
                    tarefaEscolhida = i;

                }
            }
        }

        if (tarefaEscolhida != tarefaEmExecucao) {

            if (tempoExecutado > 0) {

                if (tarefaEmExecucao == -1) {

                    fprintf(saida, "idle for %d units\n", tempoExecutado);
                } else {
                    fprintf(saida, "[%s] for %d units - H\n", arrayTarefas[tarefaEmExecucao].nome, tempoExecutado);
                }
            }

            tarefaEmExecucao = tarefaEscolhida;
            tempoExecutado = 0;

        }

        tempoExecutado++;

        if (tarefaEmExecucao != -1) {

            arrayTarefas[tarefaEmExecucao].tempoRestante--;

            if (arrayTarefas[tarefaEmExecucao].tempoRestante == 0) {

                arrayTarefas[tarefaEmExecucao].execucoesCompletas++;
                fprintf(saida, "[%s] for %d units - F\n", arrayTarefas[tarefaEmExecucao].nome, tempoExecutado);
                        tempoExecutado = 0;
                        tarefaEmExecucao = -1;

            }
        }

        if (t == tempoTotal - 1) {

            if (tempoExecutado > 0) {

                if (tarefaEmExecucao == -1) {

                    fprintf(saida, "idle for %d units\n", tempoExecutado);

                } else {

                    fprintf(saida, "[%s] for %d units - K\n", arrayTarefas[tarefaEmExecucao].nome, tempoExecutado);
                    arrayTarefas[tarefaEmExecucao].morto = 1;

                }
            }
        }
    }

    fprintf(saida, "\nLOST DEADLINES\n");
    for (int i = 0; i < qtdTarefa; i++) {

        fprintf(saida, "[%s] %d\n", arrayTarefas[i].nome, arrayTarefas[i].deadLinesPerdidos);

    }

    fprintf(saida, "\nCOMPLETE EXECUTION\n");
    for (int i = 0; i < qtdTarefa; i++) {

        fprintf(saida, "[%s] %d\n", arrayTarefas[i].nome, arrayTarefas[i].execucoesCompletas);

        }

    fprintf(saida, "\nKILLED\n");

    for (int i = 0; i < qtdTarefa; i++) {

        fprintf(saida, "[%s] %d\n", arrayTarefas[i].nome, arrayTarefas[i].morto);

        }

        free(arrayTarefas);
        fclose(arquivo);
        fclose(saida);
    return 0;
}
