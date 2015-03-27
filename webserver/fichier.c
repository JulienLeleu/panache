#include "fichier.h"

char * rewrite_url(char * url) {
	char * newUrl = "";
	int i = 0;
	
	while(url[i] != '\0' && url[i] != '?') {
		newUrl[i] = url[i];
	}
	
	return newUrl;
}

int check_and_open(const char * url, const char * document_root) {
	int fd;
	char * path;
	struct stat stats;
	
	path = malloc(strlen(url) + strlen(document_root)+1);
	
	strcpy(path,document_root);
	strcat(path,url);
	
	if(stat(path,&stats) == -1){
		perror("Stats");
		return -1;
	}
	
	if (!S_ISREG(stats.st_mode)) {
		return -1;
	}
	
	if((fd = open(path, O_RDONLY))==-1){
		perror("open");
		return -1;
	}
	return fd;
}

int get_file_size(int fd){
	struct stat s;
	if(fstat(fd,&s) == -1){
		perror("fstat");
		return -1;
	}
	return s.st_size;
}
