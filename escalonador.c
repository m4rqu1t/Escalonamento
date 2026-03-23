#include "escalonador.h"

void executar_simulacao(tarefa *arrayTarefas, int qtdTarefa, int tempoTotal, FILE *saida) {
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
        int menorValor = 9999999;

        for (int i = 0; i < qtdTarefa; i++) {
            if (arrayTarefas[i].tempoRestante > 0) {
                #ifdef ALGO_EDF
                    if (arrayTarefas[i].deadLineAtual < menorValor) {
                        menorValor = arrayTarefas[i].deadLineAtual;
                        tarefaEscolhida = i;
                    }
                #else
                    if (arrayTarefas[i].periodo < menorValor) {
                        menorValor = arrayTarefas[i].periodo;
                        tarefaEscolhida = i;
                    }
                #endif
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
}
