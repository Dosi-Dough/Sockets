#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#define SIZE 500


struct addrinfo hints;
struct sockaddr_in * dnsaccess(char *hostname){
        hints.ai_family = AF_INET;
        struct addrinfo *result;
        getaddrinfo(hostname, NULL, &hints, &result);
        struct sockaddr_in *address = (struct sockaddr_in *)result->ai_addr;

        return address;
}

int main(){
  
  //initialize socket descritors, port var, and client length var
  int listenfd, connfd, port, clientlen;
  //initialize host entity struct
  struct hostent *hp;
  struct sockaddr_in serveraddr
  //initialize host address pointer
  char *haddrp;
  
  //convert string input of port # to int
  port = atoi(argv[1]);
  
  //calls the listen function, which listens for a connect function
  // and returns a socket descriptor if the listen is valid 
  listenfd = listen(port);

  while(1):
    clientlen = sizeof(clientaddr);
    connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
    hp = Gethostbyaddr((cosnt char *)&clientaddr.sin_addr.s_addr,
                       sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    haddrp = inet_ntoa(clientaddr.sin_addr);
    printf("server connected to %s (%s)\n", hp->h_name,haddrp);
    echo(connfd);
    Close(connfd);
  
  return 0;
}

