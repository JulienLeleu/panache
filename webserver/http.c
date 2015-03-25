#include "http.h"


int verif(char * buf) {
	char * s = " ";
	char * tmp;
	char * token;
	int i = 0;
	
	tmp = alloca(strlen(buf)+1);
	strcpy(tmp, buf);
	
	token = strtok(tmp,s);
	
	while(token != NULL && i < 3) {
		switch(i) {
			case 0 : if(strncmp(token,"GET",3) !=0)
					return 400;
				break;
			case 1 : if(strncmp(token,"/",strlen(token)) !=0)
					return 404;
				break;
			case 2 : if(strncmp(token,"HTTP/1.1",8) !=0 && strncmp(token,"HTTP/1.0",8) !=0)
					return 400;
				break;
		}
    		token = strtok(NULL, s);
    		i++;
	}
	if(i != 3) {
		return 400;
	}
	return 0;
}

void skip_headers(FILE * client)
{
	char buf[256];
	while(strncmp("\r\n", fgets(buf, sizeof(buf), client), 2) != 0)
		;
}
