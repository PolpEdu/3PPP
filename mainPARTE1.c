#include <stdio.h>
#include "funcsPARTE1.h"
#include "windows.h" //para a consola dar print a utf-8

int main(int argc, char *argv[])
{
    char nome_fich2[MAXNOME + 1];
    SetConsoleOutputCP( 65001 ); //para a consola dar print a utf-8 em windows

    lerficheiro(argc, argv, nome_fich2);

    //Teste para ver se estou a ler bem:
    //Teste: readfile(nome_fich2);

    return 0;
}

