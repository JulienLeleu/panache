#include <string.h>
#include "socket.h"
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
					fgets(buf,256,file);
					if( buf == NULL){
						return 0;
					}
					fprintf(file,"%s\r\n",buf);
					fflush(file);
				}
		}
		close(socket_client);

		
	}
	return 0;
}
