#include<locale.h>
#include<stdio.h>
#include<windows.h>
#include<wincon.h>

void inicializacao();
void menu();

void main(){
    // exibição da tela inicial e outras configurações
    inicializacao();
}

void inicializacao(){
    system("cls");

    setlocale(LC_ALL, "pt_br");

    // nome da janela do console
    SetConsoleTitle("Trabalho 1 - Eduardo Conde Pires");
    
    // define o tamanho da tela
    system("mode con:cols=110 lines=30");
}

void menu(){

}