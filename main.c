#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"

// Função para exibir o menu principal do sistema
void exibirMenu()
{
    printf("Sistema de Cadastro e Organizacao de Produtos\n");
    printf("1. Adicionar Produto\n");
    printf("2. Listar Produtos\n");
    printf("3. Buscar Produto por ID\n");
    printf("4. Excluir Produto\n");
    printf("5. Listar Produtos Ordenados\n"); // NOVA OPÇÃO
    printf("6. Sair\n");
    printf("Escolha uma opcao: ");
}

int main()
{
    ListaProdutos lista; // Estrutura para armazenar a lista de produtos
    lista.cabeca = NULL; // Inicializa a lista principal como vazia
    lista.tamanho = 0;      // Inicializa a lista com tamanho zero

    int opcao;
    do
    {
        exibirMenu();
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch (opcao)
        {
        case 1:
            adicionarProduto(&lista);
            break;
        case 2:
            listarProdutos(&lista);
            break;
        case 3:
        {
            int id;
            printf("Digite o ID do produto para buscar: ");
            scanf("%d", &id);
            getchar();
            Produto *encontrado = buscarProdutoPorID(&lista, id); 
            if (encontrado)
            {
                printf("Produto encontrado:\n");
                printf("ID: %d\nNome: %s\nDescricao: %s\nPreco: %.2f\n", 
                    encontrado->id, encontrado->nome, encontrado->descricao, encontrado->preco);
            }
            else
            {
                printf("Produto com ID %d nao encontrado.\n", id);
            }
            break;
        }
        case 4:
        {
            int id;
            printf("Digite o ID do produto para excluir: ");
            scanf("%d", &id);
            getchar();
            excluirProduto(&lista, id);
            break;
        }
        case 5:
            listarProdutosOrdenados(&lista); // CHAMA A FUNÇÃO ORDENADA
            break;
        case 6:
            printf("Saindo do sistema...\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 6);

    liberarLista(&lista);
    return 0;
}
