/*
🔍 Contexto do Código
Imagine que temos uma cidade representada como um conjunto de esquinas conectadas por ruas. 
Cada rua tem um tempo associado (tempo para atravessar). 
Dado um número fixo de esquinas e as conexões entre elas, queremos que o algoritmo descubra qual é o caminho mais rápido da esquina de partida até a esquina onde está o incêndio.

Aqui eu apresento uma versão do algoritmo de Dijkstra para resolver o problema de encontrar a rota mais rápida entre duas esquinas em um mapa representado por uma matriz de adjacência.
*/

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

// Função para inverter o vetor de rota
void reorganizarRota(int rota[], int tamanho) {

    for (int i = 0; i < tamanho / 2; i++) {

        int temp = rota[i];
        rota[i] = rota[tamanho - i - 1];
        rota[tamanho - i - 1] = temp;

    }
}

// Função para encontrar a esquina com menor custo
int encontrarMenorEsquina(int T[], int E[], int numEsquinas){

    int min = INT_MAX;
    int minIndex = -1;

    for(int i = 0; i < numEsquinas; i++){

        if(!E[i] && T[i] <= min){

            min = T[i];
            minIndex = i;

        }

    }
    return minIndex;
}

int rotaMaisRapida(int **mapa, int numEsquinas, int incendio, int rota[]) {

    int T[numEsquinas];       // Vetor que armazena o menor tempo para alcançar cada esquina
    int E[numEsquinas];       // Vetor que indica se uma esquina foi visitada
    int anterior[numEsquinas]; // Vetor que armazena a esquina anterior para reconstruir o caminho

    for (int i = 0; i < numEsquinas; i++) {

        T[i] = INT_MAX;       // T[i] recebe infinito
        E[i] = 0;             // Todas as esquinas começam não visitadas
        anterior[i] = -1;     // Inicializa o vetor anterior com -1

    }

    T[0] = 0;   // Tempo gasto para ir da esquina 1 até a esquina 1

    for (int i = 0; i < numEsquinas - 1; i++) {

        int v = encontrarMenorEsquina(T, E, numEsquinas); // Escolhe a esquina com menor custo
        E[v] = 1;    // Marca a esquina v como visitada

        if (v == incendio) {      // Se a esquina é a do incêndio, interrompe
            break;
        }

        for (int e = 0; e < numEsquinas; e++) {

            if (!E[e] && mapa[v][e] && T[v] != INT_MAX && T[v] + mapa[v][e] < T[e]) {

                T[e] = T[v] + mapa[v][e]; // Atualiza os tempos para as esquinas vizinhas
                anterior[e] = v; // Atualiza a esquina anterior para reconstruir o caminho

            }
        }
    }

    // Reconstruir o caminho da esquina inicial até a do incêndio
    int indiceRota = 0;
    for (int i = incendio; i != -1; i = anterior[i]) {
        rota[indiceRota++] = i + 1; // Ajuste para 1-based
    }

    reorganizarRota(rota, indiceRota);

    return T[incendio]; // Retorna o tempo mínimo até a esquina do incêndio
}

int main(){

    int numEsquinas = 6;
    int incendio = 3;
    int rota[numEsquinas];

    int **mapa = (int **)malloc(numEsquinas * sizeof(int *));

    for( int i = 0; i < numEsquinas; i++){
        
        mapa[i] = (int *)malloc(numEsquinas * sizeof(int));

    }

    for(int i = 0; i < numEsquinas; i++){

        for(int j = 0; j < numEsquinas; j++){

            mapa[i][j] = 0;
        
        }

    }

    mapa[3][5] = 3;
    mapa[4][1] = 4;
    mapa[1][2] = 1;
    mapa[0][3] = 2;
    mapa[2][4] = 1;
    mapa[0][4] = 4;
    mapa[3][4] = 1;
    mapa[4][5] = 1;
    mapa[0][2] = 8;
    mapa[5][1] = 2;

    // Imprimindo o menor tempo para chegar à esquina do incêndio
    printf("O menor tempo para chegar a esquina do incendio (%d): %d minutos\n", incendio, rotaMaisRapida(mapa, numEsquinas, incendio -1, rota));

    printf("Rota: ");
    for( int i = 0; i < numEsquinas; i++){

        printf("%d ", rota[i]);

    }
    

    // Liberar a memória alocada para o mapa
    for (int i = 0; i < numEsquinas; i++) {
        free(mapa[i]);
    }
    free(mapa);

    return 0;
}

/*
    Referências:
    
    - https://petbcc.ufscar.br/limits/ (Usado para valor INT_MAX)
 */


