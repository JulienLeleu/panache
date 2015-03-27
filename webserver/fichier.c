#include "fichier.h"

char * rewrite_url(char * url) {
	char * newUrl = "";
	int i = 0;
	
	while(url[i] != '\0' && url[i] != '?') {
		newUrl[i] = url[i];
	}
	
	return newUrl;
}

int check_and_open(const char * url, const char * document_root) {
	
}
