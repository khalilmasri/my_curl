#include "../include/include.h"

int main(int argc, char **argv)
{
    int i = 0, k = 0;
    int find_content = 0;
    int sockfd;
    int content_len = 0;
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
    while (1)
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
        if (i == 0)
        {
            //can put this in another function status_check
            int j = 9;
            while (buffer[j] != '\r')
            {
                status[j - 9] = buffer[j];
                j++;
            }
            status[j - 9] = '\0';
            if (strcmp(status, "200 OK") != 0)
            {
                fprintf(stderr, "HTTP status code: %s\n", status);
                return 1;
            }
        }
        if (strcmp(status, "200 OK") == 0)
        {
            content_len = get_content_len(buffer);
            printf("content_len = %d\n", content_len);
        }
        if (content_len == 0 && strcmp(status, "200 OK") == 0)
        {
            printf("status, no content = %s\n", status);
            return 0;
        }
        if (content_len != 0 && content_len != -1 && strcmp(status, "200 OK") == 0)
        {
            // char *content = malloc(BUFFER);
            // memset(content, '\0', BUFFER);
            int j = 0;
            while (find_content == 0 && buffer[j] != '<')
            {
                j++;
            }
            find_content = 1;
            k = 0;
            while (k < content_len)
            {
                putchar(buffer[j]);
                j++;
                k++;
            }
            k++;
            if (k == content_len)
            {
                return 0;
            }
        }
        i++;
    }
    printf("\n");
    close(sockfd);
    return 0;
}
