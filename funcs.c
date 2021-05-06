#include "stdio.h"
#include "ctype.h"
#include "structs.h"
#include "strings.h"


//! Get do proximo input linha da consola.
int get_one_line(FILE * fich, char *linha, int lim) {
    int c, i;
    i = 0;
    while (isspace(c = fgetc(fich)));
    if (c != EOF) {
        if (!iscntrl(c)) linha[i++] = c;
    } else
        return c;

    for (; i < lim - 1;) {
        c = fgetc(fich);
        if (c == EOF)
            return c;
        if (c == '\n')
            break;
        if (!iscntrl(c)) linha[i++] = c;
    }
    linha[i] = 0;
    while ((c != EOF) && (c != '\n'))
        c = fgetc(fich);
    return c;
}


void lerficheiro(){
    char nome_fich[MAXNOME + 1], nome_fich2[MAXNOME+1] = "idx_";
    const char separavel[] = " ,.:;/_'-()\n\"?!\r[]{}";
    char textolido[MAXTEXT];

    FILE * fich = NULL;
    FILE * fich2 = NULL;

    // pedir nome do ficheiro que contém os dados
    while(fich == NULL) {

        printf("\nNome do ficheiro de dados:");
        if (get_one_line(stdin,nome_fich, MAXNOME + 1) == EOF)
            return;
        fich = fopen(nome_fich, "r");
        // ? printf("%d",fich);
        if(fich==NULL) fprintf(stderr,"Ficheiro não existe\n");
    }

    strcat(nome_fich2, nome_fich); //adicionar o nome do ficheiro antigo a idx_

    fich2 = fopen(nome_fich2, "w");
    if (fich2 == NULL)
        fprintf(stderr,"Ficheiro resultados não existe\n");

    char c;
    while ((c=fgetc(fich)) != EOF) {
        //32 : espaço
        if(c==32)
        {
            printf("OLA");
        }
        else {
            printf("%c", c);
        }



        //if que vai meter na outra file.
        fputc (c, fich2);
    }

    fclose(fich);
    fclose(fich2);
}