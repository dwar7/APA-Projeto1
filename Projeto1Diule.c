#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 1000

typedef struct {
    int id;
    char nome[50];
} Produto;

Produto estoque[MAX_PRODUTOS];
int numProdutos = 0;

int compararProdutos(const void *a, const void *b) {
    Produto *produtoA = (Produto *)a;
    Produto *produtoB = (Produto *)b;
    return strcmp(produtoA->nome, produtoB->nome);
}

void ordenarEstoque() {
    qsort(estoque, numProdutos, sizeof(Produto), compararProdutos);
}

int buscarProduto(const char *nomeProduto) {
    int inicio = 0;
    int fim = numProdutos - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int comparacao = strcmp(nomeProduto, estoque[meio].nome);

        if (comparacao == 0) {
            return estoque[meio].id;
        } else if (comparacao < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    return -1;
}

int buscarProdutoPorLetra(char letra) {
    int i;

    for (i = 0; i < numProdutos; i++) {
        if (estoque[i].nome[0] == letra) {
            return estoque[i].id;
        }
    }

    return -1;
}

int main() {
    char opcaoContinuar;
    char nomeProdutoBusca[50];

    do {
        printf("Digite o nome do produto: ");
        scanf("%s", estoque[numProdutos].nome);
        estoque[numProdutos].id = numProdutos + 1;
        numProdutos++;

        printf("Deseja adicionar mais produtos? (S/N): ");
        scanf(" %c", &opcaoContinuar);
    } while (opcaoContinuar == 'S' || opcaoContinuar == 's');

    ordenarEstoque();

    do {
        printf("Digite o nome do produto a ser buscado: ");
        scanf("%s", nomeProdutoBusca);

        int idProdutoBusca = buscarProduto(nomeProdutoBusca);

        if (idProdutoBusca != -1) {
            printf("Produto encontrado. ID: %d\n", idProdutoBusca);
        } else {
            printf("Produto não encontrado.\n");
        }

        printf("Deseja realizar outra busca? (S/N): ");
        scanf(" %c", &opcaoContinuar);
    } while (opcaoContinuar == 'S' || opcaoContinuar == 's');

    printf("\n");

    char letraBusca;
    printf("Digite a letra para buscar produtos que começam com essa letra: ");
    scanf(" %c", &letraBusca);

    int idProdutoLetra = buscarProdutoPorLetra(letraBusca);

    if (idProdutoLetra != -1) {
        printf("Produto encontrado. ID: %d\n", idProdutoLetra);
    } else {
        printf("Produto não encontrado.\n");
    }

    return 0;
}
