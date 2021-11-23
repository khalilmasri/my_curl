/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description: My_curl command line tool and library for transferring data with URLs 
 *
 *        Version:  1.0
 *        Created:  11/14/2021 01:38:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chris Dallat, Khalil Masree 
 *   Organization:  ELU
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define BUFFER 124

char *remove_http(char *url, char *address)
{
    int i = 0, j = 0;

    while (url[i] != '\0')
    {
        if (url[i] == 'h' && url[i + 1] == 't' && url[i + 2] == 't' && url[i + 3] == 'p' && url[i + 4] == ':')
            i = i + 7;
        else if (url[i] == 'h' && url[i + 1] == 't' && url[i + 2] == 't' && url[i + 3] == 'p' && url[i + 4] == 's' && url[i + 5] == ':')
            i = i + 8;
        else
        {
            address[j] = url[i];
            i++;
            j++;
        }
        address[j] = '\0';
    }
    return address;
}

char *get_path(char *address, char *path)
{
    int i = 0, j = 0;
    while (address[i] != '\0')
    {
        if (address[i] == '/')
        {
            i++;
            while (address[i] != '\0')
            {
                path[j] = address[i];
                i++;
                j++;
            }
            path[j] = '\0';
        }
        else
            i++;
    }
    return path;
}

char *remove_path(char *address, char *path)
{
    int i = 0;
    while (address[i] != '\0' && address[i] != '/')
        i++;
        
    address[i] = '\0';
    return address;
}

//function to for GET response from http hostname
int socket_connect(char *hostname, int port)
{
    struct hostent *host;
    struct sockaddr_in addr;
    int sockfd;
    if ((host = gethostbyname(hostname)) == NULL)
    {
        fprintf(stderr, "gethostbyname() failed\n");
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

int get_content_len(char *buffer){
    
    char content[] = "Content-Length: ";
    int index = 0, cur = 0;
    char ret[100];
    static int c = 1;

    while(buffer[index]){
        if(buffer[index] == content[cur]){
            cur++;
        }
        if(!content[cur])
            break;

        index++;
    }
    
    if(cur != strlen(content))
        return -1;

    index++;
    cur = 0;

    while(buffer[index] && buffer[index] != '\r'){
        ret[cur] = buffer[index];
        cur++;
        index++;
    }

    ret[cur] = '\0';
    return atoi(ret);

}

void print_status(char *status){

    int index = 9;
    while(status[index] && status[index] != '\r'){
        printf("%c", status[index]);
        index++;
    }

    printf("\n");
}


int main(int argc, char **argv)
{
    int i = 1, content_len = 0;
    int sockfd;
    char buffer[BUFFER];
    char status[BUFFER];
    char *hostname = malloc(strlen(argv[1]) + 1);
    char *path = malloc(strlen(argv[1]) + 1);

    hostname = remove_http(argv[1], hostname);
    path = get_path(hostname, path);
    hostname = remove_path(hostname, path);

    printf("host = %s\n", hostname);
    printf("path = %s\n", path);

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }
    if ((sockfd = socket_connect(hostname, 80)) == -1)
    {
        return 1;
    }
    sprintf(buffer, "GET /%s HTTP/1.0\r\nHost: %s\r\n\r\n", path, hostname);
    if (write(sockfd, buffer, strlen(buffer)) == -1)
    {
        fprintf(stderr, "write() failed\n");
        return 1;
    }
    while (i)
    {

        bzero(buffer, BUFFER);
        if (read(sockfd, buffer, BUFFER) == -1)
        {
            fprintf(stderr, "read() failed\n");
            return 1;
        }
        if (strlen(buffer) == 0)
        {
            break;
        }
        if(i == 1){
            strcpy(status, buffer);
            i++;
        }
            content_len = get_content_len(buffer);        
            if(content_len != -1)
                break;
    }

    if(content_len == 0){
        print_status(status);
    }
    printf("\n");
    close(sockfd);
    return 0;
}
