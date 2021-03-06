#include<conio.h>
#include<locale.h>
#include<stdbool.h>
#include<stdio.h>
#include<windows.h>
#include<wincon.h>

#define MAX_COLUNAS 1000 // número máximo de colunas da matriz

void inicializacao();
void defineLinhasColunas(int *linhas, int *colunas);
void atribuiMatriz(int linhas, int colunas, int (*mat)[MAX_COLUNAS]);
void menu(int linhas, int colunas, int mat[][MAX_COLUNAS]);

void trocaDeLinhas(int linhas, int colunas, int mat[][MAX_COLUNAS]);
void trocaDeLinhasMatriz(int linhas, int colunas, int mat[][MAX_COLUNAS], int x, int y);
void trocaDeColunas(int linhas, int colunas, int mat[][MAX_COLUNAS]);
void trocaDeColunasMatriz(int linhas, int colunas, int mat[][MAX_COLUNAS], int x, int y);
void trocaDeDiagonais(int linhas, int colunas, int mat[][MAX_COLUNAS]);
void trocaDeDiagonaisMatriz(int linhas, int mat[][MAX_COLUNAS]);
void verificaSimetrica(int linhas, int colunas, int mat[][MAX_COLUNAS]);
bool verificaSimetricaMatriz(int linhas, int mat[][MAX_COLUNAS]);
void matrizTransposta(int linhas, int mat[][MAX_COLUNAS], int tr[][MAX_COLUNAS]);
void verificaQuadradoMagico(int linhas, int colunas, int mat[][MAX_COLUNAS]);
bool verificaQuadradoMagicoMatriz(int linhas, int mat[][MAX_COLUNAS]);
void verificaQuadradoLatino(int linhas, int colunas, int mat[][MAX_COLUNAS]);
bool verificaQuadradoLatinoMatriz(int linhas, int mat[][MAX_COLUNAS]);
void verificaPermutacao(int linhas, int colunas, int mat[][MAX_COLUNAS]);
bool verificaPermutacaoMatriz(int linhas, int colunas, int mat[][MAX_COLUNAS]);

void exibeMatriz(int linhas, int colunas, int mat[][MAX_COLUNAS], int linaInicio);
void igualaMatrizes(int linhas, int colunas, int matAux[][MAX_COLUNAS], int mat[][MAX_COLUNAS]);
void cursor(int status);
void gotoxy(int x, int y); // coluna, linha

void main(){
    // prompt passa a aceitar codifição de texto com acentos
    setlocale(LC_ALL, "pt_br");
    
    // nome da janela do console
    SetConsoleTitle("Trabalho 1 - Eduardo Conde Pires");

    int linhas, colunas;

    cursor(1); // exibe o cursos
    
    defineLinhasColunas(&linhas, &colunas);

    int matriz[linhas][MAX_COLUNAS];

    atribuiMatriz(linhas, colunas, matriz);

    cursor(0); // esconde o cursor

    menu(linhas, colunas, matriz);
}

void inicializacao(){
    system("cls");
    
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

void menu(int linhas, int colunas, int mat[][MAX_COLUNAS]){
    int sair = 1;
    int pos = 10;
    unsigned char input;
    bool flagAjuda = false;
    
    do{
        inicializacao();

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

        if(flagAjuda){
            gotoxy(60, 16);
            printf("Escolha uma opção!!");
        }

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
            case 13: // enter
                if(pos == 10) trocaDeLinhas(linhas, colunas, mat);
                if(pos == 11) trocaDeColunas(linhas, colunas, mat);
                if(pos == 12) trocaDeDiagonais(linhas, colunas, mat);
                if(pos == 13) verificaSimetrica(linhas, colunas, mat);
                if(pos == 14) verificaQuadradoMagico(linhas, colunas, mat);
                if(pos == 15) verificaQuadradoLatino(linhas, colunas, mat);
                if(pos == 16) verificaPermutacao(linhas, colunas, mat);
                break;
            case ';': // F1
                flagAjuda = true;
                break;
            case 27: // esc
                system("cls");
                sair = 0;
                break;
        }

    }while(sair);
}

////////////////////////////////////////////////////////////////////

void trocaDeLinhas(int linhas, int colunas, int mat[][MAX_COLUNAS]){
    inicializacao();

    int matAlterada[linhas][MAX_COLUNAS], l1 = 1, l2 = 1;

    igualaMatrizes(linhas, colunas, matAlterada, mat);

    gotoxy(5, 5); printf("Insira o índice das linhas a serem trocadas (1 - n)");

    gotoxy(5, 10); printf("Linha 1: "); scanf("%d", &l1);
    gotoxy(5, 11); printf("Linha 2: "); scanf("%d", &l2);

    trocaDeLinhasMatriz(linhas, colunas, matAlterada, l1 - 1, l2 - 1);

    inicializacao();

    gotoxy(5, 5); printf("Matriz original: ");
    exibeMatriz(linhas, colunas, mat, 7);

    gotoxy(5, 16); printf("Matriz alterada: ");
    exibeMatriz(linhas, colunas, matAlterada, 18);

    gotoxy(5, 29); system("pause");
}

void trocaDeLinhasMatriz(int linhas, int colunas, int mat[][MAX_COLUNAS], int x, int y){
    for(int i = 0; i < colunas; i++){
        int aux = mat[y][i];
        mat[y][i] = mat[x][i];
        mat[x][i] = aux;
    }
}

void trocaDeColunas(int linhas, int colunas, int mat[][MAX_COLUNAS]){
    inicializacao();

    int matAlterada[linhas][MAX_COLUNAS], c1 = 1, c2 = 1;

    igualaMatrizes(linhas, colunas, matAlterada, mat);

    gotoxy(5, 5); printf("Insira o índice das colunas a serem trocadas (1 - n)");

    gotoxy(5, 10); printf("Coluna 1: "); scanf("%d", &c1);
    gotoxy(5, 11); printf("Coluna 2: "); scanf("%d", &c2);

    trocaDeColunasMatriz(linhas, colunas, matAlterada, c1 - 1, c2 - 1);

    inicializacao();

    gotoxy(5, 5); printf("Matriz original: ");
    exibeMatriz(linhas, colunas, mat, 7);

    gotoxy(5, 16); printf("Matriz alterada: ");
    exibeMatriz(linhas, colunas, matAlterada, 18);

    gotoxy(5, 29); system("pause");
}

void trocaDeColunasMatriz(int linhas, int colunas, int mat[][MAX_COLUNAS], int x, int y){
    for(int i = 0; i < linhas; i++){
        int aux = mat[i][x];
        mat[i][x] = mat[i][y];
        mat[i][y] = aux;
    }
}

void trocaDeDiagonais(int linhas, int colunas, int mat[][MAX_COLUNAS]){
    inicializacao();

    int matAlterada[linhas][MAX_COLUNAS];

    igualaMatrizes(linhas, colunas, matAlterada, mat);

    trocaDeDiagonaisMatriz(linhas - 1, matAlterada);

    gotoxy(5, 5); printf("Matriz original: ");
    exibeMatriz(linhas, colunas, mat, 7);

    gotoxy(5, 16); printf("Matriz alterada: ");
    exibeMatriz(linhas, colunas, matAlterada, 18);

    gotoxy(5, 29); system("pause");
}

void trocaDeDiagonaisMatriz(int linhas, int mat[][MAX_COLUNAS]){
    for(int i = 0; i <= linhas; i++){
        int aux = mat[i][i];
        mat[i][i] = mat[i][linhas - i];
        mat[i][linhas - i] = aux;
    }
}

void verificaSimetrica(int linhas, int colunas, int mat[][MAX_COLUNAS]){
    inicializacao();

    gotoxy(5, 5); 
    if(verificaSimetricaMatriz(linhas, mat)) printf("A matriz a seguir é Simétrica!!!");
    else printf("A matriz a seguir não é simétrica...");

    exibeMatriz(linhas, colunas, mat, 10);

    gotoxy(5, 29); system("pause");
}

bool verificaSimetricaMatriz(int linhas, int mat[][MAX_COLUNAS]){
    int tr[linhas][MAX_COLUNAS];

    matrizTransposta(linhas, mat, tr);

    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < linhas; j++){
            if(mat[i][j] != tr[i][j]) return false;
        }
    }

    return true;
}

void matrizTransposta(int linhas, int mat[][MAX_COLUNAS], int tr[][MAX_COLUNAS]){
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < linhas; j++){
            tr[i][j] = mat[j][i];
        }
    }
}

void verificaQuadradoMagico(int linhas, int colunas, int mat[][MAX_COLUNAS]){
    inicializacao();

    gotoxy(5, 5);
    if(verificaQuadradoMagicoMatriz(linhas, mat)) printf("A matriz é um Quadrado Mágico!!!");
    else printf("A matriz não é um Quadrado Mágico...");

    exibeMatriz(linhas, colunas, mat, 10);

    gotoxy(5, 29); system("pause");
}

bool verificaQuadradoMagicoMatriz(int linhas, int mat[][MAX_COLUNAS]){
    int somad1 = 0, somad2 = 0;

    for(int i = 0; i < linhas; i++){
        somad1 += mat[i][i];
        somad2 += mat[i][linhas - 1 - i];
    }

    if (somad1 != somad2) return false;

    for (int i = 0; i < linhas; i++) {
        int linhaSoma = 0, colunaSoma = 0;
    
        for (int j = 0; j < linhas; j++) {
            linhaSoma += mat[i][j];
            colunaSoma += mat[j][i];
        }

        if (linhaSoma != colunaSoma || colunaSoma != somad1) return false;
    }

    return true;
}

void verificaQuadradoLatino(int linhas, int colunas, int mat[][MAX_COLUNAS]){
    inicializacao();

    gotoxy(5, 5);
    if(verificaQuadradoLatinoMatriz(linhas, mat)) printf("A matriz é um Quadrado Latino!!!");
    else printf("A matriz não é um quadrado latino...");

    exibeMatriz(linhas, colunas, mat, 10);

    gotoxy(5, 29); system("pause");
}

bool verificaQuadradoLatinoMatriz(int linhas, int mat[][MAX_COLUNAS]){
    int i, j, k, vet[linhas];

    for(i = 0; i < linhas; i++){
        vet[i] = 0;
        for(j = 0; j < linhas; j++){
            vet[i] += mat[i][j];
            for(k = 0; k < linhas; k++){
                if(mat[i][j] == mat[i][k] && j != k) return false;
            }
        }
    }

    for(i = 0; i < linhas; i++){
        if(vet[i] != vet[i + 1]) return false;
    }

    for(j = 0; j < linhas; j++){
        vet[i] = 0;
        for(i = 0; i < linhas; i++){
            vet[j] += mat[i][j];
            for(k = 0; k < linhas; k++){
                if (mat[i][j] == mat[k][j] && i != k) return false;
            }
        }
    }

    for(i = 0; i < linhas - 1; i++){
        if(vet[i] != vet[i + 1]) return false;
    }

    return true;
}

void verificaPermutacao(int linhas, int colunas, int mat[][MAX_COLUNAS]){
    inicializacao();

    gotoxy(5, 5);
    if(verificaPermutacaoMatriz(linhas, colunas, mat)) printf("A matriz é uma Matriz de Permutação!!");
    else printf("A matriz não é uma Matriz de Permutação...");

    exibeMatriz(linhas, colunas, mat, 10);

    gotoxy(5, 29); system("pause");
}

bool verificaPermutacaoMatriz(int linhas, int colunas, int mat[][MAX_COLUNAS]){
    bool flagLinha, flagFinal = true;

    for(int i = 0; i < linhas; i++){
        flagLinha = false;
        for(int j = 0; j < colunas; j++){
            if(mat[i][j] != 0 && mat[i][j] != 1) return false;
            if(mat[i][j] == 1) flagLinha = true;
        }
        if(!flagLinha) flagFinal == false;
    }

    return flagFinal;
}

///////////////////////////////////////////////////////////////////////////////////

void exibeMatriz(int linhas, int colunas, int mat[][MAX_COLUNAS], int linhaInicio){
    int colunaInicio = 5, contadorLinha = 0, contadorColuna = 0;

    for(int i = 0; i < linhas; i++){
        int colunaDaVez = colunaInicio + contadorColuna;
        int linhaDaVez = linhaInicio + contadorLinha;
        gotoxy(colunaDaVez, linhaDaVez); printf("| ");

        int contadorValores = 3;
        for(int j = 0; j < colunas; j++){
            gotoxy(colunaDaVez + contadorValores, linhaDaVez); printf("%d", mat[i][j]);
            contadorValores += 3;
        }

        gotoxy(colunaDaVez + contadorValores, linhaDaVez); printf("|\n");

        contadorLinha += 1;
    }
}

void igualaMatrizes(int linhas, int colunas, int matAux[][MAX_COLUNAS], int mat[][MAX_COLUNAS]){
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            matAux[i][j] = mat[i][j];
        }
    }
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