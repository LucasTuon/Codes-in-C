/*
🔍 Contexto do Código
Este código implementa uma estrutura de dados de pilha (stack) em linguagem C. A pilha é um tipo de estrutura LIFO (Last In, First Out), onde o último elemento inserido é o primeiro a ser removido.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Define o tamanho máximo da pilha

// Estrutura da pilha
typedef struct {
    int topo;           // Índice do topo da pilha
    int itens[MAX];     // Vetor que armazena os elementos da pilha
} Pilha;

// Inicializa a pilha como vazia
void inicializar(Pilha *p) {
    p->topo = -1;
}

// Verifica se a pilha está vazia
int estaVazia(Pilha *p) {
    return (p->topo == -1);
}

// Verifica se a pilha está cheia
int estaCheia(Pilha *p) {
    return (p->topo == MAX - 1);
}

// Insere um valor no topo da pilha
void push(Pilha *p, int valor) {
    if (estaCheia(p)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    p->itens[++(p->topo)] = valor;
}

// Remove e retorna o valor do topo da pilha
int pop(Pilha *p) {
    if (estaVazia(p)) {
        printf("Erro: Pilha vazia!\n");
        return -1;  // Valor de erro
    }
    return p->itens[(p->topo)--];
}

// Retorna o valor no topo da pilha sem removê-lo
int top(Pilha *p) {
    if (estaVazia(p)) return -1;  // Valor de erro se vazia
    return p->itens[p->topo];
}

// Função principal para testar a pilha
int main() {
    Pilha p;
    inicializar(&p);

    push(&p, 10);
    push(&p, 20);
    push(&p, 30);

    printf("Topo: %d\n", top(&p));       // Saída: 30
    printf("Removido: %d\n", pop(&p));   // Saída: 30
    printf("Novo topo: %d\n", top(&p));  // Saída: 20

    return 0;
}
