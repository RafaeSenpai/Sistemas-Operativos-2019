#include "API.h"

void main(){//-------------------------------------FUNCIONAL

	int n;

	char* filename = malloc(100*sizeof(char));
	char* line = malloc(100*sizeof(char));

	char* param1 = NULL;
  char* param2 = NULL;
  char* param3 = NULL;

	while(read(0,filename,1024)){

		if(strcmp(filename, "quit\n") == 0) break;

		strtok(filename, "\n");
		int fd = open(filename, O_RDONLY, 0777);

		printf("LOADING...\n");

		while((n = readLine(fd, line, 1024)) > 0) menuComandosMA(line);

		printf("LOADED\n");
	}

	printf("LOADED ALL\n");

	free(filename);
	free(line);
	free(param1);
	free(param2);
	free(param3);
}