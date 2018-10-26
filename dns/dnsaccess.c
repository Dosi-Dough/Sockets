#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netdb.h>

void inputProcessing(){
  return;
}

int main(){
  FILE *fp;
  char domain[50];
  char address[300];
  int errCode;
  int len;
  struct addrinfo hints, *res;

  bzero(domain,50);

  memset(&hints, 0, sizeof(hints));  
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_CANONNAME;

  printf("enter the domain name you wish to look up \n");
  fgets(domain, 50, stdin);
  printf("the domain is: %s\n", domain);
  len = strlen(domain);
  domain[len-1] = '\0'; 

  errCode = getaddrinfo(domain, "http", &hints, &res);
  fprintf(stderr, "what is returned: %d\n", errCode);

  if(errCode != 0){
    printf("error\n");
    return 0;
  }
  inet_ntop(res->ai_family, res->ai_addr->sa_data, address, 300 );
  printf("%s \n", address);
  return 0;
}
