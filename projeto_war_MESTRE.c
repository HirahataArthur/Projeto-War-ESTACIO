#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("Cadastro do território %d:\n", i + 1);
        printf("Nome: ");
        scanf("%s", mapa[i].nome);
        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("\n");
    }
}

// Função para exibir o mapa de territórios
void exibirMapa(Territorio* mapa, int quantidade) {
    printf("\n--- Mapa de Territórios ---\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("---------------------------\n");
    }
}

// Função que simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: não é possível atacar um território da mesma cor!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nAtaque de %s contra %s\n", atacante->nome, defensor->nome);
    printf("Dado atacante: %d\n", dadoAtacante);
    printf("Dado defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Vitória do atacante!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("Defensor resistiu ao ataque.\n");
        if (atacante->tropas > 0) {
            atacante->tropas--;
        }
    }
}

// Função que atribui uma missão aleatória ao jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Função que exibe a missão do jogador
void exibirMissao(char* missao) {
    printf("\nMissão do jogador: %s\n", missao);
}

// Função que verifica se a missão foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (strcmp(missao, "Conquistar 3 territórios seguidos") == 0) {
        int cont = 1;
        for (int i = 1; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, mapa[i - 1].cor) == 0) {
                cont++;
                if (cont >= 3) return 1;
            } else {
                cont = 1;
            }
        }
    } else if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    } else if (strcmp(missao, "Controlar metade dos territórios") == 0) {
        int azul = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) azul++;
        }
        if (azul >= tamanho / 2) return 1;
    } else if (strcmp(missao, "Ter pelo menos 5 territórios com mais de 10 tropas") == 0) {
        int cont = 0;
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 10) cont++;
        }
        if (cont >= 5) return 1;
    } else if (strcmp(missao, "Conquistar todos os territórios azuis") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) return 0;
        }
        return 1;
    }
    return 0;
}

// Função que libera a memória alocada
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

int main() {
    srand(time(NULL)); // Inicializa aleatoriedade

    int quantidade;
    printf("Digite o número de territórios: ");
    scanf("%d", &quantidade);

    // Alocação dinâmica dos territórios
    Territorio* mapa = (Territorio*)calloc(quantidade, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Vetor de missões disponíveis
    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar metade dos territórios",
        "Ter pelo menos 5 territórios com mais de 10 tropas",
        "Conquistar todos os territórios azuis"
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    // Alocação dinâmica da missão do jogador
    char* missaoJogador = (char*)malloc(100 * sizeof(char));
    if (missaoJogador == NULL) {
        printf("Erro ao alocar memória para missão.\n");
        free(mapa);
        return 1;
    }

    atribuirMissao(missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);

    cadastrarTerritorios(mapa, quantidade);
    exibirMapa(mapa, quantidade);

    // Simulação de um turno de ataque
    int atacante, defensor;
    printf("\nEscolha o território atacante (1 a %d): ", quantidade);
    scanf("%d", &atacante);
    printf("Escolha o território defensor (1 a %d): ", quantidade);
    scanf("%d", &defensor);

    if (atacante >= 1 && atacante <= quantidade && defensor >= 1 && defensor <= quantidade) {
        atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
    } else {
        printf("Territórios inválidos.\n");
    }

    exibirMapa(mapa, quantidade);

    // Verificação silenciosa da missão
    if (verificarMissao(missaoJogador, mapa, quantidade)) {
        printf("\nParabéns! Você cumpriu sua missão e venceu o jogo!\n");
    } else {
        printf("\nMissão ainda não cumprida. Continue jogando!\n");
    }

    liberarMemoria(mapa, missaoJogador);
    return 0;
}
