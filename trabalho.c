#include<conio.h>
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

    menu();
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
    inicializacao();

    int sair = 1;
    int pos = 10;
    unsigned char input;
    
    do{
        // esconde o cursor
        cursor(0);

        gotoxy(5, 3); printf("[ESC] Sair");
        gotoxy(20, 3); printf("[F1] Ajuda");

        gotoxy(5, 5); printf("Escolha uma das opções!");
        gotoxy(5, 10); printf("Troca linhas dos elementos");
        gotoxy(5, 11); printf("Troca colunas dos elementos");
        gotoxy(5, 12); printf("Troca de elementos das diagonais");
        gotoxy(5, 13); printf("Verificar se é uma matriz simétrica");
        gotoxy(5, 14); printf("Verificar se é um quadrado mágico");
        gotoxy(5, 15); printf("Verificar se é um quadrado latino");
        gotoxy(5, 16); printf("Verificar se é uma matriz de permutação");

        gotoxy(3, pos); printf(">"); // coloca a seta na posição

        input = getch();

        gotoxy(3, pos); printf(" "); // remove a seta da posição

        switch(input){
            case 72: // seta para cima
                if(pos == 10){
                    pos = 16; 
                    break;
                }
                pos -= 1;
                break;
            case 80: // seta para baixo
                if(pos == 16){
                    pos = 10; 
                    break;
                } 
                pos += 1;
                break;
            case ';': // F1
                gotoxy(60, 16); printf("Escolha uma opção!!");
                break;
            case 27: // esc
                system("cls");
                sair = 0;
                break;
        }

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