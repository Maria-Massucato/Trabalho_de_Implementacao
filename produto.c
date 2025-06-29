#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"

// Função para adicionar um produto à lista
void adicionarProduto(ListaProdutos* lista) {
    Produto* novoProduto = (Produto*)malloc(sizeof(Produto));
    if (!novoProduto) {
        printf("Erro de alocacao!\n");
        return;
    }
    printf("Digite o ID: ");
    scanf("%d", &novoProduto->id);
    getchar();
    printf("Digite o nome: ");
    fgets(novoProduto->nome, sizeof(novoProduto->nome), stdin); // "fgets" lê uma linha inteira, incluindo espaços
    novoProduto->nome[strcspn(novoProduto->nome, "\n")] = 0;
    printf("Digite a descricao: ");
    fgets(novoProduto->descricao, sizeof(novoProduto->descricao), stdin); // "stdin" permite ler strings com espaços
    novoProduto->descricao[strcspn(novoProduto->descricao, "\n")] = 0; // "strcspn" remove o '\n' do final da string
    printf("Digite o preco: ");
    scanf("%f", &novoProduto->preco);
    getchar();

    novoProduto->proximo = lista->cabeca;
    lista->cabeca = novoProduto;
    lista->tamanho++;
    printf("Produto adicionado com sucesso!\n");
}

// Função para listar produtos
void listarProdutos(ListaProdutos* lista) {
    Produto* atual = lista->cabeca;
    if (!atual) {
        printf("Lista vazia!\n");
        return;
    }
    while (atual) {
        // Exibe os detalhes do produto atual
        printf("ID: %d, Nome: %s, Descricao: %s, Preco: %.2f\n", 
            atual->id, atual->nome, atual->descricao, atual->preco);
        atual = atual->proximo;
    }
}

// Função para buscar um produto por ID
Produto* buscarProdutoPorID(ListaProdutos* lista, int id) {
    Produto* atual = lista->cabeca; 
    while (atual) {
        if (atual->id == id) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

// Função para excluir um produto da lista pelo ID
void excluirProduto(ListaProdutos* lista, int id) {
    Produto* atual = lista->cabeca; 
    Produto* anterior = NULL;
    while (atual && atual->id != id) { 
        anterior = atual;
        atual = atual->proximo;
    }
    if (!atual) {
        printf("Produto com ID %d nao encontrado.\n", id);
        return;
    }
    if (!anterior) {
        lista->cabeca = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    lista->tamanho--; // Decrementa o tamanho da lista
    printf("Produto com ID %d excluido com sucesso.\n", id);
}

// Função para liberar a memória da lista
void liberarLista(ListaProdutos* lista) {
    Produto* atual = lista->cabeca;
    while (atual) {
        Produto* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    lista->cabeca = NULL;
    lista->tamanho = 0;
}


// Função para comparar produtos por ID
int comparaPorID(const void *a, const void *b) {
    const Produto *prodA = *(const Produto **)a; // Converte o ponteiro void para ponteiro de Produto
    const Produto *prodB = *(const Produto **)b; 
    return prodA->id - prodB->id;
}

// Função para comparar produtos por nome
int comparaPorNome(const void *a, const void *b) {
    const Produto *prodA = *(const Produto **)a; 
    const Produto *prodB = *(const Produto **)b;
    return strcmp(prodA->nome, prodB->nome);
}

// Função para comparar produtos por preço
int comparaPorPreco(const void *a, const void *b) {
    const Produto *prodA = *(const Produto **)a;
    const Produto *prodB = *(const Produto **)b;
    if (prodA->preco < prodB->preco) return -1; // prodA é mais barato que prodB
    if (prodA->preco > prodB->preco) return 1; // prodA é mais caro que prodB
    return 0;
}

// Função para realizar busca binária em um vetor de produtos
Produto* buscaBinaria(Produto *produtos, int tamanho, int id) {
    int esq = 0, dir = tamanho - 1;
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        if (produtos[meio].id == id) {
            return &produtos[meio];
        } else if (produtos[meio].id < id) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    return NULL; // Produto não encontrado
}

// Função para ordenar a lista de produtos
void listarProdutosOrdenados(ListaProdutos *lista) {
    if (lista->tamanho <= 0) {
        printf("Lista vazia!\n");
        return;
    }

    int criterio;
    printf("Escolha o criterio de ordenacao:\n");
    printf("1. ID\n2. Nome\n3. Preco\n");
    printf("Opcao: ");
    scanf("%d", &criterio);
    getchar();

    // Aloca vetor de ponteiros para produtos usando o tamanho da lista
    // Isso permite que eu possa ordenar os produtos sem mover os dados reais
    Produto **vetor = (Produto **)malloc(lista->tamanho * sizeof(Produto *)); 
    if (!vetor) {
        printf("Erro de alocacao!\n");
        return;
    }

    Produto *atual = lista->cabeca;
    int i = 0;
    while (atual) {
        vetor[i++] = atual; // Copia o ponteiro para o vetor
        atual = atual->proximo;
    }

    // Ordena o vetor de acordo com o critério escolhido
    int (*comparador)(const void *, const void *);
    switch (criterio) {
        case 1:
            comparador = comparaPorID;
            break;
        case 2:
            comparador = comparaPorNome;
            break;
        case 3:
            comparador = comparaPorPreco;
            break;
        default:
            printf("Opcao invalida!\n");
            free(vetor);
            return;
    }

    // Ordena o vetor usando qsort, que é uma função da biblioteca padrão C
    qsort(vetor, lista->tamanho, sizeof(Produto *), comparador);

    // Exibe os produtos ordenados
    printf("\nProdutos ordenados:\n");
    for (i = 0; i < lista->tamanho; i++) {
        printf("ID: %d, Nome: %s, Descricao: %s, Preco: %.2f\n",
               vetor[i]->id, vetor[i]->nome, vetor[i]->descricao, vetor[i]->preco);
    }

    free(vetor);
}
