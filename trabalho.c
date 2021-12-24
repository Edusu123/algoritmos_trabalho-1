#include<locale.h>
#include<stdio.h>
#include<windows.h>
#include<wincon.h>

#define MAX_COLUNAS 1000 // número máximo de colunas da matriz

void inicializacao();
void defineLinhasColunas(int *linhas, int *colunas);
void atribuiMatriz(int linhas, int colunas, int (*mat)[MAX_COLUNAS]);
void menu();
void cursor(int status);
void gotoxy(int x, int y); // coluna, linha

void main(){
    int linhas, colunas;

    defineLinhasColunas(&linhas, &colunas);

    int matriz[linhas][MAX_COLUNAS];

    atribuiMatriz(linhas, colunas, matriz);
}

void inicializacao(){
    system("cls");

    // prompt passa a aceitar codifição de texto com acentos
    setlocale(LC_ALL, "pt_br");

    // nome da janela do console
    SetConsoleTitle("Trabalho 1 - Eduardo Conde Pires");
    
    // define o tamanho da tela
    system("mode con:cols=110 lines=30");
}

void defineLinhasColunas(int *linhas, int *colunas){
    inicializacao();

    gotoxy(3, 10); printf("Bem-Vindo!");
    gotoxy(3, 12); printf("Número de Linhas: "); scanf("%d", &*linhas);
    gotoxy(3, 13); printf("Número de Colunas: "); scanf("%d", &*colunas);
}

void atribuiMatriz(int linhas, int colunas, int mat[][MAX_COLUNAS]){
    inicializacao();

    gotoxy(3, 10); printf("Defina os valores para cada posição da matriz!");

    int linhaCMD = 12; // define a linha que será exibida a operação

    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            
            int valor;
            
            // para o usuário, as posições da matriz começam em 1 e 1
            gotoxy(3, linhaCMD); printf("Valor [%d][%d]: ", i + 1, j + 1); scanf("%d", &valor);
            
            mat[i][j] = valor;

            linhaCMD += 1;
        }
    }
}

void menu(){
    int sair = 1;
    int pos = 10;
    
    do{
        // esconde o cursor
        cursor(0);

        gotoxy(5, 10); printf("Escolha uma das opções!");

    }while(sair);
}

void cursor(int status){
	switch (status) {
		case 0: {
			CONSOLE_CURSOR_INFO cursor = {1, FALSE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
		case 1: {
			CONSOLE_CURSOR_INFO cursor = {1, TRUE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
	}
}

void gotoxy(int x, int y)
{
    COORD c;

    c.X = x - 1;
    c.Y = y - 1;
    
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}