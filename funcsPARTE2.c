#include "stdio.h"
#include "ctype.h"
#include "string.h"
#include "stdlib.h"
#include "funcsPARTE2.h"
#include "stdbool.h"

bool colocar_lista(struct listaBYTES *pf, long int numero);
struct no *addtree(struct no *pr, struct no *p, long int bytes);
bool colocar(struct arvore_binaria *pa, struct structpalreadbin palinfodado);
struct no *find_next(struct no *pr, const char *anterior, struct no *candidato);
bool seguinte(struct arvore_binaria *pa, struct structpal *ppinfo);
struct no *find(struct no *pr, char *pn);
void mostrar_tudo(struct arvore_binaria *pa);


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

char *fgets_c_u8(char *s, int count, FILE *stream) {
    int i, c, restante;
    i = 0;
    for (restante = count; restante > 0 && (c = getc(stream)) != EOF && c != '\n'; restante--) {
        s[i++] = (char) c;
        if ((c & 0xF8) == 0xF0) {
            // este é o carater inicial de uma sequência de 4 bytes
            s[i++] = (char) getc(stream);
            s[i++] = (char) getc(stream);
            s[i++] = (char) getc(stream);
        } else if ((c & 0xF0) == 0xE0) {
            // este é o carater inicial de uma sequência de 3 bytes
            s[i++] = (char) getc(stream);
            s[i++] = (char) getc(stream);
        } else if ((c & 0xE0) == 0xC0) {
            // este é o carater inicial de uma sequência de 2 bytes
            s[i++] = (char) getc(stream);
        }
    }
    if (c == '\n') {
        s[i] = (char) c;
        ++i;
    }
    if (c == EOF && (restante == count))
        return NULL;
    else {
        s[i] = '\0';
        return s;
    }
}

int numerodebytesnumchar(unsigned char val) {
    //o primeiro byte de uma char utf-8 diz quantos bytes há na palavra.
    if(val == '\n') return 2; //adicionar esta exceção
    else if (val < 128) {
        return 1;
    } else if (val < 224) {
        return 2;
    } else if (val < 240) {
        return 3;
    } else {
        return 4;
    }
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

void inicializar_arvore(struct arvore_binaria *pa) {
    pa->raiz = NULL;
}

const char *getfileext(const char *nome) {
    //separo a string
    const char *ext = strrchr(nome, '.');
    //se não tiver extensão ou não houver ponto da return a nada
    if (!ext || ext == nome) return "";
    return ext + 1; //se sim da me a extensão
}

void getname(char *nome_fich) {
    FILE *fich = NULL;
    char extension[3];
    printf("\nPor favor insere o nome do ficheiro:\n");
    // pedir nome do ficheiro que contém os dados
    while (fich == NULL) {
        if ((get_one_line(stdin, nome_fich, MAXNOME + 1) == EOF))
            break;
        if ((fich = fopen(nome_fich, "r")) == NULL) {
            fprintf(stderr, "Ficheiro não existe. Tenta de novo:\n");
        } else {
            strcpy(extension, getfileext(nome_fich));
            if (!strcmp(extension, "bin") == 0) {
                fprintf(stderr, "O ficheiro não tem o formato valido para ler neste exercício, tenta outra vez:\n");
                fich = NULL;
            }
        }
    }
    ///printf("%s",nome_fich);
}

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

bool colocar_lista(struct listaBYTES *pf, long int numero) {
    struct no_fila *aux, *prox;

    //Obter espaço para um novo nó
    aux = (struct no_fila *) malloc(sizeof(struct no_fila)*2);
    if (aux == NULL)
        //não há espaço
        return false;

    //construir novo nó da filai

    aux->BYTEPOS = numero;
    aux->next = NULL;

    //Procurar a posição onde a mensagem deve ficar
    prox = pf->raizlista;
    if (pf->raizlista == NULL) {
        // fila vazia, é a primeira mensagem
        pf->raizlista = aux;
    } else {
        while (prox->next != NULL) {
            prox = prox->next;
        }
        prox->next = aux;
    }

    return true;
}

struct no *addtree(struct no *pr, struct no *p, long int bytes) {
    int cond;
    char nome1[MAXNOME + 1], nome2[MAXNOME + 1];
    if (pr == NULL) {
        pr = p;
        colocar_lista(&pr->palinfo.nolistabytes, bytes);

    } else {
        strtobase_u8(nome1, p->palinfo.pal);
        strtobase_u8(nome2, pr->palinfo.pal);

        if ((cond = strcmp(nome1, nome2)) > 0) {
            pr->right = addtree(pr->right, p, bytes);
        } else if (cond < 0){
            pr->left = addtree(pr->left, p, bytes);
        }
        else {
            colocar_lista(&pr->palinfo.nolistabytes, bytes);
        }
    }
    return pr;
}

bool colocar(struct arvore_binaria *pa, strctantg palinfodado) {
    struct no *p;

    p = (struct no *) malloc(sizeof(struct no)); // fazer novo nó com alocação dinâmica
    if (p == NULL)
        return false;

    strcpy(p->palinfo.pal, palinfodado.pal);
    p->left = p->right = NULL;
    pa->raiz = addtree(pa->raiz, p, palinfodado.bytespos);
    return true;
}

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

bool seguinte(struct arvore_binaria *pa, struct structpal *ppinfo) {
//struct pessoa seguinte(int *pvazio, const char nome[MAXNOME + 1]) {
    struct no *p;

    p = find_next(pa->raiz, ppinfo->pal, NULL);
    if (p == NULL) {
        return false;
    }
    *ppinfo = p->palinfo;
    return true;
}

struct no *find(struct no *pr, char *pn) {
    int cond;
    if (pr == NULL)
        return NULL;
    char nome1[MAXNOME+1], nome2[MAXNOME+1];
    strtobase_u8(nome1, pr->palinfo.pal);
    strtobase_u8(nome2, pn);
    if ((cond = strcmp(nome1, nome2)) == 0)
        return pr;
    else if (cond > 0)
        return find(pr->left, pn);
    return find(pr->right, pn);
}

void mostrar_tudo(struct arvore_binaria *pa) {
    struct structpal palBytes;
    struct no *p;
    struct no_fila *aux;
    palBytes.pal[0] = 0;
    while (seguinte(pa, &palBytes)) {
        printf("PAL:%s\n", palBytes.pal);
        p = find(pa->raiz, palBytes.pal);

        aux = p->palinfo.nolistabytes.raizlista;
        printf("%ld\n", aux->BYTEPOS);
        while(aux->next != NULL){
            aux = aux->next;
            printf("%ld\n", aux->BYTEPOS);

        }
    }
}


///MAIN LOOP:
void readfileInserir(char *nome_fich2, struct arvore_binaria *pa) {
    FILE *fich2B = NULL;
    // ? printf("\nnomefix:%s\n", nome_fich2);
    if ((fich2B = fopen(nome_fich2, "rb")) == NULL) {
        fprintf(stderr, "Ficheiro resultados não existe...\n");
        return;
    }

    // fprintf(stdout, "\n\nReading.....\n");
    fseek(fich2B, 0, SEEK_END);
    int n = ftell(fich2B); //tamanho total
    // printf("tam tot: %d\n", n);

    fseek(fich2B, 0, SEEK_SET);
    struct structpalreadbin nolido;
    while (ftell(fich2B) != n) //enquanto não estamos no final.
    {
        fread(&nolido, sizeof(struct structpalreadbin), 1, fich2B);
        fprintf(stdout, "Li Nó: [%s] bytepos: [%ld]\n", nolido.pal, nolido.bytespos);


        if (!colocar(pa, nolido)) {
            printf("Não há espaço para inserir\n");
            break;
        }


        memset(&nolido, 0, sizeof(nolido));
        //printf("%d", ftell(fich2B));
    }

    fclose(fich2B);
}

int checkpontofinal(char c) {
    char sep[36] = ".\n";
    for (int j = 0; j < 34; ++j) {
        if (sep[j] == c)
        {
            // ? fprintf(stdout, "hey found [%c]\n",c);
            return 1;
        }
    }
    return 0;
}

void printdecrescentelista(struct no_fila *aux,FILE *fich) {
    /* aqui dou print ao contrario visto que a lista esta por ordem crescente de aparecimento de palavras.*/
    if (aux == NULL)
    return;

    printdecrescentelista(aux->next, fich);



    char c;
    int bytes = 0, currentbytes = 0;
    char palavra[MAXNOME+1] = "";

    /// falta ver se a posição dos bytes da palavra está no contexto
    while (fgets_c_u8(&c,1,fich) != NULL) {
        currentbytes = numerodebytesnumchar((unsigned char)c);
        // ? printf("CHAR- %c  BYTES- %d",c,currentbytes);
        bytes += currentbytes;

        if (checkpontofinal(c)){
            //SE C FOR UM PONTO FINAL NO FICHEIRO LIDO ESTAMOS NA PRESENÇA DE UMA FRASE
            //printf("%d", strlen_u8(palavra));

            //todo: STUFF QUE AINDA NAO SEI BEM AO CERTO O Q
            //TODO: Se currentbytes for maior que aux->BYTEPOS estou antes. aux->BYTEPOS maior quer dizer q estou depois


        }
        else {
            strcat(palavra, &c);
            // ? fprintf(stdout, "pal:[%s] bytes:[%d] len %d\n",palavra,bytes,strlen_u8(palavra));
        }
    }

    printf("%ld ",aux->BYTEPOS);
}

void pediraouser(struct arvore_binaria *pa, char *nometxt) {
    //esta função vai conter o que o user pode/quer fazer
    char escrito[MAXNOME+1], palavraescolhida[MAXNOME+1], Bytes[MAXNOME+1];
    struct no *encontrado;

    FILE *fich = NULL;
    //Abrir um ficheiro para ler do contexto.
    char extension[3];
    if ((fich = fopen(nometxt, "r")) == NULL) {
        fprintf(stderr, "Ficheiro não existe. Tenta de novo:\n");
    } else {
        strcpy(extension, getfileext(nometxt));
        if (!strcmp(extension, "txt") == 0) {
            fprintf(stderr, "O ficheiro não tem o formato valido para ser lido de modo a ver o contexto.\n");
            fich = NULL;
        }
    }


    // pedir nome do ficheiro que contém os dados
    while (palavraescolhida != NULL) {
        printf("\nEscolhe uma palavra:\n");
        if ((get_one_line(stdin, escrito, MAXNOME + 1) == EOF))
            break;
        strcpy(palavraescolhida, escrito);
        encontrado = find(pa->raiz, palavraescolhida);

        if (encontrado != NULL) {
            printf("Palavra escolhida: %s\n", encontrado->palinfo.pal);
            printf("Posições: ");

            printdecrescentelista(encontrado->palinfo.nolistabytes.raizlista, fich);
            printf("\n");
        } else {
            fprintf(stderr, "Palavra não encontrada na árvore. Tenta de novo:\n");
        }
        *palavraescolhida = '\0';
        printf("------------------");
    }
}

