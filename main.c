#include <stdio.h>
#include <stdlib.h>

FILE *abrirArquivo(const char *);
void menu();
void aguardar();
void lerNumero(unsigned int *);
void limparBuffer();

int main()
{
    FILE *arquivo = abrirArquivo("registros.txt");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de registros.");
        return -1;
    }
    menu();
    fclose(arquivo);
    return 0;
}

void menu() {
    unsigned int escolha = 0;
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
            printf("Inserindo registro...\n");
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

void lerNumero(unsigned int *numero) {
    scanf("%d", numero);
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
