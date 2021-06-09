#include "stdlib.h"
#include "stdio.h"
#include "ctype.h"
#include "string.h"
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
    if (val == '\n') return 2; //adicionar esta exceção
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
    struct no_fila *aux = NULL, *prox;

    //Obter espaço para um novo nó
    aux = (struct no_fila *) malloc(sizeof(struct no_fila)*MAXNOME/2);
    //printf("%d\n",aux);
    if (aux == NULL)
    {
        return false;
    }


    //construir novo nó da fila
    aux->BYTEPOS = numero;
    aux->next = NULL;

    //Procurar a posição onde a mensagem deve ficar
    prox = pf->raizlista;
    if ( pf->raizlista == NULL) {
        // fila vazia, é a primeira mensagem
        pf->raizlista = aux;

    } else {

        while (prox->next != NULL){
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
        } else if (cond < 0) {
            pr->left = addtree(pr->left, p, bytes);
        } else {
            colocar_lista(&pr->palinfo.nolistabytes, bytes);
        }
    }
    return pr;
}

bool colocar(struct arvore_binaria * pa, strctantg palinfodado) {
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
    char nome1[MAXNOME + 1], nome2[MAXNOME + 1];
    strtobase_u8(nome1, anterior);
    strtobase_u8(nome2, pr->palinfo.pal);
    if (strcmp(nome1, nome2) >= 0)
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
    char nome1[MAXNOME + 1], nome2[MAXNOME + 1];
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
        printf("PAL: %s\n", palBytes.pal);
        p = find(pa->raiz, palBytes.pal);

        aux = p->palinfo.nolistabytes.raizlista;
        printf("%ld\n", aux->BYTEPOS);
        while (aux->next != NULL) {
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


void checkcontexto(long int bytepal, char *nometxt) {
    /// loop pelo texto, encontro os pontos finais e vejo se eles estão dentro
    int bytes, currentbytes,pontosfinais[MAXNOME*2];
    char fraseant[MAXFRASELEN +1] = "";
    char frasemeio[MAXFRASELEN + 1] = "";
    char frasepos[MAXFRASELEN + 1] = "";
    char pedacotresfrases[(MAXFRASELEN+1)*3] = "";
    char c;

    //inicializar a minha array que vai conter todos os pontos finais
    for (int i = 0; i < MAXNOME*2; ++i) {
        pontosfinais[i] = 0;
    }

    FILE *fichread = NULL;
    //Abrir um ficheiro para ler do contexto.
    char extension[3];
    if ((fichread = fopen(nometxt, "r")) == NULL) {
        fprintf(stderr, "Ficheiro não existe. Tenta de novo:\n");
    } else {
        //printf("%s\n", nometxt);
        strcpy(extension, getfileext(nometxt));
        if (!(strcmp(extension, "txt") == 0)) {
            fprintf(stderr, "O ficheiro não tem o formato valido para ser lido de modo a ver o contexto.\n");
            fichread = NULL;

        }
    }

    int i =0;
    while (fgets_c_u8(&c, 1, fichread) != NULL) {
        currentbytes = numerodebytesnumchar((unsigned char) c);
        bytes += currentbytes;
        //Find pontos todos os pontos finais.
        if('.'==c){
            //printf("\n%d\n", bytes);
            pontosfinais[i] = bytes;
            i++;
        }
        //printf("%s",&c);
    }

    //tenho todos os pontos finais.
    int frasetotinicio;
    int frasetotfinal;
    //vou agora ver onde é que o byte das palavras encaixa.
    for (int j = 0; j < MAXNOME*2; ++j) {
        //printf("pf: %d\n",pontosfinais[j]);
        if(j>(sizeof(pontosfinais)/sizeof(pontosfinais[0]))){
            break;
        }
        if((pontosfinais[j-1]< bytepal) && (bytepal< pontosfinais[j])) {
            frasetotinicio = pontosfinais[j-2];
            frasetotfinal = pontosfinais [j];
        }
    }
    //segundo loop para ter a frase.
    bytes =0;
    fseek(fichread, 0, SEEK_SET); //voltar para o inicio.
    while (fgets_c_u8(&c, 1, fichread) != NULL) {
        currentbytes = numerodebytesnumchar((unsigned char) c);
        bytes += currentbytes;
        //Find pontos todos os pontos finais.
        if(bytes>frasetotinicio && frasetotfinal>=bytes){
            printf("%s",&c);
            strcat(pedacotresfrases, &c);
        }
        //printf("%s",&c);
    }
    printf("PEDAÇO:\n%s\n", pedacotresfrases);


    char *token;
    //so falta seprar o pedaço das tres frases:
    token = strtok(pedacotresfrases,".");
    while (token != NULL){
        printf("%s\n", token);
        token= strtok(NULL,".");
    }
    memset(&token, 0, sizeof(token));


    //fprintf(stdout, "Frase anterior: %s \nFrase posterior: %s\n",fraseant,frasepos);
    fclose(fichread);
}


void printdecrescentelista(struct no_fila *aux, char *nometxt) {
    /* aqui dou print ao contrario visto que a lista esta por ordem crescente de aparecimento de palavras.*/
    if (aux == NULL)
        return;

    printdecrescentelista(aux->next, nometxt);
    ///return 1 se esta no contexto, return 0 se não
    printf("Palavra encontrada em byte %ld\n", aux->BYTEPOS);

    checkcontexto(aux->BYTEPOS, nometxt);
}

void listar (struct listaBYTES pf,char *nometxt){
    struct no_fila *aux = pf.raizlista;
    while (aux != NULL) {
        printf("%d", aux->BYTEPOS);
        checkcontexto(aux->BYTEPOS, nometxt);
        aux = aux->next;
    }
}

void palavraesc(struct arvore_binaria *pa, char *nometxt) {
    char palavraescolhida[MAXNOME + 1], escritopal[MAXNOME];
    struct no *encontrado;

    while (palavraescolhida != NULL) {
        printf("\nEscolhe uma palavra:\n");
        if ((get_one_line(stdin, escritopal, MAXNOME + 1) == EOF))
            break;
        strcpy(palavraescolhida, escritopal);
        encontrado = find(pa->raiz, palavraescolhida);

        if (encontrado != NULL) {
            printf("Palavra escolhida: %s\n", encontrado->palinfo.pal);

            printf("Contexto:\n");
            printdecrescentelista(encontrado->palinfo.nolistabytes.raizlista, nometxt);
            //listar(encontrado->palinfo.nolistabytes, nometxt);
            printf("\n");
        } else {
            fprintf(stderr, "Palavra não encontrada na árvore. Tenta de novo:\n");
        }
        *palavraescolhida = '\0';
    }
}

void gamaesc(struct arvore_binaria *pa) {
    char palavraescolhida[MAXNOME + 1], escritopal[MAXNOME], gamapal[MAXNOME + 1], nomeutf8[MAXNOME + 1];
    int gamalen, encontrei;
    struct structpal palBytes;
    struct no *p;
    struct no_fila *aux;


    while (escritopal != NULL) {
        printf("\nEscolhe uma gama de letras:\n");
        if ((get_one_line(stdin, escritopal, MAXNOME + 1) == EOF))
            break;
        strcpy(palavraescolhida, escritopal);
        gamalen = strlen(palavraescolhida);

        //printf("%d",pa);
        while (seguinte(pa, &palBytes)) {
            strtobase_u8(nomeutf8, palBytes.pal);
            strncpy(gamapal, nomeutf8, gamalen);
            gamapal[gamalen] = 0; //adicionar o \0 final.
            //printf("gamnapal: %s|||palesc: %s\n", gamapal,palavraescolhida);

            p = find(pa->raiz, palBytes.pal);
            if (strcmp(gamapal, palavraescolhida) == 0) {
                encontrei = 1;
                printf("%s ", palBytes.pal);
                aux = p->palinfo.nolistabytes.raizlista;
                printf("%ld\n", aux->BYTEPOS);
                while (aux->next != NULL) {
                    aux = aux->next;
                    printf("%s ", palBytes.pal);
                    printf("%ld\n", aux->BYTEPOS);

                }
            }
        }
        if (!encontrei) fprintf(stderr, "Não consegui encontrar nenhuma palavra que favorecesse a pesquisa.");
        memset(&palBytes, 0, sizeof(palBytes));
        encontrei = 0;
    }
}

void pediraouser(struct arvore_binaria *pa, char *nometxt) {
    //esta função vai conter o que o user pode/quer fazer
    char escrito[MAXNOME + 1], opcaoescolhida[MAXNOME + 1];

    printf("Queres escolher uma gama de letras (selecionar \"gama\") ou selecionar uma palavra? (selecionar \"palavra\")\n");
    //todo: o user tambem pode querer em vez de escolher palavras, pode so querer gama de letras.
    // pedir nome do ficheiro que contém os dados
    while (opcaoescolhida != NULL) {
        if ((get_one_line(stdin, escrito, MAXNOME + 1) == EOF))
            break;
        strcpy(opcaoescolhida, escrito);
        if (opcaoescolhida != NULL) {

            if (strcoll(opcaoescolhida, "gama") == 0) {
                printf("Selecionaste, escolher gama de letras.\n");
                gamaesc(pa);
                break;
            } else if (strcoll(opcaoescolhida, "palavra") == 0) {
                printf("Selecionaste, escolher uma palavra.\n");
                palavraesc(pa, nometxt);
                break;
            } else {
                fprintf(stderr, "Opção inválida. Tenta de novo:\n");
            }
            *opcaoescolhida = '\0';
        }
    }

}

