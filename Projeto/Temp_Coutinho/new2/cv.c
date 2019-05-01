#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char const *argv[]){

   int client_to_server;
   char *myfifo = "/tmp/client_to_server_fifo";

   int server_to_client;
   char *myfifo2 = "/tmp/server_to_client_fifo";

   client_to_server = open(myfifo, O_WRONLY);// ESCREVER O CLIENTE
   server_to_client = open(myfifo2, O_RDONLY); // LER O QUE O SERVER MANDA.REPARA QUE UM LÊ E OUTRO ESCREVE(NOS 2 FICHEIROS E SÃO ALTERNADOS)

   while(1){
            int n;
            pid_t pid;// saber o pid para saber que sao clientes diferente

            char str[2048];
            char str1[1024];

            while((n=read(0,str,sizeof(str)))>0){
            			  sprintf(str1,"%d",getppid());
                    write(1,"----------\n",11);
                    strcat(str1," ");
                    strcat(str1,str);
                    strcpy(str,str1);
                    write(1,"cmd message to serwer: \n",25);
		                printf("%s",str);
		                write(client_to_server, str, strlen(str)); // por causa do espaço adicionamos mais
		          		  perror("Write:"); //Very crude error check
		          		  read(server_to_client,str,strlen(str));
		          		  perror("Read:"); // Very crude error check
		                write(1,"----------\n",11);
		                write(1,str,strlen(str));
		                memset(str, 0, sizeof(str));
            	}
	}
      close(client_to_server);
      close(server_to_client);
 	  return 0;
}