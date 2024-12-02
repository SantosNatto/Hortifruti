#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>

#define MAX_TRANSACOES 100
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

Data obterDataAtual() {
    Data dataAtual;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    dataAtual.dia = tm.tm_mday;
    dataAtual.mes = tm.tm_mon + 1;
    dataAtual.ano = tm.tm_year + 1900;

    return dataAtual;
}
//---------------------------------------------ESTRUTURA DE CADASTRO--------------------------------------
typedef struct {
    char descricao[100];
    float valor;
    char tipo; // 'E' para entrada, 'S' para saída
    Data data;
} Transacao;


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
//------------------------------------------vARIAVEIS GLOBAIS-------------------------------------------
int men = 0;
Produtos listaProdutos[MAX_PRODUTOS];
int totalProdutos = 0;
int totalTransacoes = 0;
Transacao listaTransacoes[MAX_TRANSACOES];
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
const char* getNomeUnidade(UnidadeDeMedida unidade) {
    switch (unidade) {
        case KG: return "KG";
        case UNIDADE: return "Unidade";
        case PACOTE: return "Pacote";
        case GRAMAS: return "Gramas";
        default: return "Desconhecido";
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

void SalvarArquivoCSV();

void CarregarArquivoCSV(const char *BDados);

void registrarTransacao();

void exibirTransacoes();

void salvarTransacoes();

void carregarTransacoes();

void menuFluxoCaixa();

void registrarDoacao();
//---------------------------------------CODIGO PRINCIPAL------------------------------------------------------

int main(){
    clear();
    const char *BDados = "BDados.csv";
        CarregarArquivoCSV(BDados);
        carregarTransacoes();
    while (men != 6){
        menu();

        switch (men)
        {
        case 1:
            menuProdutos();
            break;
        case 2:
            menuFluxoCaixa();
            break;
        case 3:
            listarP();
            break;
        case 4:
            registrarDoacao();
            break;
        case 5:
            clear();
            printf("Saindo....");
            SalvarArquivoCSV();
            salvarTransacoes();
            Sleep(2000);
            clear();
            return 0;
        default:
            printf("Opcao invalida. Tente novamente!\n");
            Sleep(1500);
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
            printf("Unidade de medida: %s\n", getNomeUnidade(produto.unidadeDeMedida));
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
            printf("Unidade de medida: %s\n", getNomeUnidade(produto.unidadeDeMedida));
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
            printf("Unidade de medida: %s\n", getNomeUnidade(produto.unidadeDeMedida));
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
    printf("Unidade de medida: %s\n", getNomeUnidade(produto.unidadeDeMedida));
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
        printf("Unidade de medida: %s\n", getNomeUnidade(listaProdutos[i].unidadeDeMedida));
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
}

void SalvarArquivoCSV(){
    char caminhoArquivo[260];
    snprintf(caminhoArquivo, sizeof(caminhoArquivo),"BDados.csv");

    FILE *arquivo = fopen(caminhoArquivo, "w");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    
    fprintf(arquivo, "Codigo;Nome;Categoria;Estoque;Preco;Unidade de Medida;Validade;Fornecedor\n");

    for (int i = 0; i < totalProdutos; i++){
        Produtos *produto = &listaProdutos[i];
        fprintf(arquivo, "%d;%s;%d;%d;%.2f;%d;%02d/%02d/%04d;%s\n",
                produto->CodProduto,
                produto->nome,
                produto->tipo,
                produto->estoque,
                produto->preco,
                produto->unidadeDeMedida,
                produto->validade.dia,
                produto->validade.mes,
                produto->validade.ano,
                produto->fornecedor);

    }
    fclose(arquivo);
    printf("Produtos salvos com sucesso no arquivo %s\n",caminhoArquivo);
}

void CarregarArquivoCSV(const char *BDados) {
    FILE *arquivo = fopen(BDados, "r");
    if (arquivo == NULL) {
        printf("Arquivo '%s' não encontrado. Criando um novo...\n", BDados);
        arquivo = fopen(BDados, "w");
        if (arquivo == NULL){
            printf("Erro ao criar o arquivo '%s'. Verifique as permissões.\n", BDados);
            return;
        }
        fprintf(arquivo, "Codigo;Nome;Categoria;Estoque;Preco;Unidade de Medida;Validade;Fornecedor\n");
        fclose(arquivo);
        printf("Arquivo criado com sucesso: %s\n", BDados);
        return;         
    }

    char linha[512];
    fgets(linha, sizeof(linha), arquivo);

    totalProdutos = 0;
    while (fgets(linha, sizeof(linha), arquivo)){
        if (totalProdutos >= MAX_PRODUTOS){
            printf("Numero maximo de produtos (%d) atingidos.\n", MAX_PRODUTOS);
            break;
        }

    Produtos *produto = &listaProdutos[totalProdutos];
    int tipo, unidade;

    sscanf(linha, "%d;%49[^;];%d;%d;%f;%d;%d/%d/%d;%49[^;\n]",
            &produto->CodProduto,
            produto->nome,
            &tipo,
            &produto->estoque,
            &produto->preco,
            &unidade,
            &produto->validade.dia,
            &produto->validade.mes,
            &produto->validade.ano,
            produto->fornecedor);

    produto->tipo = (Categoria)tipo;
    produto->unidadeDeMedida = (UnidadeDeMedida)unidade;

    totalProdutos++;
}
    fclose(arquivo);
    printf("Arquivo carregado com sucesso. Total de produtos: %d\n", totalProdutos);
}

// Funções para manipular o fluxo de caixa
void registrarTransacao() {
    clear();
    if (totalTransacoes >= MAX_TRANSACOES) {
        printf("Limite de transacoes atingido!\n");
        return;
    }

    Transacao novaTransacao;
    printf("Descricao da transacao: ");
    getchar(); // Consumir caractere pendente
    fgets(novaTransacao.descricao, sizeof(novaTransacao.descricao), stdin);
    novaTransacao.descricao[strcspn(novaTransacao.descricao, "\n")] = '\0';

    printf("Valor: ");
    scanf("%f", &novaTransacao.valor);

    printf("Tipo ('E' para entrada, 'S' para saida): ");
    getchar();
    scanf(" %c", &novaTransacao.tipo);

    // Tratamento da data (aceita dd/mm/AAAA ou ddmmaaaa)
    char dataEntrada[11]; // Considera data no formato dd/mm/aaaa ou ddmmaaaa
    printf("Data da transacao (dd/mm/AAAA ou ddmmaaaa): ");
    getchar(); // Limpar o buffer de entrada
    fgets(dataEntrada, sizeof(dataEntrada), stdin);
    dataEntrada[strcspn(dataEntrada, "\n")] = '\0';  // Remove o '\n'

    // Usa a função lerData para processar a data
    lerData(dataEntrada, &novaTransacao.data);

    if (novaTransacao.data.dia == -1 || novaTransacao.data.mes == -1 || novaTransacao.data.ano == -1) {
        printf("Data invalida! Transacao nao registrada.\n");
        return;
    }

    listaTransacoes[totalTransacoes] = novaTransacao;
    totalTransacoes++;

    printf("\nTransacao registrada com sucesso!\n");
    Sleep(1000);
    clear();
}

void exibirTransacoes() {
    clear();
    if (totalTransacoes == 0) {
        printf("Nenhuma transacao registrada.\n");
        return;
    }

    printf("----- Transacoes -----\n");
    float saldo = 0;

    for (int i = 0; i < totalTransacoes; i++) {
        Transacao t = listaTransacoes[i];
        printf("%d. %s - R$%.2f - %s - Data: %02d/%02d/%04d\n", i + 1, t.descricao, t.valor, 
        (tolower(t.tipo) == 'e') ? "Entrada" : "Saida", 
        t.data.dia, t.data.mes, t.data.ano);

        saldo += (tolower(t.tipo) == 'e' ? t.valor : -t.valor);
    }

    printf("\n----------------------\n");
    printf("Saldo atual: R$%.2f\n", saldo);
    printf("\n----------------------\n");
    printf("\nPressione enter para continuar");
    getchar();
    getchar();
    clear();
}

void salvarTransacoes() {
    FILE *arquivo = fopen("FluxoCaixa.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar transacoes.\n");
        return;
    }

    fprintf(arquivo, "Descricao;Valor;Tipo;Data\n");
    for (int i = 0; i < totalTransacoes; i++) {
        Transacao t = listaTransacoes[i];
        fprintf(arquivo, "%s;%.2f;%c;%02d/%02d/%04d\n", t.descricao, t.valor, t.tipo,
                t.data.dia, t.data.mes, t.data.ano);
    }

    fclose(arquivo);
    printf("\nTransacoes salvas com sucesso!\n");
    Sleep(1000);
    clear();
}

void carregarTransacoes() {
    clear();
    FILE *arquivo = fopen("FluxoCaixa.csv", "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo de transacoes encontrado. Criando um novo...\n");
        return;
    }

    char linha[200];
    fgets(linha, sizeof(linha), arquivo); // Ignorar cabeçalho

    totalTransacoes = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (totalTransacoes >= MAX_TRANSACOES) {
            printf("Limite de transacoes atingido!\n");
            break;
        }

        Transacao novaTransacao;
        int dia, mes, ano;
        char tipo;

        sscanf(linha, "%99[^;];%f;%c;%d/%d/%d", novaTransacao.descricao, &novaTransacao.valor, 
        &tipo, &dia, &mes, &ano);
        novaTransacao.tipo = tipo;

        novaTransacao.tipo = tipo;
        novaTransacao.data.dia = dia;
        novaTransacao.data.mes = mes;
        novaTransacao.data.ano = ano;

        listaTransacoes[totalTransacoes++] = novaTransacao;
    }

    fclose(arquivo);
    printf("Transacoes carregadas com sucesso!\n");
}

void menuFluxoCaixa() {
    clear();
    int opcao;
    do {
        printf("----- Menu Fluxo de Caixa -----\n");
        printf("1. Registrar transacao\n");
        printf("2. Exibir transacoes\n");
        printf("3. Salvar transacoes\n");
        printf("4. Carregar transacoes\n");
        printf("5. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                registrarTransacao();
                break;
            case 2:
                exibirTransacoes();
                break;
            case 3:
                salvarTransacoes();
                break;
            case 4:
                carregarTransacoes();
                break;
            case 5:
                printf("Voltando ao menu principal...\n");
                Sleep(1000);
                clear();
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);
}

void registrarDoacao() {
    clear();

    // Perguntar pelo produto a ser doado
    int codigoProduto;
    printf("Digite o codigo do produto a ser doado: ");
    scanf("%d", &codigoProduto);

    // Buscar o produto com o código fornecido
    Produtos *produtoDoado = NULL;
    for (int i = 0; i < totalProdutos; i++) {
        if (listaProdutos[i].CodProduto == codigoProduto) {
            produtoDoado = &listaProdutos[i];
            break;
        }
    }

    if (produtoDoado == NULL) {
        printf("Produto não encontrado.\n");
        Sleep(1500);
        return;
    }

    // Exibir as informações do produto
    printf("\nProduto encontrado:\n");
    printf("Nome: %s\n", produtoDoado->nome);
    printf("Quantidade no estoque: %d\n", produtoDoado->estoque);
    printf("Data de validade: %d/%d/%d\n", produtoDoado->validade.dia, produtoDoado->validade.mes, produtoDoado->validade.ano);
    printf("Preco unitario: R$ %.2f\n", produtoDoado->preco);
    printf("\n----------------------\n");

    // Perguntar a quantidade a ser doada
    int quantidadeDoada;
    printf("Digite a quantidade a ser doada: ");
    scanf("%d", &quantidadeDoada);

    if (quantidadeDoada > produtoDoado->estoque) {
        printf("Quantidade excede o estoque disponível.\n");
        Sleep(1500);
        return;
    }

    // Calcular o valor da doação com base na quantidade
    float valorDoacao = produtoDoado->preco * quantidadeDoada;
    printf("Valor da doacao: R$ %.2f\n", valorDoacao);

    // Atualizar o estoque do produto
    produtoDoado->estoque -= quantidadeDoada;

    // Registrar a transação de doação no fluxo de caixa
    Transacao novaTransacao;
    printf("Descricao da doacao: ");
    getchar(); // Consumir caractere pendente
    fgets(novaTransacao.descricao, sizeof(novaTransacao.descricao), stdin);
    novaTransacao.descricao[strcspn(novaTransacao.descricao, "\n")] = '\0';

    // Atribuindo o valor da doação calculado à transação
    novaTransacao.valor = valorDoacao;

    // Atribuindo a data atual à transação
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    novaTransacao.data.dia = tm.tm_mday;
    novaTransacao.data.mes = tm.tm_mon + 1;
    novaTransacao.data.ano = tm.tm_year + 1900;

    novaTransacao.tipo = 'S'; // Doação é uma saída de dinheiro
    listaTransacoes[totalTransacoes] = novaTransacao;
    totalTransacoes++;

    printf("\nDoacao registrada com sucesso!\n");
    Sleep(1500);
    clear();
}