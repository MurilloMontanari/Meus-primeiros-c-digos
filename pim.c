#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>  
#define MAX_PRODUTOS 100
#define COLUNA 80
#define LINHA 30
#define TAXA_CARTAO 0.03 
#define TAMANHO_NOME 100      
#define TAMANHO_CATEGORIA 50  
#define TAMANHO_DATA 11       


typedef struct {
    char nome[100];
    char categoria[50];
    int quantidade;
    float preco;
    char dataValidade[11];
} Produto;

typedef struct {
    float totalVendas;
    float totalLucro;
    float totalDoacao; 
} FluxoCaixa;

typedef struct {
    char produto[100];  
    char destino[100];  
    int quantidade;     
} Doacao;


Produto *produtos[MAX_PRODUTOS];
Doacao doacoes[MAX_PRODUTOS];  
int numProdutos = 0;
int numDoacoes = 0;  
FluxoCaixa fluxoCaixa = {0, 0, 0};


void menu();
void cadastrarProduto();
void listarProdutos();
void venderProduto();
void doarProdutos();
void listarProdutosParaDoacao();
void exibirFluxoCaixa();
void salvarEstoque();
void carregarEstoque();
void limparTela();
void gotoxy(int x, int y);
void printfCenter(char *texto, int linha);
void coluna(int posicao);
void linha(int y);
void limparBufferEntrada();
void removerProduto();
void pressionarQualquerTeclaParaVoltar();  

int main() {
    carregarEstoque();
    menu();
    salvarEstoque();
    return 0;
}

void menu() {
    char escolha;
    do {
        limparTela();
        coluna(0);
        coluna(COLUNA - 1);
        linha(0);
        printfCenter("PIM - SISTEMA HORTIFRUTI", 1);
        linha(2);

        gotoxy(20, 4);
        printf("[1] - ADICIONAR PRODUTO\n");
        gotoxy(20, 6);
        printf("[2] - LISTAR PRODUTOS\n");
        gotoxy(20, 8);
        printf("[3] - DOAR PRODUTOS\n");
        gotoxy(20, 10);
        printf("[4] - VENDER PRODUTO\n");
        gotoxy(20, 12);
        printf("[5] - EXIBIR FLUXO DE CAIXA\n");
        gotoxy(20, 14);
        printf("[6] - LISTAR PRODUTOS PARA DOACAO\n");
        gotoxy(20, 16);
        printf("[7] - REMOVER PRODUTO\n");
        gotoxy(20, 18);
        printf("[0] - SAIR\n");

        gotoxy(20, 20);
        printf("Escolha uma opcao: ");
        escolha = getch();  
        limparBufferEntrada();
        switch (escolha) {
            case '0':
                printf("\nSaindo...\n");
                break;
            case '1':
                limparTela();
                cadastrarProduto();
                break;
            case '2':
                limparTela();
                listarProdutos();
                break;
            case '3':
                limparTela();
                doarProdutos();
                break;
            case '4':
                limparTela();
                venderProduto();
                break;
            case '5':
                limparTela();
                exibirFluxoCaixa();
                break;
            case '6':
                limparTela();
                listarProdutosParaDoacao();
                break;
            case '7':
                limparTela();
                removerProduto();
                break;
            default:
                gotoxy(20, 22);
                printf("\nOpcao invalida! Tente novamente.\n");
                Sleep(1000);
                break;
        }

        if (escolha != '0') {
            pressionarQualquerTeclaParaVoltar();
        }

    } while (escolha != '0');
}

void pressionarQualquerTeclaParaVoltar() {
    gotoxy(20, 22);
    printf("\nPressione qualquer tecla para voltar ao menu principal...");
    getch();
}

void cadastrarProduto() {
    if (numProdutos >= MAX_PRODUTOS) {
        gotoxy(5, 4);
        printf("Estoque cheio! Nao e possivel adicionar mais produtos.\n");
        return;
    }

    Produto *novoProduto = (Produto *)malloc(sizeof(Produto)); 
    if (!novoProduto) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }

    limparTela();
    linha(0);
    printfCenter("PIM - CADASTRO DE PRODUTOS", 1);
    linha(2);
    coluna(0);
    coluna(COLUNA - 1);


    gotoxy(5, 4);
    printf("Digite o nome do produto: ");
    limparBufferEntrada();
    fgets(novoProduto->nome, TAMANHO_NOME, stdin);
    strtok(novoProduto->nome, "\n");

    if (strlen(novoProduto->nome) == 0) {
        gotoxy(5, 6);
        printf("Nome do produto nao pode ser vazio.\n");
        pressionarQualquerTeclaParaVoltar();
        free(novoProduto);
        return;
    }


    gotoxy(5, 5);
    printf("Digite a categoria do produto: ");
    fgets(novoProduto->categoria, TAMANHO_CATEGORIA, stdin);
    strtok(novoProduto->categoria, "\n");

    if (strlen(novoProduto->categoria) == 0) {
        gotoxy(5, 7);
        printf("Categoria nao pode ser vazia.\n");
        pressionarQualquerTeclaParaVoltar();
        free(novoProduto);
        return;
    }

    gotoxy(5, 6);
    printf("Digite a quantidade do produto: ");
    if (scanf("%d", &novoProduto->quantidade) != 1 || novoProduto->quantidade <= 0) {
        gotoxy(5, 8);
        printf("Quantidade invalida.\n");
        limparBufferEntrada();
        free(novoProduto);
        return;
    }
    limparBufferEntrada();


    gotoxy(5, 7);
    printf("Digite o preco do produto: ");
    if (scanf("%f", &novoProduto->preco) != 1 || novoProduto->preco < 0) {
        gotoxy(5, 9);
        printf("Preco invalido.\n");
        limparBufferEntrada();
        free(novoProduto);
        return;
    }
    limparBufferEntrada();


    gotoxy(5, 8);
    printf("Digite a data de validade (DD/MM/AAAA): ");
    fgets(novoProduto->dataValidade, TAMANHO_DATA, stdin);
    strtok(novoProduto->dataValidade, "\n");


    if (!validarData(novoProduto->dataValidade)) {
        gotoxy(5, 10);
        printf("Data de validade invalida.\n");
        pressionarQualquerTeclaParaVoltar();
        free(novoProduto);
        return;
    }

  
    produtos[numProdutos++] = novoProduto;

 
    salvarEstoque();

  
    gotoxy(5, 10);
    printf("Produto cadastrado com sucesso!\n");
}




void listarProdutos() {
    if (numProdutos == 0) {
        linha(0);
        printfCenter("PIM - LISTA DE PRODUTOS", 1);
        linha(2);
        coluna(0);
        coluna(COLUNA - 1);
        gotoxy(5, 4);
        printf("Estoque vazio.\n");
        return;
    }

    linha(0);
    printfCenter("PIM - LISTA DE PRODUTOS", 1);
    linha(2);
    coluna(0);
    coluna(COLUNA - 1);

    for (int i = 0; i < numProdutos; i++) {
        gotoxy(5, 4 + i * 6);
        printf("ID: %d - %s\n", i + 1, produtos[i]->nome);  
        gotoxy(5, 5 + i * 6);
        printf("Categoria: %s\n", produtos[i]->categoria);
        gotoxy(5, 6 + i * 6);
        printf("Quantidade: %d\n", produtos[i]->quantidade);
        gotoxy(5, 7 + i * 6);
        printf("Preco: R$ %.2f\n", produtos[i]->preco);
        gotoxy(5, 8 + i * 6);
        printf("Data de Validade: %s\n", produtos[i]->dataValidade);
        gotoxy(5, 9 + i * 6);
        printf("-------------------------------\n");
    }
}

void salvarEstoque() {
    FILE *arquivo = fopen("estoque.txt", "w");
    if (!arquivo) {
        printf("Erro ao salvar o estoque.\n");
        return;
    }

    fprintf(arquivo, "%d\n", numProdutos); 

    for (int i = 0; i < numProdutos; i++) {
        fprintf(arquivo, "%s\n", produtos[i]->nome);
        fprintf(arquivo, "%s\n", produtos[i]->categoria);
        fprintf(arquivo, "%d\n", produtos[i]->quantidade);
        fprintf(arquivo, "%.2f\n", produtos[i]->preco);
        fprintf(arquivo, "%s\n", produtos[i]->dataValidade);
    }

    fclose(arquivo);
    printf("Estoque salvo com sucesso!\n");
}



void carregarEstoque() {
    FILE *arquivo = fopen("estoque.txt", "r");  
    if (!arquivo) {
        printf("Nenhum estoque encontrado. Criando um novo.\n");
        return;
    }

    char linha[256];
    if (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%d", &numProdutos);
    }

    for (int i = 0; i < numProdutos; i++) {
        Produto *produto = (Produto *)malloc(sizeof(Produto));
        if (!produto) {
            printf("Erro de alocacao de memoria ao carregar produto.\n");
            fclose(arquivo);
            return;
        }

        fgets(produto->nome, TAMANHO_NOME, arquivo);
        strtok(produto->nome, "\n");

        fgets(produto->categoria, TAMANHO_CATEGORIA, arquivo);
        strtok(produto->categoria, "\n");

        fgets(linha, sizeof(linha), arquivo);
        sscanf(linha, "%d", &produto->quantidade);

        fgets(linha, sizeof(linha), arquivo);
        sscanf(linha, "%f", &produto->preco);

        fgets(produto->dataValidade, TAMANHO_DATA, arquivo);
        strtok(produto->dataValidade, "\n");

        produtos[i] = produto;
    }

    fclose(arquivo);
}





void limparTela() {
    system("cls"); 
}

void linha(int y) {
    for (int i = 0; i < COLUNA; i++) {
        gotoxy(i, y);
        printf("%c", 205);
    }
}

void coluna(int posicao) {
    for (int i = 0; i < LINHA; i++) {
        gotoxy(posicao, i);
        printf("%c", 186);
    }
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printfCenter(char *texto, int linha) {
    int len = strlen(texto);
    int start = (COLUNA - len) / 2;
    gotoxy(start, linha);
    printf("%s", texto);
}

void limparBufferEntrada() {
    while (getchar() != '\n');
}

void removerProduto() {
    int id;


    if (numProdutos == 0) {
        gotoxy(5, 4);
        printf("Estoque vazio.\n");
        pressionarQualquerTeclaParaVoltar();
        return;
    }

    linha(0);
    printfCenter("PIM - REMOVER PRODUTO", 1);
    linha(2);
    coluna(0);
    coluna(COLUNA - 1);


    for (int i = 0; i < numProdutos; i++) {
        gotoxy(5, 4 + i * 6);
        printf("ID: %d - %s\n", i + 1, produtos[i]->nome);  
        gotoxy(5, 5 + i * 6);
        printf("Categoria: %s\n", produtos[i]->categoria);
        gotoxy(5, 6 + i * 6);
        printf("Quantidade: %d\n", produtos[i]->quantidade);
        gotoxy(5, 7 + i * 6);
        printf("Preco: R$ %.2f\n", produtos[i]->preco);
        gotoxy(5, 8 + i * 6);
        printf("Data de Validade: %s\n", produtos[i]->dataValidade);
        gotoxy(5, 9 + i * 6);
        printf("-------------------------------\n");
    }

    gotoxy(5, 4 + numProdutos * 6);
    printf("Digite o ID do produto a ser removido: ");
    scanf("%d", &id);
    limparBufferEntrada();

    if (id < 1 || id > numProdutos) {
        gotoxy(5, 6 + numProdutos * 6);
        printf("Produto nao encontrado.\n");
        pressionarQualquerTeclaParaVoltar();
        return;
    }


    free(produtos[id - 1]);
    for (int i = id - 1; i < numProdutos - 1; i++) {
        produtos[i] = produtos[i + 1];
    }
    numProdutos--;

    salvarEstoque();
    gotoxy(5, 6 + numProdutos * 6);
    printf("Produto removido com sucesso!\n");
}


void exibirFluxoCaixa() {
    linha(0);
    printfCenter("PIM - FLUXO DE CAIXA", 1);
    linha(2);
    coluna(0);
    coluna(COLUNA - 1);

    gotoxy(5, 4);
    printf("Total de vendas: R$ %.2f\n", fluxoCaixa.totalVendas);
    gotoxy(5, 5);
    printf("Total de lucro: R$ %.2f\n", fluxoCaixa.totalLucro);
    gotoxy(5, 6);
    printf("Total de doacoes: R$ %.2f\n", fluxoCaixa.totalDoacao);

    pressionarQualquerTeclaParaVoltar();
}



void listarProdutosParaDoacao() {
    if (numProdutos == 0) {
        gotoxy(5, 4);
        printf("Nao ha produtos para doacao.\n");
        return;
    }

    linha(0);
    printfCenter("PIM - PRODUTOS PARA DOACAO", 1);
    linha(2);
    coluna(0);
    coluna(COLUNA - 1);

    for (int i = 0; i < numProdutos; i++) {
      
        if (atoi(produtos[i]->dataValidade + 6) <= 2024) {  
            gotoxy(5, 4 + i * 6);
            printf("Produto: %s\n", produtos[i]->nome);
            gotoxy(5, 5 + i * 6);
            printf("Categoria: %s\n", produtos[i]->categoria);
            gotoxy(5, 6 + i * 6);
            printf("Quantidade: %d\n", produtos[i]->quantidade);
            gotoxy(5, 7 + i * 6);
            printf("Data de Validade: %s\n", produtos[i]->dataValidade);
        }
    }

    pressionarQualquerTeclaParaVoltar();
}

void venderProduto() {
    if (numProdutos == 0) {
        gotoxy(5, 4);
        printf("Nao ha produtos no estoque.\n");
        pressionarQualquerTeclaParaVoltar();
        return;
    }

    int id, quantidade;
    char metodoPagamento;
    float valorTotal, valorComTaxa;


    listarProdutos();

 
    gotoxy(5, 4);
    printf("Digite o ID do produto a ser vendido: ");
    scanf("%d", &id);
    limparBufferEntrada();


    if (id < 1 || id > numProdutos) {
        gotoxy(5, 6);
        printf("Produto nao encontrado.\n");
        pressionarQualquerTeclaParaVoltar();
        return;
    }

  
    gotoxy(5, 6);
    printf("Digite a quantidade a ser vendida: ");
    scanf("%d", &quantidade);
    limparBufferEntrada();


    if (quantidade <= 0 || quantidade > produtos[id - 1]->quantidade) {
        gotoxy(5, 8);
        printf("Quantidade invalida!\n");
        pressionarQualquerTeclaParaVoltar();
        return;
    }


    valorTotal = produtos[id - 1]->preco * quantidade;

  
    gotoxy(5, 8);
    printf("Escolha o metodo de pagamento: \n");
    printf("[D] Dinheiro\n");
    printf("[C] Cartao\n");
    gotoxy(5, 10);
    printf("Digite a opcao: ");
    metodoPagamento = getch();  
    limparBufferEntrada();

    if (metodoPagamento == 'C' || metodoPagamento == 'c') {
     
        valorComTaxa = valorTotal * (1 + TAXA_CARTAO);
        gotoxy(5, 12);
        printf("Metodo de pagamento: Cartao\n");
        printf("Valor total: R$ %.2f\n", valorComTaxa);
        fluxoCaixa.totalVendas += valorComTaxa;
        fluxoCaixa.totalLucro += valorTotal * 0.97;  
    } else {
    
        valorComTaxa = valorTotal;
        gotoxy(5, 12);
        printf("Metodo de pagamento: Dinheiro\n");
        printf("Valor total: R$ %.2f\n", valorComTaxa);
        fluxoCaixa.totalVendas += valorComTaxa;
        fluxoCaixa.totalLucro += valorTotal; 
    }


    produtos[id - 1]->quantidade -= quantidade;

   
    fluxoCaixa.totalLucro += valorTotal;

  
    gotoxy(5, 14);
    printf("Venda realizada com sucesso!\n");

    // Atualizar o estoque no arquivo
    salvarEstoque();
}

void salvarDoacoes() {
    FILE *arquivo = fopen("doacoes.txt", "a");  
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de doações.\n");
        return;
    }

    for (int i = 0; i < numDoacoes; i++) {
        fprintf(arquivo, "%s;%s;%d\n", doacoes[i].produto, doacoes[i].destino, doacoes[i].quantidade);
    }

    fclose(arquivo);
}



void doarProdutos() {
    if (numProdutos == 0) {
        gotoxy(5, 4);
        printf("Nao ha produtos para doar.\n");
        return;
    }

    listarProdutosParaDoacao();

    int idProduto;
    gotoxy(5, 6);
    printf("Escolha o ID do produto que deseja doar (ou 0 para cancelar): ");
    scanf("%d", &idProduto);
    limparBufferEntrada();


    if (idProduto == 0) {
        gotoxy(5, 7);
        printf("Doacao cancelada.\n");
        return;
    }

    if (idProduto < 1 || idProduto > numProdutos) {
        gotoxy(5, 7);
        printf("ID invalido!\n");
        return;
    }


    Doacao doacao;
    gotoxy(5, 8);
    printf("Digite o destino da doacao: ");
    limparBufferEntrada();
    fgets(doacao.destino, sizeof(doacao.destino), stdin);
    strtok(doacao.destino, "\n");


    doacoes[numDoacoes].quantidade = 1;  
    strcpy(doacoes[numDoacoes].produto, produtos[idProduto - 1]->nome);
    strcpy(doacoes[numDoacoes].destino, doacao.destino);
    numDoacoes++;

    
    produtos[idProduto - 1]->quantidade--;

 
    gotoxy(5, 11);
    printf("Produto '%s' doado para %s\n", 
           produtos[idProduto - 1]->nome, doacao.destino);

  
    if (produtos[idProduto - 1]->quantidade == 0) {
        removerProduto(idProduto - 1);
    }

 
    salvarDoacoes();

 
    salvarEstoque();
}
int validarData(const char *data) {
    int dia, mes, ano;


    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) {
        return 0; 
    }

  
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900) {
        return 0; 
    }

  
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
        return 0; 
    }
    if (mes == 2) {
        int bissexto = (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));
        if (dia > (bissexto ? 29 : 28)) {
            return 0; 
        }
    }

    return 1; 
}

void verificarProdutosCarregados() {
    for (int i = 0; i < numProdutos; i++) {
        if (strlen(produtos[i]->nome) == 0 || strlen(produtos[i]->categoria) == 0 || 
            produtos[i]->quantidade <= 0 || produtos[i]->preco < 0 ||
            !validarData(produtos[i]->dataValidade)) {
            printf("Produto invalido encontrado no arquivo e sera ignorado.\n");
            free(produtos[i]);
            for (int j = i; j < numProdutos - 1; j++) {
                produtos[j] = produtos[j + 1];
            }
            numProdutos--;
            i--;  
        }
    }
}
