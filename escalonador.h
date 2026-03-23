#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include <stdio.h>

typedef struct tarefa {
    char nome[5];
    int periodo;
    int cpuBurst;
    int tempoRestante;
    int deadLineAtual;
    int execucoesCompletas;
    int deadLinesPerdidos;
    int morto;
} tarefa;

void executar_simulacao(tarefa *arrayTarefas, int qtdTarefa, int tempoTotal, FILE *saida);

#endif
