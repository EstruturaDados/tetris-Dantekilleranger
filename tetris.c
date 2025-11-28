#include <stdio.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5   // tamanho fixo da fila
#define TAM_PILHA 3  // capacidade máxima da pilha

// ---------------------------
// Estruturas de dados
// ---------------------------
int fila[TAM_FILA];   // fila de peças
int pilha[TAM_PILHA]; // pilha de reserva
int topo = -1;        // índice do topo da pilha

// ---------------------------
// Funções auxiliares
// ---------------------------

// Gera uma peça aleatória (simulação)
int gerarPeca() {
    return rand() % 7 + 1; // peças numeradas de 1 a 7
}

// Inicializa a fila com peças
void inicializarFila() {
    for (int i = 0; i < TAM_FILA; i++) {
        fila[i] = gerarPeca();
    }
}

// Exibe estado atual da fila e pilha
void mostrarEstado() {
    printf("\nFila: ");
    for (int i = 0; i < TAM_FILA; i++) {
        printf("[%d] ", fila[i]);
    }

    printf("\nPilha: ");
    if (topo == -1) {
        printf("(vazia)");
    } else {
        for (int i = 0; i <= topo; i++) {
            printf("[%d] ", pilha[i]);
        }
    }
    printf("\n");
}

// ---------------------------
// Operações da fila
// ---------------------------

// Remove peça da frente da fila e insere nova no fim
int jogarPeca() {
    int peca = fila[0]; // pega a peça da frente

    // desloca elementos para frente
    for (int i = 0; i < TAM_FILA - 1; i++) {
        fila[i] = fila[i + 1];
    }

    // insere nova peça no fim
    fila[TAM_FILA - 1] = gerarPeca();

    return peca;
}

// ---------------------------
// Operações da pilha
// ---------------------------

// Push: reserva peça da fila
void reservarPeca() {
    if (topo == TAM_PILHA - 1) {
        printf("\nPilha cheia! Não é possível reservar mais peças.\n");
        return;
    }

    int peca = jogarPeca(); // remove da fila
    pilha[++topo] = peca;   // insere na pilha
    printf("\nPeça %d reservada!\n", peca);
}

// Pop: usa peça da pilha
void usarReservada() {
    if (topo == -1) {
        printf("\nPilha vazia! Não há peças reservadas.\n");
        return;
    }

    int peca = pilha[topo--]; // remove do topo
    printf("\nUsando peça reservada: %d\n", peca);
}

// ---------------------------
// Programa principal
// ---------------------------

int main()
{

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.

    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).

    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha

    srand(time(NULL)); // inicializa gerador aleatório
    inicializarFila();

    int opcao;
    do {
        mostrarEstado();
        printf("\nMenu:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int peca = jogarPeca();
                printf("\nJogando peça: %d\n", peca);
                break;
            }
            case 2:
                reservarPeca();
                break;
            case 3:
                usarReservada();
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

