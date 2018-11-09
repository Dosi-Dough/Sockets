#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#define SIZE 500
#define PORT_STRING "35942"


struct addrinfo hints;
struct sockaddr_in * dnsaccess(char *hostname){
        hints.ai_family = AF_INET;
        struct addrinfo *result;
        getaddrinfo(hostname, NULL, &hints, &result);
        struct sockaddr_in *address = (struct sockaddr_in *)result->ai_addr;

        return address;
}

int main(int argc, char* argv[]){
  
  int listenfd, connfd, port, clientlen, backLog;
  struct hostent *hp;
  struct sockaddr_in clientaddr;
  char *haddrp;
  
  port = atoi(argv[1]);
  backLog = 0;
  listenfd = listen(port, backLog);
  if(listenfd < 0){
    printf("Error: could not open server socker\n");
  }
  clientlen = sizeof(clientaddr);
      
  while(1){
    connfd = accept(listenfd, (struct sockaddr*)&clientaddr, &clientlen);
    if(connfd < 0){
      printf("Error: accept faild\n");
    }
    
    
    hp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
                       sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    if(hp != 0 ){
      printf("Error: client address lookup failed \n");
      shutdown(connfd, SHUT_RDWR);
      continue;
    }
    haddrp = inet_ntoa(clientaddr.sin_addr);

    printf("server connected to %s (%s)\n", hp->h_name,haddrp);
    
    char buf[256];
    int ret;
    while ((ret = read(connfd,buf, sizeof(buf) - 1)) > 0){
        buf[ret] = '\0';
        printf("server received %d bytes \n", ret);
        write(connfd, buf, ret);
    }
   
    shutdown(connfd,SHUT_RDWR);
  }
  
  return 0;
}

