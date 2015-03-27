#include "http.h"

int parse_http_request(const char * request_line, http_request * request) {
	char * sp = " ";
	char * token;
	int nbMots = 0;
	char * tmp;
	char ** res = NULL;
	
	tmp = alloca(strlen(request_line)+1);
	strcpy(tmp, request_line);
	
	request->method = HTTP_GET;	
	request->url = NULL;
	
	token = strtok(tmp, sp);
	
	while(token) {
		nbMots++;
		res = realloc(res, sizeof(char*) * nbMots);
		if (res == NULL)
		{
			return -1;
		}
		res[nbMots - 1] = token;
		token = strtok(NULL, sp);
	}
	
	if (nbMots != 3 || strcmp("GET", res[0]) != 0 || (strncmp("HTTP/1.0", res[2], 8) != 0 && strncmp("HTTP/1.1", res[2], 8) != 0)) {
		printf(" %s\n", request_line);
		request->method = HTTP_UNSUPPORTED;
		free(res);
		return 0;
	}
	
	request->major_version = 1;
	
	if (strncmp("HTTP/1.0", res[2], 8) == 0) {
		request->minor_version = 0;
	} else if (strncmp("HTTP/1.1", res[2], 8) == 0) {
		request->minor_version = 1;
	}
	
	request->url = malloc(strlen(res[1])+1);
	strcpy(request->url, res[1]);
	
	free(res);
	return 1;
}

void skip_headers(FILE * client)
{
	char buf[256];
	while(strncmp("\r\n", fgets_or_exit(buf, sizeof(buf), client), 2) != 0)
		;
}

void send_status(FILE * client, int code, const char * reason_phrase, int http_version) {
	fprintf(client, "HTTP/1.%d %d %s\r\n", http_version, code, reason_phrase);
	if (code != 200) {
		fprintf(client, "Connection: close\r\n");
	}
}

void send_response(FILE * client, int code, const char * reason_phrase, const char * message_body, int http_version) {
	send_status(client, code, reason_phrase, http_version);
	fprintf(client, "Content-Length: %d\r\n\r\n%s\r\n", (int)strlen(message_body), message_body);
	fflush(client);
}
