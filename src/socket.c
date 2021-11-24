#include "../include/include.h"

int socket_connect(char *hostname, int port)
{
    struct hostent *host;
    struct sockaddr_in addr;
    int sockfd;
    if ((host = gethostbyname(hostname)) == NULL)
    {
        printf("Couldn't resolve host.\n");
        return -1;
    }
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stderr, "socket() failed\n");
        return -1;
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(addr.sin_zero), 8);
    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr, "connect() failed\n");
        return -1;
    }
    return sockfd;
}
