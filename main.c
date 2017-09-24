#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_PESSOAS 23
#define VAZIO -1

unsigned int hash(unsigned int, unsigned int);
int proximoEndereco(int);
FILE *abrirArquivo(const char *);
void menu();
void inserir();
void acessar();
void aguardar();
void lerNumero(int *);
void lerCaracter(char *);
void lerPalavra(char *);
void limparBuffer();

typedef struct Pessoas {
    int chave;
    char primeiroNome[30];
    int idade;
    char sexo;
} Pessoa;

Pessoa pessoas[TAMANHO_PESSOAS];

int main()
{
    // eu odeio c mais que tudo na vida
    int i = 0;
    for (; i < TAMANHO_PESSOAS; i++) {
        pessoas[i].chave = VAZIO;
    }

    FILE *arquivo = abrirArquivo("registros.txt");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de registros.");
        return -1;
    }
    menu();
    fclose(arquivo);
    return 0;
}

unsigned int hash(unsigned int chave, unsigned int primo){
    return chave % primo;
}

int proximoEndereco(int chave) {
    return (chave % 3) + 1;
}

void inserir() {
    Pessoa pessoa;
    printf("Inserindo um registro (Pessoa)\n");
    printf("Digite uma chave (numero natural unico): ");
    lerNumero(&pessoa.chave);
    printf("Digite o primeiro nome: ");
    lerPalavra(pessoa.primeiroNome);
    printf("Idade (numero natural): ");
    lerNumero(&pessoa.idade);
    printf("Sexo (M ou F): ");
    lerCaracter(&pessoa.sexo);
    printf("\nResumo\n");
    printf("Chave: %d, Nome: %s, Idade: %d, Sexo: %c\n", pessoa.chave, pessoa.primeiroNome, pessoa.idade, pessoa.sexo);
    unsigned int endereco = hash(pessoa.chave, TAMANHO_PESSOAS);
    if (pessoas[endereco].chave == VAZIO) {
        pessoas[endereco] = pessoa;
    } else {
        while (pessoas[endereco += proximoEndereco(pessoa.chave)].chave != VAZIO) {}
        pessoas[endereco] = pessoa;
    }
}

void acessar() {
    printf("Acessando um registro (Pessoa)\n");
    printf("Digite a chave: ");
    int chave;
    lerNumero(&chave);
    unsigned int endereco = hash(chave, TAMANHO_PESSOAS);
    int achou = 1; // 0 = FALSE, 1 = TRUE
    if (pessoas[endereco].chave != chave) {
        achou = 0;
        unsigned int enderecoInicial = endereco;
        while ((pessoas[endereco = (endereco + proximoEndereco(chave)) % TAMANHO_PESSOAS].chave != chave) && endereco != enderecoInicial) {}
        if (endereco != enderecoInicial) achou = 1;
    }
    if (achou) {
        printf("\nRegistro\n");
        printf("Endereco: %d, Chave: %d, Nome: %s, Idade: %d, Sexo: %c\n", endereco, pessoas[endereco].chave, pessoas[endereco].primeiroNome, pessoas[endereco].idade, pessoas[endereco].sexo);
    } else {
        printf("Nenhum registro com essa chave foi encontrado!\n");
    }
}

void menu() {
    int escolha = 0;
    while (escolha != 4) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        printf("Hashing em arquivos - Trabalho de ED II\n\n");
        printf("Menu:\n");
        printf("1. Inserir registro\n");
        printf("2. Acessar registro\n");
        printf("3. Listar todos os registros\n");
        printf("4. Sair\n");
        printf(": ");
        lerNumero(&escolha);
        printf("\n");
        switch (escolha) {
        case 1:
            inserir();
            aguardar();
            break;
        case 2:
            acessar();
            aguardar();
            break;
        case 4:
            printf("Saindo...\n");
            aguardar();
            break;
        default:
            printf("Escolha invalida!\n");
            aguardar();

        }
    }
}

FILE *abrirArquivo(const char *caminho) {
    FILE *arquivo = fopen(caminho, "r+");
    if (arquivo == NULL) {
        arquivo = fopen(caminho, "w+");
    }
    return arquivo;
}

void lerNumero(int *numero) {
    scanf("%d", numero);
    limparBuffer();
}

void lerCaracter(char *caracter) {
    scanf("%c", caracter);
    limparBuffer();
}

void lerPalavra(char *palavra) {
    scanf("%s", palavra);
    limparBuffer();
}

void limparBuffer() {
    // limpa o NEWLINE char que fica no buffer (C things)
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // odeio C
    }
}

void aguardar() {
    printf("Pressione ENTER para continuar...");
    limparBuffer();
}
