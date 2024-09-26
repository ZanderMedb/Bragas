#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição de estrutura para representar um produto
typedef struct {
    char nome[100];
    char vendedor[100];
    int quantidade;
} produto;

// Estrutura para representar uma lista de produto
typedef struct {
    produto *produtos;
    int tamanho;
} Listaprodutos;

// Função para criar uma lista de produtos vazia.
Listaprodutos criarLista() {
    Listaprodutos lista;
    lista.produtos = NULL;
    lista.tamanho = 0;
    return lista;
}

    // Função para adicionar um produto à lista
    void adicionarproduto(Listaprodutos *lista, char nome[], char vendedor[], int quantidade) {
    lista->tamanho++;
    lista->produtos = realloc(lista->produtos, lista->tamanho * sizeof(produto));
    produto produto;
    // Copia os dados fornecidos para o produto temporario
    strcpy(produto.nome, nome);
    strcpy(produto.vendedor, vendedor);
    produto.quantidade = quantidade;
    // Adiciona o produto à lista
    lista->produtos[lista->tamanho - 1] = produto;
    printf("\n\nproduto adicionado com sucesso.\n\n");
}

    // Funçao para exibir os produtos de uma lista
    void exibirprodutos(Listaprodutos lista, const char *titulo) {
    // Verifica se a lista está vazia
    if (lista.tamanho == 0) {
        printf("\nVoce nao tem produtos adicionados.\n\n");
        return;
    }
    // Exibe o nome da lista
    printf("\n%s:\n", titulo);
    for (int i = 0; i < lista.tamanho; i++) {
        printf("produto %d:\n", i + 1);
        printf("Nome: %s\n", lista.produtos[i].nome);
        printf("vendedor: %s\n", lista.produtos[i].vendedor);
        printf("Quantidade: %d\n", lista.produtos[i].quantidade);
    }
    printf("\n\n");
}

    // Funçao para adicionar um produto a partir da estrada do usuario
    void adicionarprodutoLista(Listaprodutos *lista, const char *titulo) {
    char nome[100], vendedor[100];
    int quantidade;

    // Solicita os dados do produto
    printf("\nDigite o nome do produto para adicionar a lista de %s ('0' para voltar): ", titulo);
    scanf(" %[^\n]", nome);

    // Verifica se o usuario deseja voltar
    if (nome[0] == '0') return;

    printf("Digite a loja: ");
    scanf(" %[^\n]", vendedor);

    printf("Digite a quantidade de produtos que deseja: ");
    scanf("%d", &quantidade);

    // Chama a função para adicionar o produto à lista
    adicionarproduto(lista, nome, vendedor, quantidade);
}

    // Funçao para listar os produtos de uma lista
    void listarprodutos(Listaprodutos lista) {
    // Verifica se a lista esta vazia
    if (lista.tamanho == 0) {
        printf("\nNao ha produtos nesta lista.\n\n");
        return;
    }
    // Exibe os produtos na lista
    printf("\nprodutos na lista:\n");
    for (int i = 0; i < lista.tamanho; i++) {
        printf("%d. %s, por %s\n", i + 1, lista.produtos[i].nome, lista.produtos[i].vendedor);
    }
    printf("\n");
}
    // Funçao para apagar um produto de uma lista
    void apagarproduto(Listaprodutos *lista) {
    listarprodutos(*lista);
    int produtoSelecionado;
    printf("Digite o numero do produto que deseja apagar ('0' para voltar): ");
    scanf("%d", &produtoSelecionado);

    // Verifica se o usuario deseja voltar
    if (produtoSelecionado == 0) return;

    if (produtoSelecionado > 0 && produtoSelecionado <= lista->tamanho) {
        for (int i = produtoSelecionado - 1; i < lista->tamanho - 1; i++) {
            lista->produtos[i] = lista->produtos[i + 1];
        }
        lista->tamanho--;
        lista->produtos = realloc(lista->produtos, lista->tamanho * sizeof(produto));
        printf("\nproduto removido com sucesso.\n\n");
    } else {
        printf("\nproduto nao encontrado.\n\n");
    }
}

    // Funçao para editar as informações de um produto

    void editarproduto(Listaprodutos *listas) {
    printf("\nEscolha a lista (1 - Meus produtos, 2 - Lista de desejos): ");
    int listaSelecionada;
    scanf("%d", &listaSelecionada);

    // Verifica se a lista escolhida é valida

    if (listaSelecionada < 1 || listaSelecionada > 2) {
        printf("\nLista invalida.\n");
        return;
    }

    // Lista os produtos da lista selecionada

    listarprodutos(listas[listaSelecionada - 1]);

    int produtoSelecionado;
    printf("Digite o numero do produto que deseja editar ('0' para voltar): ");
    scanf("%d", &produtoSelecionado);

    if (produtoSelecionado == 0) return;

    if (produtoSelecionado > 0 && produtoSelecionado <= listas[listaSelecionada - 1].tamanho) {
        char nome[100], vendedor[100];
        int quantidade;

        // Solicita ao usuario as novas infos do produto
        printf("\nDigite o novo nome do produto: ");
        scanf(" %[^\n]", nome);

        printf("Digite o nova loja do produto: ");
        scanf(" %[^\n]", vendedor);

        printf("Digite a nova quantidade de produtos que deseja: ");
        scanf("%d", &quantidade);

        strcpy(listas[listaSelecionada - 1].produtos[produtoSelecionado - 1].nome, nome);
        strcpy(listas[listaSelecionada - 1].produtos[produtoSelecionado - 1].vendedor, vendedor);
        listas[listaSelecionada - 1].produtos[produtoSelecionado - 1].quantidade = quantidade;

        printf("\nproduto editado com sucesso.\n\n");
    } else {
        printf("\nproduto nao encontrado.\n\n");
    }
}

    // Funçao para salvar a lista de produtos em um arquivo

    void salvarLista(Listaprodutos lista, const char *nomeArquivo) {
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("\nErro ao criar o arquivo.\n\n");
        return;
    }

    // Escreva as informações dos produtos no arquivo

    for (int i = 0; i < lista.tamanho; i++) {
        fprintf(arquivo, "produto %d:\n", i + 1);
        fprintf(arquivo, "Nome: %s\n", lista.produtos[i].nome);
        fprintf(arquivo, "vendedor: %s\n", lista.produtos[i].vendedor);
        fprintf(arquivo, "Quantidade: %d\n\n", lista.produtos[i].quantidade);
    }
    fclose(arquivo);
    printf("\nLista de produtos salva no arquivo '%s'.\n\n", nomeArquivo);
}

    // Funçao de emprestar um produto da biblioteca 

    void emprestarproduto(Listaprodutos *lista, Listaprodutos *listaBiblioteca) {
    printf("\nprodutos disponiveis para emprestimo:\n");
    for (int i = 0; i < listaBiblioteca->tamanho; i++) {
        printf("%d. %s, por %s - Disponiveis: %d\n", i + 1, listaBiblioteca->produtos[i].nome,
               listaBiblioteca->produtos[i].vendedor, listaBiblioteca->produtos[i].quantidade);
    }
    int escolhaproduto;
    printf("Escolha o produto que deseja pegar emprestado ('0' para voltar): ");
    scanf("%d", &escolhaproduto);

    if (escolhaproduto == 0) return;

    if (escolhaproduto > 0 && escolhaproduto <= listaBiblioteca->tamanho) {
        char nome[100], vendedor[100];
        int quantidade;

        strcpy(nome, listaBiblioteca->produtos[escolhaproduto - 1].nome);
        strcpy(vendedor, listaBiblioteca->produtos[escolhaproduto - 1].vendedor);

        printf("Quantos produtos deseja pegar emprestado? ");
        scanf("%d", &quantidade);

        if (quantidade <= listaBiblioteca->produtos[escolhaproduto - 1].quantidade) {
            adicionarproduto(lista, nome, vendedor, quantidade);
            listaBiblioteca->produtos[escolhaproduto - 1].quantidade -= quantidade;
        } else {
            printf("\nNao ha produtos suficientes para emprestar.\n\n");
        }
    } else {
        printf("\nproduto nao encontrado.\n\n");
    }
}   
    // Funçao principal
    int main() {
    Listaprodutos meusprodutos = criarLista();
    Listaprodutos listaDesejos = criarLista();
    Listaprodutos listaBiblioteca = criarLista();

    // produtos disponiveis para emprestimo
    adicionarproduto(&listaBiblioteca, "", "", 0);
    adicionarproduto(&listaBiblioteca, "", "", 0);
    adicionarproduto(&listaBiblioteca, "", "", 0);

    int opcao;

    do {
        // Exibe o menu de opçoes
        printf("\nMenu:\n");
        printf("1. Adicionar produto\n");
        printf("2. Exibir meus produtos\n");
        printf("3. Adicionar produto a lista de desejos\n");
        printf("4. Editar produto\n");
        printf("5. Exibir lista de desejos\n");
        printf("6. Apagar produto\n");
        printf("7. Pegar produto emprestado\n");
        printf("8. Salvar lista de produtos\n");
        printf("9. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
    // Executa a opção escolhida pelos usuarios
    switch (opcao) {
            case 1:
                adicionarprodutoLista(&meusprodutos, "Meus produtos");
                break;
            case 2:
                exibirprodutos(meusprodutos, "Meus produtos");
                break;
            case 3:
                adicionarprodutoLista(&listaDesejos, "Lista de desejos");
                break;
            case 4:
                editarproduto((Listaprodutos[]){meusprodutos, listaDesejos});
                break;
            case 5:
                exibirprodutos(listaDesejos, "Lista de desejos");
                break;
            case 6:
                printf("\nEscolha a lista (1 - Meus produtos, 2 - Lista de desejos): ");
                int listaSelecionada;
                scanf("%d", &listaSelecionada);
                if (listaSelecionada == 1) {
                    apagarproduto(&meusprodutos);
                } else if (listaSelecionada == 2) {
                    apagarproduto(&listaDesejos);
                } else {
                    printf("\nLista invalida.\n");
                }
                break;
            case 7:
                emprestarproduto(&meusprodutos, &listaBiblioteca);
                break;
            case 8:
                salvarLista(meusprodutos, "Lista_de_produtos.txt");
                break;
            case 9:
                printf("\nObrigado por utilizar o programa. Volte sempre!\n\n");
                break;
            default:
                printf("\nEssa opcao nao existe.\n");
                break;
        }   
          } while (opcao != 9);

    free(meusprodutos.produtos);
    free(listaDesejos.produtos);
    free(listaBiblioteca.produtos);

    return 0;
}
