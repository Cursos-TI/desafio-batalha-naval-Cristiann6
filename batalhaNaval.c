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

    // Variáveis para as posições iniciais dos navios
    // Coordenadas devem ser escolhidas para garantir que estejam dentro dos limites
    // e não se sobreponham.

    // Navio 1: Horizontal (Orientação: 0)
    int linhaN1 = 2; // Linha de início
    int colunaN1 = 1; // Coluna de início
    int orientacaoN1 = 0; // 0 = Horizontal

    // Navio 2: Vertical (Orientação: 1)
    int linhaN2 = 4; // Linha de início
    int colunaN2 = 6; // Coluna de início
    int orientacaoN2 = 1; // 1 = Vertical

    printf("Posicionamento de Navios no Tabuleiro (Batalha Naval)\n\n");

    // 2. Posicionar Navios
    // Tenta posicionar o Navio 1 (Horizontal)
    printf("Posicionando Navio 1 (Horizontal) em (%d, %d)...\n", linhaN1, colunaN1);
    if (!posicionarNavio(tabuleiro, linhaN1, colunaN1, orientacaoN1)) {
        printf("ERRO: Navio 1 nao pode ser posicionado. Verifique os limites ou sobreposicao.\n");
    }

    // Tenta posicionar o Navio 2 (Vertical)
    printf("Posicionando Navio 2 (Vertical) em (%d, %d)...\n", linhaN2, colunaN2);
    if (!posicionarNavio(tabuleiro, linhaN2, colunaN2, orientacaoN2)) {
        printf("ERRO: Navio 2 nao pode ser posicionado. Verifique os limites ou sobreposicao.\n");
        // exit(1);
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
    // Loop aninhado para percorrer todas as posições da matriz
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA; // Define o valor 0 (Água) em todas as posições
        }
    }
}

/**
 * @brief Posiciona um navio de tamanho fixo (3) no tabuleiro, 
 * validando limites e sobreposição.
 * * @param tabuleiro A matriz do tabuleiro onde o navio será posicionado.
 * @param linhaInicial Linha de início do navio.
 * @param colunaInicial Coluna de início do navio.
 * @param orientacao 0 para Horizontal, 1 para Vertical.
 * @return int Retorna 1 se o navio foi posicionado com sucesso, 0 caso contrário.
 */
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaInicial, int colunaInicial, int orientacao) {
    // Vetores para representar o navio (apenas para fins conceituais, 
    // o valor 3 é copiado diretamente no tabuleiro)
    // int navio[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO}; // Navio = {3, 3, 3}

    // 1. Validação de Limites
    if (orientacao == 0) { // Horizontal
        // Verifica se o navio ultrapassa a borda direita do tabuleiro
        if (colunaInicial < 0 || colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO || 
            linhaInicial < 0 || linhaInicial >= TAMANHO_TABULEIRO) {
            printf("[VAL. ERRO]: Limite - Navio Horizontal fora do tabuleiro.\n");
            return 0;
        }
    } else if (orientacao == 1) { // Vertical
        // Verifica se o navio ultrapassa a borda inferior do tabuleiro
        if (linhaInicial < 0 || linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO || 
            colunaInicial < 0 || colunaInicial >= TAMANHO_TABULEIRO) {
            printf("[VAL. ERRO]: Limite - Navio Vertical fora do tabuleiro.\n");
            return 0;
        }
    } else {
        printf("[VAL. ERRO]: Orientacao invalida (%d).\n", orientacao);
        return 0;
    }

    // 2. Validação de Sobreposição (Simplificada)
    // Verifica se alguma posição já está ocupada (valor 3) antes de posicionar
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linhaAtual = linhaInicial;
        int colunaAtual = colunaInicial;

        if (orientacao == 0) { // Horizontal
            colunaAtual += i;
        } else { // Vertical
            linhaAtual += i;
        }

        // Verifica a sobreposição
        if (tabuleiro[linhaAtual][colunaAtual] == NAVIO) {
            printf("[VAL. ERRO]: Sobreposicao detectada em (%d, %d).\n", linhaAtual, colunaAtual);
            return 0; // Sobreposição
        }
    }

    // 3. Posicionamento (Se todas as validações passarem)
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (orientacao == 0) { // Horizontal
            // Copia o valor 3 (NAVIO) para as posições (linhaInicial, colunaInicial + i)
            tabuleiro[linhaInicial][colunaInicial + i] = NAVIO;
        } else { // Vertical
            // Copia o valor 3 (NAVIO) para as posições (linhaInicial + i, colunaInicial)
            tabuleiro[linhaInicial + i][colunaInicial] = NAVIO;
        }
    }

    return 1; // Sucesso no posicionamento
}

/**
 * @brief Exibe o tabuleiro no console de forma organizada.
 * * @param tabuleiro A matriz do tabuleiro a ser exibida.
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   "); // Espaço para alinhamento das colunas
    
    // Imprime o cabeçalho das colunas (0 a 9)
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");
    
    printf("  +--------------------\n"); // Separador

    // Loop aninhado para imprimir o conteúdo da matriz
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d |", i); // Imprime o índice da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Imprime o valor da posição seguido por um espaço para organização
            printf("%d ", tabuleiro[i][j]); 
        }
        printf("\n"); // Quebra de linha no final de cada linha da matriz
    }
}