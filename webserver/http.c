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

void skip_headers(FILE * client)
{
	char buf[256];
	while(strncmp("\r\n", fgets(buf, sizeof(buf), client), 2) != 0)
		;
}
