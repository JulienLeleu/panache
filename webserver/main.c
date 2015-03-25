#include <string.h>
#include "socket.h"
#include "http.h"

char * fgets_or_exit(char * buf, int size, FILE * file)
{
	if (fgets(buf, size, file) == NULL)
	{
		fclose(file);
		exit(0);
	}
	return buf;
}

int main()
{
	char *buf = malloc(1024);
	int socket_serveur = creer_serveur(8080);
	initialiser_signaux();
	const char *message_bienvenue = "Bonjour, bienvenue sur mon serveur";
	http_request request;


	while(1){
		int socket_client;
		int pid;
		int bad_request;
		FILE * client;
		traitement_signal(socket_client);
		socket_client = accept(socket_serveur,NULL,NULL);
		if((pid = fork()) == 0){
			if(socket_client == -1) {
				perror("accept");
				return -1;
			}
				client = fdopen(socket_client,"w+");
				while(1) {
					sleep(1);
					buf = fgets_or_exit(buf,1024,client);
					skip_headers(client);
					bad_request = parse_http_request(buf, &request);
					if(bad_request == 0)
						send_response(client, 400, "Bad Request", "Bad request\r\n", request.minor_version);
					else if(request.method == HTTP_UNSUPPORTED)
						send_response ( client , 405 , "Method Not Allowed" , "Method Not Allowed\r\n", request.minor_version);
					else if(strcmp(request.url, "/") == 0)
						send_response(client, 200, "OK", message_bienvenue, request.minor_version);
					else
						send_response(client, 404, "Not Found", "Not Found\r\n", request.minor_version);
				}
		}
		close(socket_client);
	}
	return 0;
}
