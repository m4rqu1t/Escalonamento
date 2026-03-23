# Simulador de Escalonamento de Tempo Real (RM & EDF)

Este projeto é um simulador de escalonamento de processos em tempo real construído em **C**, focado na implementação e análise de dois dos mais clássicos algoritmos de Sistemas Operacionais:
* **Rate-Monotonic (RM):** Escalonamento estático baseado na frequência (menor período = maior prioridade).
* **Earliest-Deadline-First (EDF):** Escalonamento dinâmico baseado no prazo (deadline mais próximo = maior prioridade).

O sistema processa um arquivo de entrada contendo a lista de tarefas periódicas, simula a execução na CPU lidando com preempção e trocas de contexto, e gera um arquivo de saída formatado com o histórico de execução e estatísticas finais.

##  Arquitetura do Projeto

O código foi construído com foco em boas práticas de Engenharia de Software, utilizando alocação dinâmica de memória e uma arquitetura modularizada:

* `main.c`: O maestro da aplicação. Responsável pela interface via linha de comando (CLI), leitura/validação do arquivo de entrada e alocação de memória.
* `escalonador.h`: Arquivo de cabeçalho contendo a definição da estrutura (`struct tarefa`) e assinaturas das funções.
* `escalonador.c`: O motor da simulação. Contém a lógica de verificação de prazos, escolha de prioridade via diretivas de pré-processador (`#ifdef`), execução e cálculo de estatísticas.
* `Makefile`: Automação do processo de compilação utilizando flags do GCC para gerar executáveis distintos a partir do mesmo código-fonte.

##  Como Compilar e Executar

O projeto inclui um `Makefile` para facilitar a compilação no Linux, Unix ou macOS.

### 1. Compilação
Abra o terminal na raiz do projeto e utilize um dos comandos abaixo:

```bash
    Para compilar o algoritmo Rate-Monotonic (gera o executável ./rate)
make rate

    Para compilar o algoritmo Earliest-Deadline-First (gera o executável ./edf)
make edf

    Para limpar os arquivos compilados e arquivos de saída (.out)
make clean

```

### 2. Execução

Após compilar, execute o programa passando o arquivo .txt de entrada como argumento:
Bash

./rate entrada.txt
# ou
./edf entrada.txt

## Formato de Entrada e Saída

### Arquivo de Entrada (.txt)

A primeira linha deve conter o tempo total de simulação. As linhas seguintes representam as tarefas (Nome, Período, CPU Burst).

Exemplo:

```bash

165
T1 50 25
T2 80 35

```

### Arquivo de Saída (.out)

O programa gerará automaticamente um arquivo nomeado [algoritmo]_[login].out (ex: rate_maolf.out). Ele contém os blocos contínuos de execução com os seguintes marcadores de status:

F (Finished): Tarefa concluiu sua execução no período.

H (Hold): Tarefa sofreu preempção (troca de contexto).

L (Lost): Tarefa perdeu o seu deadline.

K (Killed): Tarefa foi abortada pelo fim do tempo de simulação.

O final do arquivo apresenta um consolidado estatístico das categorias LOST DEADLINES, COMPLETE EXECUTION e KILLED.


*Marco Aurélio (m4rqu1t) Estudante de Ciência da Computação - CESAR School*
