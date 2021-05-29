#define MAXNOME 50 //ESPAÇO MAXIMO QUE UMA PALAVRA PODE OCUPAR EM QUALQUER OCASIÃO.
#define MAXTEXT 3000
#define MAXLINHAS 1700

#ifndef INC_3PPP_FUNCS_H
#define INC_3PPP_FUNCS_H


//dar fwrite() a esta struct
struct structpal {
    char pal[50];
    int bytespos; //bytes
};

void lerficheiro(int argc, char *argv[], char *nome_fich2);
void readfile(char *nome_fich2);

#endif //INC_3PPP_FUNCS_H