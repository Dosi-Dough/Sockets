#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SIZE 50

struct addrinfo hints;
int main(){
        hints.ai_family = AF_INET;
        struct addrinfo *result;
        printf("Please enter host name:\n");
        char in[SIZE];
        bzero(in, SIZE);
        fflush(stdout);
        scanf("%s", in);
        printf("%\nIPv4 Address:");
        getaddrinfo(in, NULL, &hints, &result);
        struct sockaddr_in *address = (struct sockaddr_in *)result->ai_addr;
        char *s= inet_ntoa(address->sin_addr);

        printf("%s", s);
        return 0;
}
