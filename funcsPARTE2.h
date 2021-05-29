#include "stdbool.h"

#define MAXNOME 50
#define MAXFRASE 350

#ifndef PPPTRABALHO3_FUNCSPARTE2_H
#define PPPTRABALHO3_FUNCSPARTE2_H


struct no_fila
{
    char FRASE[MAXFRASE];
    int BYTEPOS_PAL_IGUAL_SEGUINTE[MAXNOME]; //int para o index da palavra igual seguinte
};

struct structpal {
    char pal[MAXNOME];
    int bytespos; //bytes
    int ocorrencias;
    /// ESTA FILA VAI TER A FRASE ANTERIOR, ATUAL E POSTERIOR (CARACTER DE SEPARAÇÃO: ".")
    /// E A POSIÇÃO DOS BYTESDE PALAVRAS IGUAS
    struct no_fila no[MAXNOME]; //lista de nos para as palavras depois e a seguir.
};

struct no {
    struct structpal palinfo;
    struct no *left;
    struct no *right;
};

struct arvore_binaria {
    struct no * raiz;
};

void mostrar_tudo(struct arvore_binaria *pa);
void inicializar_arvore(struct arvore_binaria * pa);
void readfileInserir(char *nome_fich2,struct arvore_binaria * pa);
void getname(char *nome_fich);
void pediraouser();

#endif //PPPTRABALHO3_FUNCSPARTE2_H
