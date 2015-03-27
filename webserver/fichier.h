#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

char * rewrite_url(char * url);
int check_and_open(const char * url, const char * document_root);
