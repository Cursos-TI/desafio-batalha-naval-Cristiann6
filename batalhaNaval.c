#include <stdio.h>
#include <stdlib.h> 

// Definições de constantes
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

//Protótipos de Funções 
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaInicial, int colunaInicial, int orientacao);
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

//Função Principal
int main() {
    // 1. Representação do Tabuleiro: Matriz 10x10
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicializa todas as posições do tabuleiro com 0 (ÁGUA)
    inicializarTabuleiro(tabuleiro);

    printf("--- Posicionamento de Quatro Navios (Horizontal, Vertical e Diagonais) ---\n\n");

    

    // Navio 1: Horizontal
    int linhaN1 = 2, colunaN1 = 1, orientacaoN1 = 0; 

    // Navio 2: Vertical 
    int linhaN2 = 4, colunaN2 = 6, orientacaoN2 = 1; 

    // Navio 3: Diagonal Principal (Linha e Coluna aumentam)
    int linhaN3 = 0, colunaN3 = 0, orientacaoN3 = 2; 
    
    // Navio 4: Diagonal Secundária (Linha aumenta e Coluna diminui)
    int linhaN4 = 7, colunaN4 = 8, orientacaoN4 = 3; 

    // 2. Posicionar Navios
    
    // Navio 1 (Horizontal)
    printf("Posicionando Navio 1 (Horizontal) em (%d, %d)...\n", linhaN1, colunaN1);
    if (!posicionarNavio(tabuleiro, linhaN1, colunaN1, orientacaoN1)) {
        printf("ERRO: Navio 1 nao pode ser posicionado.\n");
    }

    // Navio 2 (Vertical)
    printf("Posicionando Navio 2 (Vertical) em (%d, %d)...\n", linhaN2, colunaN2);
    if (!posicionarNavio(tabuleiro, linhaN2, colunaN2, orientacaoN2)) {
        printf("ERRO: Navio 2 nao pode ser posicionado.\n");
    }

    // Navio 3 (Diagonal Principal)
    printf("Posicionando Navio 3 (Diagonal ++) em (%d, %d)...\n", linhaN3, colunaN3);
    if (!posicionarNavio(tabuleiro, linhaN3, colunaN3, orientacaoN3)) {
        printf("ERRO: Navio 3 nao pode ser posicionado.\n");
    }

    // Navio 4 (Diagonal Secundária)
    printf("Posicionando Navio 4 (Diagonal +-) em (%d, %d)...\n", linhaN4, colunaN4);
    if (!posicionarNavio(tabuleiro, linhaN4, colunaN4, orientacaoN4)) {
        printf("ERRO: Navio 4 nao pode ser posicionado.\n");
    }
    
    printf("\n");

    // 3. Exibir o Tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}

//Definição das Funções 

/**
 * @brief Inicializa o tabuleiro 10x10 com o valor de ÁGUA (0).
 * * @param tabuleiro A matriz do tabuleiro a ser inicializada.
 */
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

/**
 * @brief Posiciona um navio de tamanho fixo (3) no tabuleiro, 
 * validando limites e sobreposição, incluindo orientações diagonais.
 * @param tabuleiro A matriz do tabuleiro.
 * @param linhaInicial Linha de início.
 * @param colunaInicial Coluna de início.
 * @param orientacao 0=Horizontal, 1=Vertical, 2=Diagonal (++), 3=Diagonal (+-).
 * @return int Retorna 1 se o navio foi posicionado com sucesso, 0 caso contrário.
 */
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaInicial, int colunaInicial, int orientacao) {
    int linhaAtual, colunaAtual;
    int validaLimite = 1; 

    // 1. Validação de Limites
    // Verifica se as coordenadas iniciais são válidas
    if (linhaInicial < 0 || linhaInicial >= TAMANHO_TABULEIRO || 
        colunaInicial < 0 || colunaInicial >= TAMANHO_TABULEIRO) {
        printf("[VAL. ERRO]: Coordenadas iniciais fora do tabuleiro.\n");
        return 0;
    }

    // Verifica se o navio ultrapassa o limite em todas as posições
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        linhaAtual = linhaInicial;
        colunaAtual = colunaInicial;

        if (orientacao == 0) { // Horizontal
            colunaAtual += i;
        } else if (orientacao == 1) { // Vertical
            linhaAtual += i;
        } else if (orientacao == 2) { // Diagonal (Linha++ e Coluna++)
            linhaAtual += i;
            colunaAtual += i;
        } else if (orientacao == 3) { // Diagonal (Linha++ e Coluna--)
            linhaAtual += i;
            colunaAtual -= i;
        } else {
            printf("[VAL. ERRO]: Orientacao invalida (%d).\n", orientacao);
            return 0;
        }

        // Se alguma coordenada estiver fora do tabuleiro (0..9)
        if (linhaAtual < 0 || linhaAtual >= TAMANHO_TABULEIRO || 
            colunaAtual < 0 || colunaAtual >= TAMANHO_TABULEIRO) {
            validaLimite = 0;
            printf("[VAL. ERRO]: Limite - Navio (%d) fora do tabuleiro em (%d, %d).\n", orientacao, linhaAtual, colunaAtual);
            break; 
        }
    }

    if (!validaLimite) {
        return 0;
    }

    // 2. Validação de Sobreposição (Em todas as posições)
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        linhaAtual = linhaInicial;
        colunaAtual = colunaInicial;
        
        // Determina as coordenadas baseadas na orientação
        if (orientacao == 0) { // Horizontal
            colunaAtual += i;
        } else if (orientacao == 1) { // Vertical
            linhaAtual += i;
        } else if (orientacao == 2) { // Diagonal (++)
            linhaAtual += i;
            colunaAtual += i;
        } else { // Diagonal (+-)
            linhaAtual += i;
            colunaAtual -= i;
        }

        // Verifica a sobreposição
        if (tabuleiro[linhaAtual][colunaAtual] == NAVIO) {
            printf("[VAL. ERRO]: Sobreposicao detectada em (%d, %d).\n", linhaAtual, colunaAtual);
            return 0; // Sobreposição
        }
    }

    // 3. Posicionamento (Se todas as validações passarem)
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        // Recalcula as coordenadas para posicionamento
        linhaAtual = linhaInicial;
        colunaAtual = colunaInicial;

        if (orientacao == 0) { // Horizontal
            colunaAtual += i;
        } else if (orientacao == 1) { // Vertical
            linhaAtual += i;
        } else if (orientacao == 2) { // Diagonal (++)
            linhaAtual += i;
            colunaAtual += i;
        } else { // Diagonal (+-)
            linhaAtual += i;
            colunaAtual -= i;
        }

        // Copia o valor 3 (NAVIO)
        tabuleiro[linhaAtual][colunaAtual] = NAVIO;
    }

    return 1;
}

/**
 * @brief Exibe o tabuleiro no console de forma organizada.
 * * @param tabuleiro A matriz do tabuleiro a ser exibida.
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   "); // Espaço para alinhamento das colunas
    
    // Imprime o cabeçalho das colunas (0 a 9)
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j); // Alinha com 2 espaços
    }
    printf("\n");
    
    
    printf("  +");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("---");
    }
    printf("-\n");

    // Loop aninhado para imprimir o conteúdo da matriz
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d |", i); // Imprime o índice da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Imprime o valor da posição com formatação para alinhamento
            printf("%2d ", tabuleiro[i][j]); 
        }
        printf("\n"); // Quebra de linha no final de cada linha
    }
}