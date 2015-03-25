#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

enum http_method {
	HTTP_GET ,
	HTTP_UNSUPPORTED ,
};
typedef struct
{
	enum http_method method ;
	int major_version ;
	int minor_version ;
	char * url ;
} http_request ;

int verif(char * buf);
void skip_headers(FILE * client);
char * fgets_or_exit(char * buf, int size, FILE * file);
int parse_http_request(const char * request_line, http_request * request);
void send_status(FILE * client, int code, const char * reason_phrase, int http_version);
void send_response(FILE * client, int code, const char * reason_phrase, const char * message_body, int http_version);
