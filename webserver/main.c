#include <string.h>
#include "socket.h"

int verif(char * buf);
int verifHTTP(char * buf, int indice);
int verifGET(char * buf);

int main()
{
/* Arnold Robbins in the LJ of February ’95 , describing RCS
if (argc > 1 && strcmp(argv[1], " - advice " ) == 0) {
	printf ("Don't Panic !\n");
	return 42;
}
	printf ("Need an advice ?\n");
	return 0;
}*/
char *buf = malloc(256);
int socket_serveur = creer_serveur(8080);
initialiser_signaux();


	while(1){
		int socket_client;
		int pid;
		FILE * file;
		traitement_signal(socket_client);
		socket_client = accept(socket_serveur,NULL,NULL);
		if((pid = fork()) == 0){
			if(socket_client == -1) {
				perror("accept");
				return -1;
			}
				file = fdopen(socket_client,"w+");
				const char *message_bienvenue = "Bonjour, bienvenue sur mon serveur\n";
				sleep(1);
				fprintf(file,"%s\r\n",message_bienvenue);
				fflush(file);
				while(1) {
					if(fgets(buf,256,file) == NULL)
						return 0;
					if(verif(buf) == 0){
						fprintf(file,"HTTP/1.1 200 OK");
					} else {
						fprintf(file,"HTTP/1.1 400 Bad Request\nConnection: close\nContent-Length: 17\n\n400 Bad request\n");
					}
				}
		}
		close(socket_client);
	}
	return 0;
}

/*Verifie que le mot est bel est bien correct
retourne 0 quand correct et 1 quand incorrect
*/
int verif(char * buf) {
	int i = 0;
	int j = 0;
	int length = strlen(buf);
	int nbMots = 1;
	if(verifGET(buf) == 0 && strcmp("\r\n",buf)) {
		while(i<length){
			if(buf[i]==' '){
				nbMots++;
				
				while(buf[i+j] == ' ' && i+j < length){
					i++;
				}
				if(nbMots == 3 && verifHTTP(buf,i) == 0){
					return 0;
				}
				j=0;
			}
			else {
				i++;
			}
		}
	}
	return 1;
}

int verifHTTP(char * buf, int i){
	if(buf[i] == 'H' && buf[i+1] == 'T' && buf[i+2] == 'T' && buf[i+3] == 'P' && buf[i+4] == '/' && buf[i+6] == '.'){
		if(buf[i+5] == '1' && (buf[i+7] == '1' || buf[i+7] == '0')){
			return 0;
		}
	}
	return 1;
}

int verifGET(char * buf){
	if(buf[0] == 'G' && buf[1] == 'E' && buf[2] == 'T'){
		return 0;
	}
	return 1;
}
