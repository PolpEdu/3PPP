#include "stdio.h"
#include "ctype.h"
#include "string.h"
#include "stdlib.h"
#include "funcsPARTE1.h"
#include "errno.h"
#include "stdbool.h"

#define MAXNOME 60 //ESPAÇO MAXIMO QUE UMA PALAVRA PODE OCUPAR EM QUALQUER OCASIÃO.

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

size_t strlen_u8(const char *s) {
    size_t tam = 0, i = 0;
    while (s[i] != 0) {
        if ((s[i] & 0xC0) != 0x80)
            tam++;
        i++;
    }
    return tam;
}


void readfile(char *nome_fich2) {
    FILE *fich2B = NULL;

    // ? printf("\nnomefix:%s\n", nome_fich2);

    if ((fich2B = fopen(nome_fich2,"rb")) == NULL){
        fprintf(stderr, "Ficheiro resultados não existe...\n");
        return;
    }


    // fprintf(stdout, "\n\nReading.....\n");
    fseek(fich2B, 0, SEEK_END);
    int n = ftell(fich2B); //tamanho total
    //printf("tam tot: %d\n",n);

    fseek(fich2B, 0, SEEK_SET);
    struct structpal noderead;
    while (ftell(fich2B)!=n ) //enquanto não estamos no final.
    {

        fread(&noderead, sizeof(struct structpal),1,fich2B);
        fprintf(stdout,"Li Nó: [%s] | bytepos:[%d]\n", noderead.pal, noderead.bytespos);
        memset(&noderead, 0, sizeof(noderead));
        //printf("%d", ftell(fich2B));
    }

    fclose(fich2B);
}


struct structpal createNODE(char *word, int currentbytes){
    struct structpal newnode;
    newnode.bytespos = currentbytes;
    strcpy(newnode.pal,word);

    return newnode;
}

int checkchar(char c) {
    char sep[42] = " 0123456789/()[]{}?!#$%&=+*:\\;.,-\"\'_'\r\n\0\t\v";
    for (int j = 0; j < 42; ++j) {
        if (sep[j] == c)
        {
            //fprintf(stdout, "hey found [%c]\n",c);
            return 1;
        }
    }
    return 0;
}

void writestuct(FILE *fich,char *palavra, int bytes){
    struct structpal node;

    if(strlen(palavra) > 3) { //global word lenght check
        node = createNODE(palavra, bytes);
        fwrite(&node, sizeof(struct structpal), 1,fich);
        fseek(fich, 0, SEEK_END);
        if(fwrite != 0)
            fprintf(stdout, "Escrevi NÓ: [pal:%s] | [bytepos:%ld]\n",node.pal,node.bytespos);
    }

    memset(&node, 0, sizeof(node));
    memset(palavra, 0, sizeof(palavra)); //reseting word mas nao a variavel
    // ? printf("-----------\n");
}

void lerficheiro(int argc, char *argv[], char *nome_fich2) {
    char nome_fich[MAXNOME + 1];
    char *nomefile;

    FILE *fich = NULL;

    if(argc > 1){
        if ((fich = fopen(argv[1], "r"))== NULL)
            fprintf(stderr, "Não consigo abrir o ficheiro passado como parametro.");
        else
            strcpy(nome_fich,argv[1]);
    }
    if (argc == 1 || errno) {
        printf("\nPrograma lancado em modo sem parametros\nPor favor insere o nome do ficheiro:\n");
        // pedir nome do ficheiro que contém os dados
        while (fich == NULL) {

            if (get_one_line(stdin, nome_fich, MAXNOME + 1) == EOF)
                return;
            if ((fich = fopen(nome_fich, "r"))== NULL)
                fprintf(stderr, "Ficheiro não existe. Tenta de novo:\n");
        }
    }

    //get the name of the file from the string
    nomefile = strtok(nome_fich, ".");
    // ? printf("%s",nomefile);

    //formats a new string corretamente.
    sprintf(nome_fich2,"idx_%s.bin",nomefile);
    //printf("\n%s\n", nome_fich2);


    FILE *fich2 = NULL;
    if ((fich2= fopen(nome_fich2, "wb")) == NULL)
        fprintf(stderr, "Ficheiro resultados não existe\n");

    int c;
    int soma = 0, currentbytes = 0;
    char palavra[MAXNOME+1] = "";

    bool letra=false;
    ///usar a função do stor para ver os characteres reais do utf-8
    while ((c= fgetc(fich)) != EOF) {
        //printf("CHAR- %c  BYTES- %d\n",c,currentbytes);

        if (checkchar(c) && letra){
            //tenho um espaço e o char anterior foi uma letra, meter mais chars

            writestuct(fich2,palavra,soma- strlen(palavra)); //bytes-wordsize(palavra)-1 para ser o inicio da palavra.
            letra = false;
        }
        else if (!checkchar(c)){
            char ch= (char)c;
            //strcat(palavra->letras , c);
            //printf("%c", ch);
            strncat(palavra, &ch, 1);
            //fprintf(fchegada, "%c", c);
            //printf("%c", c);
            letra = true;
        }
        soma++;
    }
    fclose(fich);
    fclose(fich2);
}