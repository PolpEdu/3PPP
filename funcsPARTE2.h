#include "stdbool.h"

#define MAXNOME 50
#define MAXFRASELEN 400
#ifndef PPPTRABALHO3_FUNCSPARTE2_H
#define PPPTRABALHO3_FUNCSPARTE2_H

// esta estrutura serve para ser usada como modulo de leitura
// como escrevi com este tipo de estrutura vou ter que usar o mesmo tipo para ler.
typedef struct structpalreadbin {
    char pal[MAXNOME+1];
    long int bytespos; //bytes
}  strctantg;

struct no_fila {
    long int BYTEPOS;
    struct no_fila * next;
};

struct listaBYTES {
    struct no_fila * raizlista;
};

//esta struct pal vai ser um nó de uma arvore.
struct structpal {
    char pal[MAXNOME+1];
    struct listaBYTES nolistabytes; //lista de nos para as palavras depois e a seguir.
};

struct no {
    struct structpal palinfo;
    struct no *left;
    struct no *right;
};

struct arvore_binaria {
    struct no *raiz;
};

void mostrar_tudo(struct arvore_binaria *pa);

void inicializar_arvore(struct arvore_binaria *pa);

void readfileInserir(char *nome_fich2, struct arvore_binaria *pa);

void getname(char *nome_fich);

void pediraouser(struct arvore_binaria *pa, char *nometxt);

#endif //PPPTRABALHO3_FUNCSPARTE2_H
