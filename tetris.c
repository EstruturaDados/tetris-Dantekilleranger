#include <stdio.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAM_FILA 5    // capacidade da fila (sempre cheia)
#define TAM_PILHA 3   // capacidade da pilha

// ---------------------------
// Estruturas de dados
// ---------------------------
typedef struct {
    int dados[TAM_FILA];
    int front;  // índice do elemento da frente
    int count;  // quantidade atual de itens
} Fila;

typedef struct {
    int dados[TAM_PILHA];
    int topo;   // índice do topo (-1 se vazia)
} Pilha;

typedef struct {
    Fila fila;
    Pilha pilha;
    int valido; // 1 se há estado salvo para desfazer, 0 caso contrário
} Estado;

// ---------------------------
// Variáveis globais
// ---------------------------
Fila fila;
Pilha pilha;
Estado estadoAnterior;

// ---------------------------
// Utilidades
// ---------------------------
int gerarPeca() {
    // Gera uma peça "tipo" entre 1 e 7 (simulação de tetrominós ou afins)
    return rand() % 7 + 1;
}

void inicializarFilaCheia(Fila *f) {
    f->front = 0;
    f->count = TAM_FILA;
    for (int i = 0; i < TAM_FILA; i++) {
        f->dados[i] = gerarPeca();
    }
}

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int filaCheia(const Fila *f) {
    return f->count == TAM_FILA;
}

int filaVazia(const Fila *f) {
    return f->count == 0;
}

int pilhaCheia(const Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

int pilhaVazia(const Pilha *p) {
    return p->topo == -1;
}

// Obtém índice real (circular) para posição i a partir de front
int idx(const Fila *f, int i) {
    return (f->front + i) % TAM_FILA;
}

// ---------------------------
// Exibição de estado
// ---------------------------
void mostrarEstado(const Fila *f, const Pilha *p) {
    printf("\nFila: ");
    if (f->count == 0) {
        printf("(vazia)");
    } else {
        for (int i = 0; i < f->count; i++) {
            printf("[%d] ", f->dados[idx(f, i)]);
        }
    }

    printf("\nPilha: ");
    if (p->topo == -1) {
        printf("(vazia)");
    } else {
        for (int i = 0; i <= p->topo; i++) {
            printf("[%d] ", p->dados[i]);
        }
    }
    printf("\n");
}

// ---------------------------
// Persistência para desfazer
// ---------------------------
void salvarEstado() {
    estadoAnterior.fila = fila;
    estadoAnterior.pilha = pilha;
    estadoAnterior.valido = 1;
}

void desfazer() {
    if (!estadoAnterior.valido) {
        printf("\nNão há operação para desfazer.\n");
        return;
    }
    fila = estadoAnterior.fila;
    pilha = estadoAnterior.pilha;
    estadoAnterior.valido = 0;
    printf("\nÚltima operação desfeita.\n");
}

// ---------------------------
// Operações da fila
// ---------------------------

// Remove a peça da frente e repõe uma nova no fim, mantendo a fila cheia
int jogarPeca() {
    if (filaVazia(&fila)) {
        // Por projeto, a fila deve estar sempre cheia; este caso não deve ocorrer.
        printf("\nErro: fila vazia inesperada.\n");
        return -1;
    }

    // Peça da frente
    int peca = fila.dados[fila.front];

    // Avança a frente e decrementa contagem (remoção lógica)
    fila.front = (fila.front + 1) % TAM_FILA;
    fila.count--;

    // Insere nova peça no "fim"
    int posFim = idx(&fila, fila.count); // posição física do novo fim
    fila.dados[posFim] = gerarPeca();
    fila.count++;

    return peca;
}

// Enfileira uma peça no fim (usado em integração, garante consistência da fila)
void enfileirarReposicao(int peca) {
    if (filaCheia(&fila)) {
        // substitui o fim de forma circular: avança front e escreve no slot do fim
        // política: se precisar enfileirar mesmo cheia, descartamos a peça da frente
        fila.front = (fila.front + 1) % TAM_FILA;
        fila.count--; // removeu um
    }
    int posFim = idx(&fila, fila.count);
    fila.dados[posFim] = peca;
    fila.count++;
}

// ---------------------------
// Operações da pilha
// ---------------------------
void pushReservar(int peca) {
    if (pilhaCheia(&pilha)) {
        printf("\nPilha cheia! Não é possível reservar mais peças.\n");
        return;
    }
    pilha.dados[++pilha.topo] = peca;
}

int popReservada() {
    if (pilhaVazia(&pilha)) {
        printf("\nPilha vazia! Não há peças reservadas.\n");
        return -1;
    }
    return pilha.dados[pilha.topo--];
}

// ---------------------------
// Ações do menu (com salvarEstado)
// ---------------------------

void acaoJogarPeca() {
    salvarEstado();
    int p = jogarPeca();
    if (p != -1) {
        printf("\nJogando peça: %d\n", p);
    }
}

void acaoReservarPeca() {
    if (pilhaCheia(&pilha)) {
        printf("\nPilha cheia! Não é possível reservar mais peças.\n");
        return;
    }
    salvarEstado();
    int p = jogarPeca();
    if (p != -1) {
        pushReservar(p);
        printf("\nPeça %d reservada.\n", p);
    }
}

void acaoUsarReservada() {
    if (pilhaVazia(&pilha)) {
        printf("\nPilha vazia! Não há peças reservadas.\n");
        return;
    }
    salvarEstado();
    int p = popReservada();
    printf("\nUsando peça reservada: %d\n", p);
    // Opcional: ao usar peça reservada, podemos decidir se ela impacta a fila.
    // Aqui, mantemos a fila cheia gerando automaticamente, então não alteramos a fila.
}

void acaoTrocarTopoComFrente() {
    if (pilhaVazia(&pilha)) {
        printf("\nPilha vazia! Não há topo para troca.\n");
        return;
    }
    if (filaVazia(&fila)) {
        printf("\nFila vazia inesperada; não é possível trocar.\n");
        return;
    }
    salvarEstado();
    int idxFrente = fila.front;
    int tmp = pilha.dados[pilha.topo];
    pilha.dados[pilha.topo] = fila.dados[idxFrente];
    fila.dados[idxFrente] = tmp;
    printf("\nTroca realizada entre topo da pilha e frente da fila.\n");
}

// Política segura para “inverter fila com pilha”:
// - Objetivo: aumentar integração sem perda de dados.
// - Passos:
//   1) Extrair até TAM_PILHA elementos da fila (da frente ao fim) para novo conteúdo da pilha (topo recebe a frente da fila).
//   2) Extrair até TAM_FILA elementos da pilha antiga (do topo para baixo) para novo conteúdo da fila (frente recebe topo antigo).
//   3) Elementos excedentes em cada estrutura permanecem onde estavam (sem descarte).
//   4) Fila é reposta para ficar cheia (se necessário), garantindo integridade e invariantes.
// Observação: Esta política é uma “integração inversora” limitada por capacidade,
// preservando dados e evitando colapsos de estado.
void acaoInverterFilaComPilha() {
    salvarEstado();

    // Buffer temporário para estados atuais
    int filaTemp[TAM_FILA];
    int pilhaTemp[TAM_PILHA];

    // Copiar ordem lógica da fila (frente -> fim)
    for (int i = 0; i < fila.count; i++) {
        filaTemp[i] = fila.dados[idx(&fila, i)];
    }

    // Copiar ordem lógica da pilha (base -> topo)
    for (int i = 0; i <= pilha.topo; i++) {
        pilhaTemp[i] = pilha.dados[i];
    }

    // 1) Novo conteúdo da pilha recebe até TAM_PILHA primeiros da fila (frente primeiro vai ao topo)
    int qtdParaPilha = (fila.count < TAM_PILHA) ? fila.count : TAM_PILHA;
    pilha.topo = -1;
    for (int i = 0; i < qtdParaPilha; i++) {
        // topo recebe frente da fila; sequência mantém “inversão” conceitual
        pilha.dados[++pilha.topo] = filaTemp[i];
    }

    // Remover logicamente da fila os elementos usados (qtdParaPilha)
    fila.front = (fila.front + qtdParaPilha) % TAM_FILA;
    fila.count -= qtdParaPilha;

    // 2) Novo conteúdo a ser enfileirado recebe da pilha antiga (do topo -> base),
    //    inserindo no fim da fila atual
    int qtdPilhaAntiga = pilhaVazia(&estadoAnterior.pilha) ? 0 : (estadoAnterior.pilha.topo + 1);
    for (int i = estadoAnterior.pilha.topo; i >= 0; i--) {
        // enfileirar dado da pilha antiga (topo para baixo)
        enfileirarReposicao(estadoAnterior.pilha.dados[i]);
    }

    // 3) Elementos excedentes (fila antiga além dos primeiros TAM_PILHA) permanecem na fila
    //    Isso já está garantido pela remoção parcial no passo 1.

    // 4) Garantir que a fila esteja cheia novamente
    while (!filaCheia(&fila)) {
        enfileirarReposicao(gerarPeca());
    }

    printf("\nIntegração inversora aplicada entre fila e pilha (com política segura).\n");
}

// ---------------------------
// Menu e loop principal
// ---------------------------
void mostrarMenu() {
    printf("\nMenu:\n");
    printf("1 - Jogar peça\n");
    printf("2 - Reservar peça\n");
    printf("3 - Usar peça reservada\n");
    printf("4 - Trocar topo da pilha com frente da fila\n");
    printf("5 - Desfazer última jogada\n");
    printf("6 - Inverter fila com pilha\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
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

    srand((unsigned)time(NULL));
    inicializarFilaCheia(&fila);
    inicializarPilha(&pilha);
    estadoAnterior.valido = 0;

    int opcao;
    do {
        mostrarEstado(&fila, &pilha);
        mostrarMenu();
        if (scanf("%d", &opcao) != 1) {
            // Limpeza básica de entrada
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("\nEntrada inválida.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                acaoJogarPeca();
                break;
            case 2:
                acaoReservarPeca();
                break;
            case 3:
                acaoUsarReservada();
                break;
            case 4:
                acaoTrocarTopoComFrente();
                break;
            case 5:
                desfazer();
                break;
            case 6:
                acaoInverterFilaComPilha();
                break;
            case 0:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}

