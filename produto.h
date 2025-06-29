#ifndef PRODUTO_H 
#define PRODUTO_H 

// Declaração da estrutura Produto e funções para gerenciar produtos
typedef struct Produto {
    int id;
    char nome[100];
    char descricao[255];
    float preco;
    struct Produto* proximo; // Ponteiro para o próximo produto na lista
} Produto;

// Estrutura para a lista de produtos
typedef struct {
    Produto *cabeca;
    int tamanho;
} ListaProdutos;

// Funções para gerenciar produtos
void adicionarProduto(ListaProdutos *lista);
void listarProdutos(ListaProdutos *lista);
Produto* buscarProdutoPorID(ListaProdutos *lista, int id);
void excluirProduto(ListaProdutos *lista, int id);
void liberarLista(ListaProdutos *lista);

// Comparadores (protótipos)
int comparaPorID(const void *a, const void *b); // const void* para compatibilidade com qsort  
int comparaPorNome(const void *a, const void *b); // "const" para evitar modificações
int comparaPorPreco(const void *a, const void *b); // "void*" para permitir qualquer tipo de dado

// Busca binária 
Produto* buscaBinaria(Produto *produtos, int tamanho, int id);

// Função para ordenar a lista de produtos
void listarProdutosOrdenados(ListaProdutos *lista);

#endif // PRODUTO_H
