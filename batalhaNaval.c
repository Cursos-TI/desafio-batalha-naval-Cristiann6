#include <stdio.h>
#include <stdlib.h>

// Definições de constantes para o Tabuleiro
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5 

#define TAMANHO_AOE 7 
#define CENTRO_AOE (TAMANHO_AOE / 2)

void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaInicial, int colunaInicial, int orientacao);
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void criarAoECone(int aoe[TAMANHO_AOE][TAMANHO_AOE]);
void criarAoECruz(int aoe[TAMANHO_AOE][TAMANHO_AOE]);
void criarAoEOctaedro(int aoe[TAMANHO_AOE][TAMANHO_AOE]);
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int aoe[TAMANHO_AOE][TAMANHO_AOE], int centroLinha, int centroColuna);


int main() {
    // 1. Representação do Tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    printf("--- Desafio Nivel Mestre: Habilidades Especiais (AoE) ---\n\n");

    // 2. Posicionar Navios 
    // Navios posicionados para serem atingidos pelas habilidades.
    posicionarNavio(tabuleiro, 2, 1, 0); // Horizontal em (2, 1)
    posicionarNavio(tabuleiro, 4, 6, 1); // Vertical em (4, 6)
    posicionarNavio(tabuleiro, 0, 0, 2); // Diagonal (++) em (0, 0)
    posicionarNavio(tabuleiro, 7, 8, 3); // Diagonal (+-) em (7, 8)

    // 3. Criar Matrizes de Habilidade
    int aoe_cone[TAMANHO_AOE][TAMANHO_AOE] = {0};
    int aoe_cruz[TAMANHO_AOE][TAMANHO_AOE] = {0};
    int aoe_octaedro[TAMANHO_AOE][TAMANHO_AOE] = {0};

    criarAoECone(aoe_cone);
    criarAoECruz(aoe_cruz);
    criarAoEOctaedro(aoe_octaedro);

    // 4. Integrar Habilidades ao Tabuleiro 
    
    // Habilidade 1: Cone
    int centroConeL = 1; 
    int centroConeC = 5; 
    printf("Aplicando Habilidade Cone em (%d, %d)...\n", centroConeL, centroConeC);
    aplicarHabilidade(tabuleiro, aoe_cone, centroConeL, centroConeC);

    // Habilidade 2: Cruz
    int centroCruzL = 6; 
    int centroCruzC = 3; 
    printf("Aplicando Habilidade Cruz em (%d, %d)...\n", centroCruzL, centroCruzC);
    aplicarHabilidade(tabuleiro, aoe_cruz, centroCruzL, centroCruzC);
    
    // Habilidade 3: Octaedro 
    int centroOctaedroL = 7; 
    int centroOctaedroC = 8; 
    printf("Aplicando Habilidade Octaedro (Losango) em (%d, %d)...\n", centroOctaedroL, centroOctaedroC);
    aplicarHabilidade(tabuleiro, aoe_octaedro, centroOctaedroL, centroOctaedroC);


    printf("\n");

    // 5. Exibir o Tabuleiro com Habilidades
    exibirTabuleiro(tabuleiro);

    return 0;
}

/**
 * @brief Cria a matriz de área de efeito em formato de Cone (apontando para baixo).
 * O cone é definido pelo triângulo superior na matriz.
 * @param aoe A matriz de habilidade (TAMANHO_AOE x TAMANHO_AOE) a ser preenchida.
 */
void criarAoECone(int aoe[TAMANHO_AOE][TAMANHO_AOE]) {
    
    for (int i = 0; i < TAMANHO_AOE; i++) {
        for (int j = 0; j < TAMANHO_AOE; j++) {
            // A largura (numero de elementos) na linha 'i' é (2 * i) + 1.
            // O centro é CENTRO_AOE.
            // A area afetada vai de: CENTRO_AOE - i até CENTRO_AOE + i
            if (j >= CENTRO_AOE - i && j <= CENTRO_AOE + i) {
                // Para limitar o cone a um tamanho razoavel 
                // A altura maxima do cone sera (CENTRO_AOE + 1)
                if (i <= CENTRO_AOE) {
                     aoe[i][j] = 1;
                } else {
                     aoe[i][j] = 0; 
                }
            } else {
                aoe[i][j] = 0;
            }
        }
    }
}

/**
 * @brief Cria a matriz de área de efeito em formato de Cruz, centrada.
 * A cruz é definida preenchendo a linha central e a coluna central.
 * @param aoe A matriz de habilidade (TAMANHO_AOE x TAMANHO_AOE) a ser preenchida.
 */
void criarAoECruz(int aoe[TAMANHO_AOE][TAMANHO_AOE]) {
    for (int i = 0; i < TAMANHO_AOE; i++) {
        for (int j = 0; j < TAMANHO_AOE; j++) {
            // Se a linha for a linha central OU a coluna for a coluna central, a posicao é 1.
            if (i == CENTRO_AOE || j == CENTRO_AOE) {
                aoe[i][j] = 1;
            } else {
                aoe[i][j] = 0;
            }
        }
    }
}

/**
 * @brief Cria a matriz de área de efeito em formato de Octaedro, centrada.
 * O losango é definido pela distância de Manhattan em relação ao centro: |i - centro| + |j - centro|
 * @param aoe A matriz de habilidade (TAMANHO_AOE x TAMANHO_AOE) a ser preenchida.
 */
void criarAoEOctaedro(int aoe[TAMANHO_AOE][TAMANHO_AOE]) {
    // Para um AoE 7x7, o centro é 3. A distancia maxima é 3.
    // Condicao: |i - CENTRO| + |j - CENTRO| <= RAIO
    int raio = CENTRO_AOE; 
    
    for (int i = 0; i < TAMANHO_AOE; i++) {
        for (int j = 0; j < TAMANHO_AOE; j++) {
            // Calcula a distância de Manhattan (abs() está na stdlib)
            int dist_manhattan = abs(i - CENTRO_AOE) + abs(j - CENTRO_AOE);
            
            if (dist_manhattan <= raio) {
                aoe[i][j] = 1; // Dentro do losango
            } else {
                aoe[i][j] = 0; // Fora
            }
        }
    }
}

/**
 * @brief Aplica a matriz de habilidade (AoE) no tabuleiro, centrando no ponto de origem.
 * Marca as posições afetadas com o valor HABILIDADE (5).
 * @param tabuleiro A matriz do tabuleiro 10x10.
 * @param aoe A matriz de habilidade (TAMANHO_AOE x TAMANHO_AOE) a ser sobreposta.
 * @param centroLinha A linha do tabuleiro que será o centro da habilidade.
 * @param centroColuna A coluna do tabuleiro que será o centro da habilidade.
 */
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int aoe[TAMANHO_AOE][TAMANHO_AOE], int centroLinha, int centroColuna) {
    // i e j iteram sobre a matriz AoE
    for (int i = 0; i < TAMANHO_AOE; i++) {
        for (int j = 0; j < TAMANHO_AOE; j++) {
        
            int tabLinha = centroLinha + (i - CENTRO_AOE);
            int tabColuna = centroColuna + (j - CENTRO_AOE);

            // 1. Condicional para validar limites do tabuleiro
            if (tabLinha >= 0 && tabLinha < TAMANHO_TABULEIRO &&
                tabColuna >= 0 && tabColuna < TAMANHO_TABULEIRO) 
            {
                // 2. Condicional para verificar se a posição do AoE deve ser aplicada (valor 1)
                if (aoe[i][j] == 1) {
                    // Sobrescreve a posição, MAS mantendo a posição do navio (3) se já estiver lá.
                    // O valor 5 é aplicado se for água (0) ou se for 5.
                    // Se for 3 , o valor 3 é mantido, mas um sistema de jogo
                    // real registraria que o navio foi atingido. Aqui, simplificamos.
                    if (tabuleiro[tabLinha][tabColuna] != NAVIO) {
                        tabuleiro[tabLinha][tabColuna] = HABILIDADE;
                    }
                }
            }
            // Se a coordenada estiver fora dos limites, simplesmente ignora.
        }
    }
}

void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaInicial, int colunaInicial, int orientacao) {
 
   // Simplificando o posicionamento apenas:
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linhaAtual = linhaInicial;
        int colunaAtual = colunaInicial;

        if (orientacao == 0) colunaAtual += i;       // Horizontal
        else if (orientacao == 1) linhaAtual += i;   // Vertical
        else if (orientacao == 2) { linhaAtual += i; colunaAtual += i; } // Diagonal (++)
        else if (orientacao == 3) { linhaAtual += i; colunaAtual -= i; } // Diagonal (+-)
        
        // Verifica limites antes de posicionar
        if (linhaAtual >= 0 && linhaAtual < TAMANHO_TABULEIRO && 
            colunaAtual >= 0 && colunaAtual < TAMANHO_TABULEIRO && 
            tabuleiro[linhaAtual][colunaAtual] != NAVIO) {
            tabuleiro[linhaAtual][colunaAtual] = NAVIO;
        } else {
            
        }
    }
    return 1;
}

/**
 * @brief Exibe o tabuleiro, usando caracteres visuais para ÁGUA, NAVIO e HABILIDADE.
 * @param tabuleiro A matriz do tabuleiro a ser exibida.
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   "); 
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j); 
    }
    printf("\n");
    
    printf("  +");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("---");
    }
    printf("-\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d |", i); 
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            
            if (tabuleiro[i][j] == NAVIO) {
                printf(" 🛳️ "); // Navio (3)
            } else if (tabuleiro[i][j] == HABILIDADE) {
                printf(" 💥 "); // Habilidade (5) - Area de Efeito
            } else {
                printf(" %d ", tabuleiro[i][j]); // Água (0) ou outro valor
            }
        }
        printf("\n"); 
    }
    printf("\nLegenda: 0=Água, 🛳️=Navio, 💥=Habilidade AoE\n");
}