#include<locale.h>
#include<stdio.h>
#include<windows.h>
#include<wincon.h>

#define MAX_COLUNAS 1000 // número máximo de colunas da matriz

void inicializacao();
void menu();
void cursor(int);
void gotoxy(int, int); // coluna, linha
void defineLinhasColunas(int *linhas, int *colunas);

void main(){
    int linhas, colunas;

    defineLinhasColunas(&linhas, &colunas);
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
    gotoxy(3, 13); printf("Número de Colunhas: "); scanf("%d", &*colunas);
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