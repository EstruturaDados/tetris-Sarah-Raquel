#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5   // Tamanho fixo da fila circular de peças

// Aqui eu defino a struct que representa cada peça do Tetris
typedef struct {
    int id;     // identificador único
    char tipo;  // tipo da peça: I, O, T, L...
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[MAX]; 
    int inicio; 
    int fim;   
    int total; 
} Fila;


// Função que gera uma peça aleatória automaticamente
Peca gerarPeca() {
    Peca p;
    char tipos[4] = {'I', 'O', 'T', 'L'};

    p.id = rand() % 1000;                   // id aleatório
    p.tipo = tipos[rand() % 4];             // tipo aleatório

    return p;
}


// Inicializa a fila deixando preparada para uso
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}


// Insere uma nova peça no fim da fila circular
void inserir(Fila *f, Peca p) {
    if (f->total == MAX) {
        // No nível novato a fila sempre terá 5 elementos
        printf("A fila esta cheia! (Isso nao deveria acontecer no nivel Novato)\n");
        return;
    }

    f->itens[f->fim] = p;                   // Coloca a peça no fim
    f->fim = (f->fim + 1) % MAX;            // Movimento circular
    f->total++;
}


// Remove a peça da frente (jogar a próxima)
Peca remover(Fila *f) {
    Peca vazia = {-1, '-'};

    if (f->total == 0) {
        printf("Fila vazia! (Nao deveria ocorrer no nivel Novato)\n");
        return vazia;
    }

    Peca p = f->itens[f->inicio];          // Pega o primeiro elemento
    f->inicio = (f->inicio + 1) % MAX;     // Avança circularmente
    f->total--;

    return p;
}


// Mostra todas as peças da fila na ordem correta
void mostrarFila(Fila *f) {
    printf("\n=== Fila de Pecas Futuras ===\n");

    int idx = f->inicio;
    for (int i = 0; i < f->total; i++) {
        printf("ID: %d | Tipo: %c\n", f->itens[idx].id, f->itens[idx].tipo);
        idx = (idx + 1) % MAX;
    }
}


int main() {
    Fila fila;
    inicializarFila(&fila);

    srand(time(NULL)); // Para gerar peças aleatórias diferentes

    // Nivel Novato: a fila deve iniciar já com 5 peças automáticas
    for (int i = 0; i < MAX; i++) {
        inserir(&fila, gerarPeca());
    }

    int opcao;
    Peca p;

    do {
        printf("\n=== MENU TETRIS STACK - NIVEL NOVATO ===\n");
        printf("1 - Visualizar fila de pecas\n");
        printf("2 - Jogar peca (remover da frente)\n");
        printf("3 - Inserir nova peca (automatica)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                mostrarFila(&fila);
                break;

            case 2:
                p = remover(&fila);
                if (p.id != -1) {
                    printf("\nPeca jogada -> ID: %d | Tipo: %c\n", p.id, p.tipo);

                    // Após remover, insiro automaticamente outra
                    inserir(&fila, gerarPeca());
                }
                break;

            case 3:
                inserir(&fila, gerarPeca());
                printf("Nova peca inserida!\n");
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
