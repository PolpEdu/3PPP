#include "stdio.h"
#include "ctype.h"
#include "structs.h"
#include "string.h"
#include "utf8lib/lib-utf8.h"

//! Get do proximo input linha da consola.
int get_one_line(FILE *fich, char *linha, int lim) {
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

void lerficheiro() {
    char nome_fich[MAXNOME + 1], nome_fich2[MAXNOME + 1] = "idx_";

    FILE *fich = NULL;
    FILE *fich2 = NULL;

    // pedir nome do ficheiro que contém os dados
    while (fich == NULL) {

        printf("\nNome do ficheiro de dados:");
        if (get_one_line(stdin, nome_fich, MAXNOME + 1) == EOF)
            return;
        fich = fopen(nome_fich, "r");
        // ? printf("%d",fich);
        if (fich == NULL) fprintf(stderr, "Ficheiro não existe\n");
    }

    strcat(nome_fich2, nome_fich); //adicionar o nome do ficheiro antigo a idx_

    fich2 = fopen(nome_fich2, "w");
    if (fich2 == NULL)
        fprintf(stderr, "Ficheiro resultados não existe\n");


    char c, cdecoded;
    char wordutf8[MAXNOME];
    char linhaaescrev[MAXNOME];

    //! Nota: nunca vou ter o nr de bytes do tamanho do ficheiro porque nunca vou contar o byte EOF no final
    int bytes = 0;

    while ((c = fgetc(fich)) != EOF) {
        //DEC-32 : espaço
        bytes += 1; //TODO: mudar isto uma palvra pode não ter só 1 byte. contar bytes por caracteres e nao por contagem.
        //letras maiusculas e minusculas
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57)) {
            //conta para uma palavra aqui.
            strtobase_u8(&cdecoded,&c); //TODO: isto passa para minuscula as maiusculas. Tirar isto.
            printf("char:%c || nr of bytes: %d\n", cdecoded, bytes);
            // printf(" %s ",c);
            strncat(wordutf8,&cdecoded,MAXNOME);

        } else {
            //Se houve separação
            if (strlen_u8(wordutf8) > 3) {
                //formato uma string para escrever.
                sprintf(linhaaescrev,"Palavra: %s, Posição: %d\n",wordutf8,bytes);
                printf("%s\n",linhaaescrev);
                fputs(linhaaescrev, fich2);
            }
            memset(wordutf8, 0, strlen_u8(wordutf8)); //! forçar a memoria da variavel para 0
            // tambem podia ter feito word [0] = "\0";
            // que dizia "que o inicio da string correspondia ao seu final" ou seja apagava-a
        }

    }

    fclose(fich);
    fclose(fich2);
}