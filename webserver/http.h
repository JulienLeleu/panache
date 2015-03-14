#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

int verif(char * buf);
int verifNbMots(char * buf);
int verifHTTP(char * buf, int indice);
int verifGET(char * buf);
