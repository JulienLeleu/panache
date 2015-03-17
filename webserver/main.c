#include <string.h>
#include "socket.h"
#include "http.h"

int main()
{
//char *buf = malloc(1024);
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
				const char *message_bienvenue = "Bonjour, bienvenue sur mon serveur";
				sleep(1);
				while(1) {
					/*if(fgets(buf,1024,file) != NULL) {*/
						/*if(verif(buf) == 0){*/
							fprintf(file,"HTTP/1.0 200 OK\r\nConnection: close\r\nContent-Length: %d\r\n\r\n%s\r\n",(int) strlen(message_bienvenue),message_bienvenue);
							fflush(file);
						/*} else {
							fprintf(file,"%d\n",verif(buf));
							fprintf(file,"HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: 17\r\n\r\n400 Bad request\r\n");
							fflush(file);
						}
					}*/
				}
		}
		close(socket_client);
	}
	return 0;
}
