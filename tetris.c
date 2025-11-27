#include <stdio.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5   // tamanho fixo da fila circular

// Estrutura que representa uma peça do Tetris
typedef struct {
    int id;     // identificador único
    char nome;  // tipo da peça (I, O, T, L)
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca fila[TAM]; // array fixo de peças
    int front;      // índice da frente (primeiro elemento)
    int rear;       // índice do final (último elemento)
    int count;      // quantidade atual de elementos na fila
} FilaCircular;

int idGlobal = 1; // contador global para gerar IDs únicos

// Função que gera uma peça automaticamente
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'}; // tipos possíveis
    Peca p;
    p.id = idGlobal++;                   // gera ID único
    p.nome = tipos[rand() % 4];          // escolhe tipo aleatório
    return p;
}

// Inicializa a fila com 5 peças
void inicializarFila(FilaCircular *f) {
    f->front = 0;
    f->rear = -1;
    f->count = 0;
    for (int i = 0; i < TAM; i++) {
        f->rear = (f->rear + 1) % TAM;   // move o rear circularmente
        f->fila[f->rear] = gerarPeca();  // insere peça
        f->count++;
    }
}

// Remove peça da frente da fila (dequeue)
void dequeue(FilaCircular *f) {
    if (f->count == 0) {
        printf("Fila vazia!\n");
        return;
    }
    Peca removida = f->fila[f->front];   // pega peça da frente
    printf("Jogou a peça: ID=%d Tipo=%c\n", removida.id, removida.nome);
    f->front = (f->front + 1) % TAM;     // avança a frente circularmente
    f->count--;
}

// Insere nova peça no final da fila (enqueue)
void enqueue(FilaCircular *f) {
    if (f->count == TAM) {
        printf("Fila cheia!\n");
        return;
    }
    f->rear = (f->rear + 1) % TAM;       // move o rear circularmente
    f->fila[f->rear] = gerarPeca();      // insere nova peça
    f->count++;
}

// Mostra o estado atual da fila
void mostrarFila(FilaCircular *f) {
    printf("\nFila Atual:\n");
    int i = f->front;
    for (int j = 0; j < f->count; j++) {
        printf("Pos %d -> ID=%d Tipo=%c\n", j, f->fila[i].id, f->fila[i].nome);
        i = (i + 1) % TAM; // avança circularmente
    }
    printf("\n");
}

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

    srand(time(NULL)); // inicializa gerador de números aleatórios
    FilaCircular fila;
    inicializarFila(&fila); // começa com 5 peças

    int opcao;
    do {
        printf("Menu:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("3 - Visualizar fila\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                // remove peça da frente e insere nova automaticamente
                dequeue(&fila);
                enqueue(&fila); // mantém sempre 5 peças
                mostrarFila(&fila);
                break;
            case 2:
                // insere nova peça manualmente
                enqueue(&fila);
                mostrarFila(&fila);
                break;
            case 3:
                // mostra estado atual da fila
                mostrarFila(&fila);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);

    return 0;
}
