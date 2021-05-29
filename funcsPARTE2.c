#include "stdio.h"
#include "ctype.h"
#include "string.h"
#include "stdlib.h"
#include "funcsPARTE2.h"
#include "stdbool.h"


static char acentuadas[][8] =
 {"á", "Á", "à", "À", "ã", "Ã", "â", "Â", "ä", "Ä", "ç", "Ç",
         "é", "É", "è", "È", "ê", "Ê", "í", "Í", "ì", "Ì", "î", "Î",
         "ó", "Ó", "ò", "Ò", "õ", "Õ", "ô", "Ô", "ö", "Ö", "ú", "Ú",
         "ù", "Ù", "û", "Û", "\0"};
static char base[] =
        {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'c', 'c',
         'e', 'e', 'e', 'e', 'e', 'e', 'i', 'i', 'i', 'i', 'i', 'i',
         'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'u', 'u',
         'u', 'u', 'u', 'u', '\0'};

static int comp_mchar(const char *um, const char *outro) {
    int i = 0;
    while (um[i] != 0) {
        if (um[i] != outro[i])
            return 0;
        i++;
    }
    return i;
}

void strtobase_u8(char *dest, const char *orig) {
    int i = 0, j = 0, c;
    // percorrer a string origem
    c = (unsigned char) orig[0];
    while (c != 0) {
        if ((c & 0x80) == 0) {
            // é um carater ASCII, basta converter as letras para minusculas
            if (c <= 'Z' && c >= 'A')
                c = c + 'a' - 'A';
            i++;
            dest[j] = (char) c;
            j++;
        } else {
            // é um carater UTF-8 com mais de um byte
            int k = 0, tc = 0;
            while (acentuadas[k][0] != 0) {
                // se for uma das letras acentuadas, retira-se o acento
                if ((tc = comp_mchar(&acentuadas[k][0], &orig[i])) != 0) {
                    // encontramos uma minúscula acentuada
                    dest[j] = base[k];
                    j++;
                    i = i + tc;
                    break;
                }
                k++;
            }
            if (tc == 0) {
                // não é uma letra acentuada, logo é de copiar para
                //   o destino, sem alterações, todos os carateres UTF-8
                do {
                    dest[j] = orig[i];
                    i++;
                    j++;
                } while ((orig[i] & 0xC0) == 0x80);
            }
        }
        c = (unsigned char) orig[i];
    }
    dest[j] = 0;
}



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

struct no *addtree(struct no *pr, struct no *p) {
    int cond;
    char nome1[MAXNOME+1],nome2[MAXNOME+1];
    if (pr == NULL) {
        pr = p;
    } else {
        strtobase_u8(nome1,p->palinfo.pal);
        strtobase_u8(nome2,pr->palinfo.pal);
        if ((cond = strcmp(nome1,nome2)) > 0) {
            pr->right = addtree(pr->right, p);
        } else if (cond < 0)
            pr->left = addtree(pr->left, p);
    }
    return pr;
}
// devolve NULL se não há seguinte
struct no *find_next(struct no *pr, const char *anterior, struct no *candidato) {
    if (pr == NULL) return candidato;
    char nome1[MAXNOME+1],nome2[MAXNOME+1];
    strtobase_u8(nome1,anterior);
    strtobase_u8(nome2,pr->palinfo.pal);
    if (strcmp(nome1,nome2) >= 0)
        return find_next(pr->right, anterior, candidato);
    else
        return find_next(pr->left, anterior, pr);
}

bool seguinte(struct arvore_binaria * pa, struct structpal *ppinfo) {
//struct pessoa seguinte(int *pvazio, const char nome[MAXNOME + 1]) {
    struct no *p;

    p = find_next(pa->raiz, ppinfo->pal, NULL);
    if (p == NULL) {
        return false;
    }
    *ppinfo = p->palinfo;
    return true;
}

bool colocar(struct arvore_binaria * pa, struct structpal palinfodado) {
    struct no *p;
    p = (struct no *) malloc(sizeof(struct no)); // fazer novo nó com alocação dinâmica
    if (p == NULL)
        return false;
    p->palinfo =palinfodado;
    p->left = p->right = NULL;
    pa->raiz = addtree(pa->raiz, p);
    return true;
}

void mostrar_tudo(struct arvore_binaria *pa) {
    struct structpal palinfo;
    palinfo.pal[0] = 0;
    while (seguinte(pa, &palinfo)) {
        printf("PAL:%s BYTEPOS:%d Ocorrências:%d", palinfo.pal, palinfo.bytespos, palinfo.ocorrencias);
    }
}

///MAIN LOOP:
void readfileInserir(char *nome_fich2,struct arvore_binaria * pa) {
    FILE *fich2B = NULL;

    // ? printf("\nnomefix:%s\n", nome_fich2);

    if ((fich2B = fopen(nome_fich2,"rb")) == NULL){
        fprintf(stderr, "Ficheiro resultados não existe...\n");
        return;
    }


    // fprintf(stdout, "\n\nReading.....\n");
    fseek(fich2B, 0, SEEK_END);
    int n = ftell(fich2B); //tamanho total
    printf("tam tot: %d\n",n);

    fseek(fich2B, 0, SEEK_SET);
    struct structpal noderead;
    while (ftell(fich2B)!=n ) //enquanto não estamos no final.
    {

        fread(&noderead, sizeof(struct structpal),1,fich2B);
        fprintf(stdout,"Li Nó: [%s] bytepos:[%d]\n", noderead.pal, noderead.bytespos);

        if (!colocar(pa, noderead)) {
            printf("Não há espaço para inserir\n");
            break;
        }


        memset(&noderead, 0, sizeof(noderead));
        //printf("%d", ftell(fich2B));
    }

    fclose(fich2B);
}

const char *getfileext(const char *nome) {
    //separo a string
    const char *ext = strrchr(nome, '.');
    //se não tiver extensão ou não houver ponto da return a nada
    if(!ext || ext == nome) return "";
    return ext + 1; //se sim da me a extensão
}

void getname(char *nome_fich){
    FILE *fich = NULL;
    char extension[3];
    printf("\nPor favor insere o nome do ficheiro:\n");
    // pedir nome do ficheiro que contém os dados
    while (fich == NULL) {
        if ((get_one_line(stdin, nome_fich, MAXNOME + 1) == EOF))
            break;
        if ((fich = fopen(nome_fich, "r"))== NULL)
        {
            fprintf(stderr, "Ficheiro não existe. Tenta de novo:\n");
        }
        else {
            strcpy(extension, getfileext(nome_fich));
            if (!strcmp(extension, "bin")== 0) {
                fprintf(stderr, "O ficheiro não tem o formato valido para ler neste exercício, tenta outra vez:\n");
                fich = NULL;
            }
        }
    }
    ///printf("%s",nome_fich);
}

void inicializar_arvore(struct arvore_binaria * pa) {
    pa->raiz = NULL;
}

void pediraouser(){
    //esta função vai conter o que o user pode/quer fazer
}
