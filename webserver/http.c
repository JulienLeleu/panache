#include "http.h"


int verif(char * buf) {
	char * s = " ";
	char *tmp;
	char * token;
	int i = 1;
	
	tmp = alloca(strlen(buf)+1);
	strcpy(tmp, buf);
	
	token = strtok(tmp,s);
	
	while(token != NULL && i <= 3) {
		switch(i) {
			case 1 : if(strncmp(token,"GET",3) !=0)
					return -1;
				break;
			case 2 : if(strncmp(token,"/",1) !=0)
					return -1;
				break;
			case 3 : if(strncmp(token,"HTTP/1.1",8) !=0 )
					return -1;
				break;
		}
		printf( " %s\n", token );
    		token = strtok(NULL, s);
    		i++;
	}
	return 0;
}

/*Verifie que le mot est bel est bien correct
retourne 0 quand correct et 1 quand incorrect

int verif(char * buf) { 
	if(verifGET(buf) == 0 && verifNbMots(buf) == 3) {
		return 0;
	} else {
		return -1;
	}
}

int verifNbMots(char * buf) {
	int i = 0;
	int length = strlen(buf);
	int nbMots = 0;
	while(i<length){
		if(buf[i]==' '){	
			while(buf[i] == ' ' && i < length){
				i++;
			}
		} else {
			nbMots++;
			if(nbMots == 3 && verifHTTP(buf,i) == -1) {
				return -1;
			}
			i++;
			while(buf[i] != ' ' && i < length){
				i++;
			}
		}
	}
	return nbMots;
	
}

char * recupFirstLine(char * buf){
	int i =0;
	char * line = malloc(1024);
	while(buf[i]!='\r' && buf[i+1]!='\n'){
		line[i]=buf[i];
	}
	return line;
}

int verifHTTP(char * buf, int i){
	if(buf[i] == 'H' && buf[i+1] == 'T' && buf[i+2] == 'T' && buf[i+3] == 'P' && buf[i+4] == '/' && buf[i+6] == '.'){
		if(buf[i+5] == '1' && (buf[i+7] == '1' || buf[i+7] == '0')){
			return 0;
		}
	}
	return -1;
}

int verifGET(char * buf){
	if(buf[0] == 'G' && buf[1] == 'E' && buf[2] == 'T'){
		return 0;
	}
	return -1;
}*/
