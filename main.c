#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

// Constantes
#define MAX 100

// Estrutura
typedef struct {
    char categoria[50];
    float valor;
} Despesa;

// Vari�veis globais
Despesa despesas[MAX];
int totalDespesas = 0;

// Prot�tipos das fun��es
void menu();
void gotoxy(int x, int y);
void desenharJanela();
void linhaHorizontal(int col, int lin, int colunas, char ch);
void linhaVertical(int col, int lin, int colunas, int linhas, char ch);
void textoJanela();
void limparBuffer();
void salvarDespesas();
void carregarDespesas();

// ======================= MAIN =========================
int main() {
    setlocale(LC_ALL, "");
    system("color F0");
    system("MODE con cols=91 lines=25");

    menu();

    return 0;
}

// ======================= MENU =========================
void menu() {
    int opcao, indice;
    char filtro[50];

    carregarDespesas();

    do {
        system("cls");
        desenharJanela();

        gotoxy(5,6);
        printf("------ MENU DE DESPESAS MENSAL ------");
        gotoxy(5,7);
        printf("1 - Adicionar despesa");
        gotoxy(5,8);
        printf("2 - Listar despesas");
        gotoxy(5,9);
        printf("3 - Mostrar total gasto");
        gotoxy(5,10);
        printf("4 - Excluir uma despesa");
        gotoxy(5,11);
        printf("5 - Editar uma despesa");
        gotoxy(5,12);
        printf("6 - Filtrar por categoria");
        gotoxy(5,13);
        printf("7 - Mostrar maior e menor despesa");
        gotoxy(5,14);
        printf("8 - Limpar todas as despesas");
        gotoxy(5,15);
        printf("0 - Sair");

        gotoxy(5,17);
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        system("cls");

        switch (opcao) {
            case 1:
                if (totalDespesas < MAX) {
                    printf("Digite a categoria: ");
                    fgets(despesas[totalDespesas].categoria, sizeof(despesas[totalDespesas].categoria), stdin);
                    despesas[totalDespesas].categoria[strcspn(despesas[totalDespesas].categoria, "\n")] = '\0';

                    printf("Digite o valor da despesa: R$ ");
                    scanf("%f", &despesas[totalDespesas].valor);
                    limparBuffer();

                    totalDespesas++;
                    printf("Despesa adicionada com sucesso!\n");
                    salvarDespesas();
                } else {
                    printf("Limite de despesas atingido.\n");
                }
                break;

            case 2:
                if (totalDespesas == 0) {
                    printf("Nenhuma despesa registrada.\n");
                } else {
                    printf("----- Lista de Despesas -----\n");
                    for (int i = 0; i < totalDespesas; i++) {
                        printf("%d. %s - R$ %.2f\n", i + 1, despesas[i].categoria, despesas[i].valor);
                    }
                }
                break;

            case 3: {
                float soma = 0;
                for (int i = 0; i < totalDespesas; i++) {
                    soma += despesas[i].valor;
                }
                printf("Total de despesas: R$ %.2f\n", soma);
                break;
            }

            case 4:
                printf("Digite o numero da despesa a excluir: ");
                scanf("%d", &indice);
                limparBuffer();
                if (indice >= 1 && indice <= totalDespesas) {
                    for (int i = indice - 1; i < totalDespesas - 1; i++) {
                        despesas[i] = despesas[i + 1];
                    }
                    totalDespesas--;
                    printf("Despesa exclu�da com sucesso.\n");
                    salvarDespesas();
                } else {
                    printf("�ndice inv�lido.\n");
                }
                break;

            case 5:
                printf("Digite o numero da despesa a editar: ");
                scanf("%d", &indice);
                limparBuffer();
                if (indice >= 1 && indice <= totalDespesas) {
                    printf("Nova categoria: ");
                    fgets(despesas[indice - 1].categoria, sizeof(despesas[indice - 1].categoria), stdin);
                    despesas[indice - 1].categoria[strcspn(despesas[indice - 1].categoria, "\n")] = '\0';

                    printf("Novo valor: R$ ");
                    scanf("%f", &despesas[indice - 1].valor);
                    limparBuffer();

                    printf("Despesa editada com sucesso.\n");
                    salvarDespesas();
                } else {
                    printf("�ndice inv�lido.\n");
                }
                break;

            case 6:
                printf("Digite a categoria para filtrar: ");
                fgets(filtro, sizeof(filtro), stdin);
                filtro[strcspn(filtro, "\n")] = '\0';

                printf("----- Despesas da categoria: %s -----\n", filtro);
                for (int i = 0; i < totalDespesas; i++) {
                    if (strcmp(despesas[i].categoria, filtro) == 0) {
                        printf("%d. %s - R$ %.2f\n", i + 1, despesas[i].categoria, despesas[i].valor);
                    }
                }
                break;

            case 7:
                if (totalDespesas == 0) {
                    printf("Nenhuma despesa registrada.\n");
                } else {
                    float maior = despesas[0].valor;
                    float menor = despesas[0].valor;
                    for (int i = 1; i < totalDespesas; i++) {
                        if (despesas[i].valor > maior) maior = despesas[i].valor;
                        if (despesas[i].valor < menor) menor = despesas[i].valor;
                    }
                    printf("Maior despesa: R$ %.2f\n", maior);
                    printf("Menor despesa: R$ %.2f\n", menor);
                }
                break;

            case 8:
                totalDespesas = 0;
                printf("Todas as despesas foram apagadas.\n");
                salvarDespesas();
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Op��o inv�lida.\n");
                break;
        }
        printf("\nPressione qualquer tecla para continuar...\n");
        system("pause > nul");

    } while (opcao != 0);
}

// =================== FUN��ES AUXILIARES ===================
void gotoxy(int x, int y) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) {x - 1, y - 1});
}

void linhaHorizontal(int col, int lin, int colunas, char ch) {
    gotoxy(col, lin);
    for (int i = 0; i < colunas; i++) {
        printf("%c", ch);
    }
}

void linhaVertical(int col, int lin, int colunas, int linhas, char ch) {
    for (int i = 0; i < linhas; i++) {
        gotoxy(col, lin + i);
        printf("%c", ch);
        gotoxy(colunas, lin + i);
        printf("%c", ch);
    }
}

void textoJanela() {
    gotoxy(28, 1);
    printf("ESCOLA POLIT�CNICA E DE ARTES");
    gotoxy(26, 2);
    printf("TRABALHO DE FINAL DE MODULO - ALGORITMO");
    gotoxy(35, 3);
    printf("Prof: Lucilia Ribeiro");
}

void desenharJanela() {
    int col = 1, lin = 1, colunas = 90, linhas = 24;
    char ch = '=';

    linhaHorizontal(col, lin, colunas, ch);
    linhaHorizontal(col, 4, colunas, ch);
    linhaHorizontal(col, 18, colunas, ch);
    linhaHorizontal(col, 22, colunas, ch);
    linhaHorizontal(col, 24, colunas, ch);

    linhaVertical(col, lin, colunas, linhas, '*');

    textoJanela();
}

void limparBuffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void salvarDespesas() {
    FILE *file = fopen("DESPESAS.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    for (int i = 0; i < totalDespesas; i++) {
        fprintf(file, "%s %.2f\n", despesas[i].categoria, despesas[i].valor);
    }
    fclose(file);
}

void carregarDespesas() {
    FILE *file = fopen("DESPESAS.txt", "r");
    if (file == NULL) {
        return;
    }
    while (fscanf(file, "%49s %f", despesas[totalDespesas].categoria, &despesas[totalDespesas].valor) != EOF) {
        totalDespesas++;
    }
    fclose(file);
}