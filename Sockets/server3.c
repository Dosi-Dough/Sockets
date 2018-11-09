#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define LISTENQ 500
#define SIZE 500
int open_listen(int port){
        int listenfd, optval=1;
        struct sockaddr_in serveraddr;

        listenfd = socket(AF_INET, SOCK_STREAM,0 );
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void*) &optval, sizeof(int));

        bzero( (char *) &serveraddr, sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_addr.s_addr =htonl(INADDR_ANY);
        serveraddr.sin_port =htons((unsigned short) port);

        bind(listenfd, (struct sockaddr*) &serveraddr, sizeof(serveraddr));
        listen(listenfd, LISTENQ);

        return listenfd;
}

int main(int argc, char**argv){
        int listenfd, connfd, port, clientlen;
        struct sockaddr_in clientaddr;
        char *confirm = "from server";
        char buf[SIZE];
        port = atoi( argv[1]);
        listenfd =open_listen(port);
	if(listenfd < 0){
		printf("Error: could not open server socket \n");
	}
	
        bzero((char*)buf, sizeof(buf));
//      connfd =accept(listenfd, ...;
        while(1){
                clientlen = sizeof(clientaddr);
                connfd = accept(listenfd, (struct sockaddr*) &clientaddr, &clientlen);
		if(connfd < 0){
			printf("Error: accept failed \n");
		}
                read(connfd, buf, SIZE);
                fputs(buf, stdout);
                write(connfd, buf, strlen(buf));
                write(connfd, confirm, strlen(confirm));
        }
        close(connfd);
        return 0;
}

