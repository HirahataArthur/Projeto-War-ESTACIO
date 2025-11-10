#include <stdio.h>
#include <string.h>

// Definição da struct "Territorio"
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
} Territorio;

int main() {
    // armazenar 5 territórios
    Territorio territorios[5];

    // dados dos territórios
    printf("Cadastro de 5 territórios:\n\n");

    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);

        // nome do território
        printf("Digite o nome do território: ");
        scanf("%s", territorios[i].nome);

        //cor do exército
        printf("Digite a cor do exército: ");
        scanf("%s", territorios[i].cor);

        // quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n"); // Espaço entre os cadastros
    }

   
    printf("Dados dos territórios cadastrados:\n\n");

    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
        printf("--------------------------\n");
    }

    return 0;
}

