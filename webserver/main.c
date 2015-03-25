#include <string.h>
#include "socket.h"
#include "http.h"

int main()
{
	char *buf = malloc(1024);
	int socket_serveur = creer_serveur(8080);
	initialiser_signaux();
	const char *message_bienvenue = "Bonjour, bienvenue sur mon serveur";


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
				while(1) {
					sleep(1);
					buf = fgets(buf,1024,file);
					if(verif(buf) == 0){
						fprintf(file,"HTTP/1.0 200 OK\r\nContent-Length: %d\r\nContent-Type: text/plain\r\n\r\n%s\r\n",(int) strlen(message_bienvenue),message_bienvenue);
						fflush(file);
					} else {
						fprintf(file,"HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: 17\r\n\r\n400 Bad request\r\n");
						fflush(file);
					}
				}
		}
		close(socket_client);
	}
	return 0;
}
