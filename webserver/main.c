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
char *buf = malloc(50);
int nb_char;
int socket_serveur = creer_serveur(8080);


	while(1){
		int socket_client;
		int pid;
		socket_client = accept(socket_serveur,NULL,NULL);
		if((pid = fork()) == 0){
			if(socket_client == -1) {
				perror("accept");
				return -1;
			}

				const char *message_bienvenue = "Bonjour, bienvenue sur mon serveur\n";
				sleep(1);
				write(socket_client, message_bienvenue, strlen(message_bienvenue));
				while(1) {
					nb_char = read(socket_client, buf, 50);
					if( nb_char == -1){
						perror("read");
						return -1;
					}
					if( nb_char == 0){
						break;
						waitpid(-1,NULL,WNOHANG);
					}
					write(socket_client, buf, nb_char);
				}
		}
		close(socket_client);

		
	}
	return 0;
}
