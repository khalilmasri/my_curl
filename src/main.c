#include "../include/include.h"

int main(int argc, char **argv)
{
    if(argc != 2){
        printf("Usage: ./my_curl <URL>.\n");
        return 0;
    }

    char *hostname = malloc(strlen(argv[1]) + 1),
         *path = malloc(strlen(argv[1]) + 1),
         buffer[BUFFER];
    int sockfd;

    hostname = remove_http(argv[1], hostname);
    path = get_path(hostname, path);
    hostname = remove_path(hostname);

    if ((sockfd = socket_connect(hostname, PORT)) != -1){
        sprintf(buffer, "GET /%s HTTP/1.0\r\nHost: %s\r\n\r\n", path, hostname);
        my_curl(sockfd, buffer);
        close(sockfd);
    }
    free(hostname);
    free(path);

    return 0;
}
