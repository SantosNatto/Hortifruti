#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 100

// Estrutura para representar um produto
struct Produto {
    int codigo;        // Código único do produto
    char nome[100];    // Nome do produto
    int quantidade;    // Quantidade disponível no estoque
    float preco;       // Preço unitário do produto
};

// Estrutura para representar o estoque
struct Estoque {
    struct Produto produtos[MAX_PRODUTOS]; // Lista de produtos no estoque
    int totalProdutos;                     // Contagem total de produtos cadastrados
};

// Função para registrar a entrada (compra) de um produto no estoque
void registrarEntrada(struct Estoque *estoque, int codigo, int quantidade) {
    // Percorre o estoque para encontrar o produto com o código informado
    for (int i = 0; i < estoque->totalProdutos; i++) {
        if (estoque->produtos[i].codigo == codigo) {  // Encontrou o produto
            estoque->produtos[i].quantidade += quantidade; // Atualiza a quantidade do produto
            printf("Entrada registrada com sucesso!\n");
            return; // Sai da função
        }
    }
    printf("Produto nao encontrado!\n"); // Se não encontrou o produto
}

// Função para registrar a saída (venda) de um produto no estoque
void registrarSaida(struct Estoque *estoque, int codigo, int quantidade) {
    // Percorre o estoque para encontrar o produto com o código informado
    for (int i = 0; i < estoque->totalProdutos; i++) {
        if (estoque->produtos[i].codigo == codigo) { // Encontrou o produto
            // Verifica se há estoque suficiente para a venda
            if (estoque->produtos[i].quantidade >= quantidade) {
                estoque->produtos[i].quantidade -= quantidade; // Atualiza a quantidade do produto
                printf("Saida registrada com sucesso!\n");
            } else {
                printf("Estoque insuficiente!\n"); // Se não houver quantidade suficiente
            }
            return; // Sai da função
        }
    }
    printf("Produto não encontrado!\n"); // Se não encontrou o produto
}

// Função para salvar o estoque em um arquivo .csv
void salvarEstoqueEmArquivo(struct Estoque *estoque) {
    FILE *arquivo = fopen("estoque.csv", "w"); // Abre o arquivo para escrita

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Escreve o cabeçalho do arquivo CSV
    fprintf(arquivo, "Codigo,Nome,Quantidade,Preco\n");

    // Escreve os dados de cada produto
    for (int i = 0; i < estoque->totalProdutos; i++) {
        fprintf(arquivo, "%d,%s,%d,%.2f\n", estoque->produtos[i].codigo,
                estoque->produtos[i].nome,
                estoque->produtos[i].quantidade,
                estoque->produtos[i].preco);
    }

    fclose(arquivo); // Fecha o arquivo
    printf("Estoque salvo no arquivo 'estoque.csv' com sucesso!\n");
}

// Função principal que contém o menu e as opções para o usuário
int main() {
    struct Estoque estoque = {0};  // Inicializa o estoque vazio, com zero produtos

    // Menu de opções do sistema
    int opcao;
    do {
        // Exibe as opções para o usuário
        printf("\nMenu:\n");
        printf("1. Registrar compra (Entrada de produtos)\n");
        printf("2. Registrar venda (Saida de produtos)\n");
        printf("3. Salvar estoque em arquivo CSV\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        // Ação conforme a opção escolhida
        if (opcao == 1) {
            // Registrar a entrada de um produto (compra)
            int codigo, quantidade;
            printf("Digite o codigo do produto: ");
            scanf("%d", &codigo);
            printf("Digite a quantidade a ser comprada: ");
            scanf("%d", &quantidade);

            // Chama a função para registrar a entrada
            registrarEntrada(&estoque, codigo, quantidade);
        } else if (opcao == 2) {
            // Registrar a saída de um produto (venda)
            int codigo, quantidade;
            printf("Digite o codigo do produto: ");
            scanf("%d", &codigo);
            printf("Digite a quantidade a ser vendida: ");
            scanf("%d", &quantidade);

            // Chama a função para registrar a saída
            registrarSaida(&estoque, codigo, quantidade);
        } else if (opcao == 3) {
            // Salvar o estoque em um arquivo CSV
            salvarEstoqueEmArquivo(&estoque);
        }
    } while (opcao != 4); // Continua o menu até que o usuário escolha a opção 4 (Sair)

    return 0; // Finaliza o programa
}