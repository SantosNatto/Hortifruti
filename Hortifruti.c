#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_PRODUTOS 100
void clear() {
    #ifdef __linux__
        system("clear");
    #else
        system("cls");
    #endif
}
typedef enum {
    FRUTAS = 1,
    LEGUMES,
    VERDURAS,
    ORGANICOS
} Categoria;

typedef enum {
    KG = 1,
    UNIDADE,
    PACOTE,
    GRAMAS
} UnidadeDeMedida;

//-------------------------------------------------DATA--------------------------------------------------
typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;
//---------------------------------------------ESTRUTURA DE CADASTRO--------------------------------------
void UnidadeMedida();

typedef struct cadastro {
    char nome[50];
    float pesog;
    float pesoKg;
    Categoria tipo;
    float preco;
    int estoque;
    UnidadeDeMedida unidadeDeMedida;
    char fornecedor[50];
    int CodProduto;
    Data validade;
} Produtos;
//------------------------------------------vARIAVEIS MUNDIAIS-------------------------------------------
int men = 0;
Produtos listaProdutos[MAX_PRODUTOS];
int totalProdutos = 0;
//------------------------------------------------FUNÇÕES------------------------------------------------
const char* getNomeCategoria(Categoria tipo) {
    switch (tipo) {
        case FRUTAS:
            return "Frutas";
        case LEGUMES:
            return "Legumes";
        case VERDURAS:
            return "Verduras";
        case ORGANICOS:
            return "Organicos";
        default:
            return "Desconhecido";
    }
}

void lerData(char* entrada, Data* data);

void menu();

void menuProdutos();

void cadastroProduto();

void excluirP();

void listarP();

void editarP();

void exibirProduto(Produtos *produto);
//---------------------------------------CODIGO PRINCIPAL------------------------------------------------------

int main(){
    clear();
    while (men != 6){
        menu();

        switch (men)
        {
        case 1:
            menuProdutos();
            break;
        case 5:
            clear();
            printf("Saindo....");
            Sleep(2000);
            clear();
            return 1;
        default:
            break;
        }
    }
    
    return 0;
}
//--------------------------------------------------------------------FUNÇÕES---------------------------------------------------------------------

//---------------------------------------------------------------UNIDADE DE MEDIDA----------------------------------------------------------------
void UnidadeMedida() {
    printf("\nUnidade de medida:\n");
    printf("1. KG\n");
    printf("2. Unidade\n");
    printf("3. Pacote\n");
    printf("4. Gramas\n");
    printf("Escolha a unidade de medida: ");
}

//--------------------------------------------------------------LER DATA---------------------------------------------------------

void lerData(char *entrada, Data *data) {
    int dia, mes, ano;

    if (strlen(entrada) == 8 && sscanf(entrada, "%2d%2d%4d", &dia, &mes, &ano) == 3) {
        if (dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12 && ano >= 1900) {
        data->dia = dia;
        data->mes = mes;
        data->ano = ano;
        return;
        }
    } 
    
 else if (strlen(entrada) == 10 && sscanf(entrada, "%d/%d/%d", &dia, &mes, &ano) == 3){
       if (dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12 && ano >= 1900) {
        data->dia = dia;
        data->mes = mes;
        data->ano = ano;
        return;
       }
    } 
        data->dia = data->mes = data->ano = -1;

}

//-------------------------------------------------------------menu---------------------------------------------------------------------------

void menu(){
    clear();
    printf("-----Menu-----\n");
    printf("1. Cadastro de produtos\n");
    printf("2. Fluxo de caixa\n");
    printf("3. Estoque\n");
    printf("4. Relatorio de ajuda a comunidade\n");
    printf("5. Sair\n");
    printf("------------------------------------------\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &men);
    getchar();
}

//---------------------------------------------------------------MENU PRODUTOS--------------------------------------------------------------------

void menuProdutos(){
    int opcao = 0;
    clear();
    printf("-----Cadastro de produtos-----\n\n");
    printf("1. Cadastrar novo produto\n");
    printf("2. Excluir produto\n");
    printf("3. listar produtos cadastrados\n");
    printf("4. Editar produto cadastrado\n");
    printf("5. Voltar para o menu principal\n");
    printf("------------------------------------------\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao)
    {
    case 1:
        cadastroProduto();
        break;
    case 2:
        excluirP();
        break;
    case 3:
        listarP();
        break;
    case 4:
        editarP();
        break;
    case 5:
        menu();
        break;
    default:
        printf("Opcao invalida!! favor tente outra opcao\n");
        break;
    }
}

//-------------------------------------------------------------CADASTRO PRODUTOS----------------------------------------------------

void cadastroProduto(){
    if (totalProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos alcançado!\n");
        Sleep(2000);
        return;
    }

    Produtos produto;
    int campo = 1;
    int opcaoCategoria = 0;
    char dataEntrada[11];
    
    while (campo <= 7){
        switch (campo)
        {
        case 1:
            clear();
            printf("-----Cadatro de produtos-----\n\n");
            printf("Nome do produto: ");
            fgets(produto.nome, sizeof(produto.nome), stdin);
            produto.nome[strcspn(produto.nome, "\n")] = '\0';
            break;
        case 2:
            clear();
            printf("-----Cadatro de produtos-----\n\n");
            printf("Nome: %s\n", produto.nome);
            printf("--------------------------------------------\n\n");
            printf("Categoria:\n\n");
            printf("1. Frutas\n");
            printf("2. Legumes\n");
            printf("3. Verduras\n");
            printf("4. Organicos\n");
            printf("Escolha a categoria: ");
            scanf("%d", &opcaoCategoria);
            getchar();
            produto.tipo = opcaoCategoria;
            break;
        case 3:
            clear();
            printf("Nome: %s\n", produto.nome);
            printf("Categoria: %s\n", getNomeCategoria(produto.tipo));
            printf("--------------------------------------------\n\n");
            printf("Quantidade em estoque: ");
            scanf("%d", &produto.estoque);
            getchar();
            break;
        case 4:
            clear();
            printf("Nome: %s\n", produto.nome);
            printf("Categoria: %s\n", getNomeCategoria(produto.tipo));
            printf("Quantidade em estoque: %d\n", produto.estoque);
            printf("--------------------------------------------\n\n");
            UnidadeMedida();
            int opcaoUnidade;
            scanf("%d", &opcaoUnidade);
            getchar();
            produto.unidadeDeMedida = opcaoUnidade;
            break;
        case 5:
            clear();
            printf("Nome: %s\n", produto.nome);
            printf("Categoria: %s\n", getNomeCategoria(produto.tipo));
            printf("Quantidade em estoque: %d\n", produto.estoque);
            printf("Unidade de medida: ");
                switch (produto.unidadeDeMedida) {
                    case KG:
                        printf("KG\n");
                        break;
                    case UNIDADE:
                        printf("Unidade\n");
                        break;
                    case PACOTE:
                        printf("Pacote\n");
                        break;
                    case GRAMAS:
                        printf("Gramas\n");
                        break;
                }
            printf("\n--------------------------------------------\n\n");
            printf("Preco: R$ ");
            scanf("%f", &produto.preco);
            getchar();
            break;
        case 6:
            clear();
            printf("Nome: %s\n", produto.nome);
            printf("Categoria: %s\n", getNomeCategoria(produto.tipo));
            printf("Quantidade em estoque: %d\n", produto.estoque);
            printf("Unidade de medida: ");
                switch (produto.unidadeDeMedida) {
                    case KG:
                        printf("KG\n");
                        break;
                    case UNIDADE:
                        printf("Unidade\n");
                        break;
                    case PACOTE:
                        printf("Pacote\n");
                        break;
                    case GRAMAS:
                        printf("Gramas\n");
                        break;
                }
            printf("Preco: R$%.2f\n", produto.preco);
            printf("--------------------------------------------\n\n");
            printf("Data de validade: ");
            fgets(dataEntrada, sizeof(dataEntrada), stdin);
            dataEntrada[strcspn(dataEntrada, "\n")] = '\0';
            lerData(dataEntrada, &produto.validade);
            break;
        case 7:
            clear();
            printf("Nome: %s\n", produto.nome);
            printf("Categoria: %s\n", getNomeCategoria(produto.tipo));
            printf("Quantidade em estoque: %d\n", produto.estoque);
            printf("Unidade de medida: ");
                switch (produto.unidadeDeMedida) {
                    case KG:
                        printf("KG\n");
                        break;
                    case UNIDADE:
                        printf("Unidade\n");
                        break;
                    case PACOTE:
                        printf("Pacote\n");
                        break;
                    case GRAMAS:
                        printf("Gramas\n");
                        break;
                }
            printf("Preco: R$%.2f\n", produto.preco);
            printf("--------------------------------------------\n\n");
            printf("Fornecedor: ");
            fgets(produto.fornecedor, sizeof(produto.fornecedor), stdin);
            produto.fornecedor[strcspn(produto.fornecedor, "\n")] = '\0';    
            break;
        default:
            break;
        }
        int escolha;
        printf("\n1. Continuar\n2. Voltar para o campo anterior\nEscolha: ");
        scanf("%d", &escolha);
        getchar();
        if (escolha == 2 && campo > 1) {
            campo--;
        } else {
            campo++;
        }

        clear();
    }
        produto.CodProduto = totalProdutos + 1;

        listaProdutos[totalProdutos] = produto;
        totalProdutos++;

        
    clear();

    printf("Nome: %s\n", produto.nome);
    printf("Categoria: %s\n", getNomeCategoria(produto.tipo));
    printf("Quantidade em Estoque: %d\n", produto.estoque);
    printf("Unidade de medida: ");
    switch (produto.unidadeDeMedida) {
    case KG:
        printf("KG\n");
        break;
    case UNIDADE:
        printf("Unidade\n");
        break;
    case PACOTE:
        printf("Pacote\n");
        break;
    case GRAMAS:
        printf("Gramas\n");
        break;
    }

    printf("Preco: R$%.2f\n", produto.preco);
    printf("Data de validade: %02d/%02d/%d\n", produto.validade.dia, produto.validade.mes, produto.validade.ano);
    printf("Fornecedor: %s\n", produto.fornecedor);
    printf("Codigo do produto: %d\n\n", produto.CodProduto);

    printf("Produto cadastrado com sucesso!!\n");
    printf("Pressione enter para continuar...\n");
    getchar();
}

//----------------------------------------------------------EXCLUIR PRODUTOS---------------------------------------------------------------

void excluirP(){
    int cod = 0;
    int resp = 0;
    if (totalProdutos == 0)
    {
        printf("Nunhum produto cadastrado!!\n");
        Sleep(2300);
        clear();
        return;
    }
    
    printf("-----Excluir produto-----\n\n");
    printf("Digite o codigo do produto: ");
    scanf("%d", &cod);
    getchar();

    int encontrado = -1;

    for (int i = 0; i < totalProdutos; i++) {
        if (listaProdutos[i].CodProduto == cod) {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1) {
        printf("Produto com codigo %d nao encontrado.\n", cod);
    } else {
        printf("\nAtencao!! Vece realmente deseja continuar com a exclusao deste produto?\n");
        printf("1.Sim\n2.nao\n");
        scanf("%d", &resp);
        getchar();

        if (resp == 1){
            for (int i = encontrado; i < totalProdutos - 1; i++) {
                listaProdutos[i] = listaProdutos[i + 1];
        }
        totalProdutos--;
        printf("Produto excluido com sucesso!\n");

        } else {
            printf("Operacao de exclusao cancelada.\n");
            return;
        }
        
        
    }
    Sleep(2000);
    clear();
}

//---------------------------------------------------------------listar produtos---------------------------------------------------------

void listarP(){
    clear();
    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado!\n");
        printf("Pressione Enter para voltar ao menu.\n");
        getchar();
        return;
    }

    printf("----- Produtos Cadastrados -----\n\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("Codigo: %d\n", listaProdutos[i].CodProduto);
        printf("Nome: %s\n", listaProdutos[i].nome);
        printf("Categoria: %s\n", getNomeCategoria(listaProdutos[i].tipo));
        printf("Quantidade em Estoque: %d\n", listaProdutos[i].estoque);
        printf("Unidade de medida: ");
        switch (listaProdutos[i].unidadeDeMedida) {
            case KG: printf("KG\n"); break;
            case UNIDADE: printf("Unidade\n"); break;
            case PACOTE: printf("Pacote\n"); break;
            case GRAMAS: printf("Gramas\n"); break;
        }
        printf("Preco: R$%.2f\n", listaProdutos[i].preco);
        printf("Data de validade: %02d/%02d/%d\n", listaProdutos[i].validade.dia, listaProdutos[i].validade.mes, listaProdutos[i].validade.ano);
        printf("Fornecedor: %s\n", listaProdutos[i].fornecedor);
        printf("----------------------------------\n");
    }
    printf("Pressione enter para voltar para a tela inicial\n");
    getchar();
}

//-------------------------------------------------------------EDITAR PRODUTO----------------------------------------------------------------

void editarP(){ 
    int codP, encontrado = -1;
    int opcaoE = 0;
    int escolha;

    clear();

        if (totalProdutos == 0){
            printf("Nenhum produto cadastrado!\n");
            Sleep(2000);
            clear();
            return;
        }
        
    printf("-----Editar Produto-----\n\n");
    printf("Deseja buscar o produto pelo:\n1. Codigo\n2. Nome\nEscolha: ");
    scanf("%d", &opcaoE);
    getchar();

    Produtos *produto = NULL;

    if (opcaoE == 1){
        clear();
        printf("-----Editar produto-----\n\n");
        printf("Digite o codigo do produto: ");
        scanf("%d", &codP);
        getchar();

        for (int i = 0; i < totalProdutos; i++) {
            if (listaProdutos[i].CodProduto == codP) {
                encontrado = i;
                produto = &listaProdutos[encontrado];
                break;
            }
        }    
        if (encontrado == -1) {
            printf("Produto com codigo %d nao encontrado.\n", codP);
            Sleep(2000);
            clear();
            return;
        } 
    } else if (opcaoE == 2){
        char nome[50];
        printf("Digite o nome do produto: ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0';

        Produtos *produtosE[totalProdutos];
        int contE = 0;

        for (int i = 0; i < totalProdutos; i++){
            if (strstr(listaProdutos[i].nome, nome) != NULL){
                produtosE[contE++] = &listaProdutos[i];
            }
            
        }
        
        if (contE == 0){
            printf("Nenhum produto encontrado com o nome \"%s\". \n", nome);
            Sleep(2000);
            return;   
        } else if (contE == 1){
            produto = produtosE[0];
        } else{
            printf("Foram encontrados %d produtos: \n", contE);
            for (int i = 0; i < contE; i++){
                printf("%d. codigo: %d, nome: %s\n", i + 1, produtosE[i]->CodProduto, produtosE[i]->nome);
            }
        printf("Escolha o numero do produto que deseja editar: ");
        scanf("%d", &escolha);
        getchar();   
        }
        
        if (escolha < 1 || escolha > contE){
            printf("Opcao invalida!\n");
            Sleep(2000);
            return;
        }
        produto = produtosE[escolha - 1];
        
    } else{
        printf("Opcao invalida\n");
        Sleep(2000);
        return;
    }
    clear();
    
    exibirProduto(produto);

    printf("Nome atual: %s\n", produto->nome);
    printf("Novo nome (ou pessione enter para manter): ");
    char nomeN[50];
    fgets(nomeN, sizeof(nomeN), stdin);
    if (nomeN[0] != '\n'){
        strcpy(produto->nome, nomeN);
        produto->nome[strcspn(produto->nome, "\n")] = '\0';
    }
    clear();
    
    exibirProduto(produto);
    printf("Categoria atual: %s\n", getNomeCategoria(produto->tipo));

    printf("Deseja alterar a categoria?\n1. Sim\n2. Nao\nEscolha: ");
    int alterarC;
    scanf("%d", &alterarC);
    getchar();
    if (alterarC == 1){
        printf("1. Frutas\n2. Legumes\n3. Verduras\n4. Orgânicos\nEscolha a nova categoria: ");
        scanf("%d", &alterarC);
        getchar();
        produto->tipo = (Categoria)alterarC;
    }
    clear();
    
    exibirProduto(produto);


    printf("Estoque atual: %d\nNovo estoque (ou pessione enter para manter): ", produto->estoque);
    char estoqueN[10];
    fgets(estoqueN, sizeof(estoqueN), stdin);
    if (estoqueN[0] != '\n'){
        produto->estoque = atoi(estoqueN);
    }
    clear();
    
    exibirProduto(produto);

    printf("Unidade de medida atual: ");
    switch (produto->unidadeDeMedida) {
        case KG: printf("KG\n"); break;
        case UNIDADE: printf("Unidade\n"); break;
        case PACOTE: printf("Pacote\n"); break;
        case GRAMAS: printf("Gramas\n"); break;
    }
    printf("Deseja alterar a unidade de medida?\n1. Sim\n2. Nao\nEscolha: ");
    scanf("%d", &alterarC);
    getchar();
    if (alterarC == 1) {
        UnidadeMedida();
        scanf("%d", &alterarC);
        getchar();
        produto->unidadeDeMedida = (UnidadeDeMedida)alterarC;
    }
    clear();
    
    exibirProduto(produto);

    printf("Valor atual: R$%.2f\nNovo valor (ou pressione Enter para manter): ", produto->preco);
    char novoPreco[10];
    fgets(novoPreco, sizeof(novoPreco), stdin);
    if (novoPreco[0] != '\n') {
        produto->preco = atof(novoPreco);
    }
    clear();
    
    exibirProduto(produto);

    printf("Data de validade atual: %02d/%02d/%d\nNova validade (ou pressione Enter para manter): ", produto->validade.dia, produto->validade.mes, produto->validade.ano);
    char novaValidade[11];
    fgets(novaValidade, sizeof(novaValidade), stdin);
    novaValidade[strcspn(novaValidade, "\n")] = '\0';
    
    if (novaValidade[0] != '\0') {
        lerData(novaValidade, &produto->validade);
        
    }

    clear();
    
    exibirProduto(produto);

    printf("Fornecedor atual: %s\nNovo fornecedor (ou pressione Enter para manter): ", produto->fornecedor);
    char novoFornecedor[50];
    fgets(novoFornecedor, sizeof(novoFornecedor), stdin);
    if (novoFornecedor[0] != '\n') {
        strcpy(produto->fornecedor, novoFornecedor);
        produto->fornecedor[strcspn(produto->fornecedor, "\n")] = '\0';
    }
    clear();

    exibirProduto(produto);

    printf("Produto atualizado com sucesso!\n");
    printf("Pressione Enter para voltar ao menu.\n");
    getchar();
}

//--------------------------------------------------------EXIBIR O DADS DO PRODUTOS----------------------------------------------------

void exibirProduto(Produtos *produto) {
    printf("Editando o Produto - Codigo: %d\n", produto->CodProduto);
    printf("---------------------------------------------------------------------------------\n");
    printf("Nome: %s\n", produto->nome);
    printf("Categoria: %s\n", getNomeCategoria(produto->tipo));
    printf("Estoque: %d\n", produto->estoque);
    printf("Unidade de medida: ");
    switch (produto->unidadeDeMedida) {
        case KG: printf("KG\n"); break;
        case UNIDADE: printf("Unidade\n"); break;
        case PACOTE: printf("Pacote\n"); break;
        case GRAMAS: printf("Gramas\n"); break;
    }
    printf("Valor: R$%.2f\n: ", produto->preco);
    printf("Data de validade: %02d/%02d/%d\n", produto->validade.dia, produto->validade.mes, produto->validade.ano);
    printf("Fornecedor: %s\n", produto->fornecedor);
    printf("---------------------------------------------------------------------------------\n\n");
    //ksjjkd
}