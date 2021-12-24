#include<stdio.h>
#include<windows.h>
#include<wincon.h>

void inicializacao();

void main(){
    // exibição da tela inicial e outras configurações
    inicializacao();
}

void inicializacao(){
    system("cls");

    // nome da janela do console
    SetConsoleTitle("Trabalho 1 - Eduardo Conde Pires");
    
    // define o tamanho da tela
    system("mode con:cols=110 lines=30");
}