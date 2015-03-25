#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

int verif(char * buf);
int verifNbMots(char * buf);
int verifHTTP(char * buf, int indice);
char * recupFirstLine(char * buf);
int verifGET(char * buf);
