#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SIZE 500

struct addrinfo hints;
struct sockaddr_in * dnsaccess(char *hostname){
        hints.ai_family = AF_INET;
        struct addrinfo *result;
        getaddrinfo(hostname, NULL, &hints, &result);
        struct sockaddr_in *address = (struct sockaddr_in *)result->ai_addr;

	return address;
}
int client(char *hostname, int port){
	int clientfd;
	struct hostent *hp;
	struct sockaddr_in serveraddr;

	clientfd = socket(AF_INET, SOCK_STREAM, 6);
	serveraddr = *(dnsaccess(hostname));
	serveraddr.sin_port = htons(port);
	connect(clientfd,(struct sockaddr*) &serveraddr, sizeof(serveraddr));
	
	return clientfd; 
}
int main(int argc, char**argv){
	struct sockaddr_in serveraddr;
	char buf[SIZE];
	char *host = argv[1];
	int port = atoi(argv[2]);
	serveraddr = *(dnsaccess(host));
	
	char *s = inet_ntoa(serveraddr.sin_addr);
	printf("%s", s);
	int clientfd = client(host, port);
	printf("\nSocket file descriptor: %d\n", clientfd);

	while(fgets(buf, SIZE, stdin) != NULL){
		write(clientfd, buf, strlen(buf));
		bzero(buf, SIZE);
		sleep(5);
		read(clientfd,  buf, SIZE);
		fputs(buf,stdout);
	}
	close(clientfd);
	return 0;
}
