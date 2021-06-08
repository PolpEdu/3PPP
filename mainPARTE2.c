#include "funcsPARTE2.h"
#include "windows.h" //para a consola dar print a utf-8

int main()
{
    SetConsoleOutputCP( 65001 ); //para a consola dar print a utf-8 em windows

    struct arvore_binaria arvore;
    inicializar_arvore(&arvore);

    //getname(nomedoficheiro);
    readfileInserir("idx_fonte.bin",&arvore);
    mostrar_tudo(&arvore);


    pediraouser(&arvore, "fonte.txt");

    return 0;
}