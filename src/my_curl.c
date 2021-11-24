#include "../include/include.h"

char *get_status(char *buffer){

    int index = 9;
    char *status = malloc(sizeof(char)*(strlen(buffer)-8));

    while(buffer[index] && buffer[index] != '\r'){
        status[index-9] = buffer[index];
        index++;
    }

    status[index-9] = '\0';

    return status;
}

int check_status(char *status){
    return strcmp(status, "200 OK");
}

void write_content(char *buffer, int index, int size){

    while(index < size){
        putchar(buffer[index]);
        index++;
    }
}

int check_for_content(char *buffer, int size){

    int index = 0;

    while(buffer[index] && buffer[index] != '\r'){
        if(buffer[index] == '<' && buffer[index+1] == '!'){
            write_content(buffer, index, size);
            return 0;
        }
        index++;
    }

    return 1;
}

int read_sockfd(char *buffer, int sockfd){

    int entries = 1,
        content_len = 0,
        size;

    char *status;

    while(strlen(buffer) != 0){

        bzero(buffer, BUFFER);
        if ((size = read(sockfd, buffer, BUFFER)) > 0){
            buffer[size-1] = '\0';
        }

        if(entries == 1){
            status = get_status(buffer);
            entries = 2;
            if (check_status(status)){
                printf("%s\n", status);
                free(status);
                return 0;
            }
        }

        content_len = get_content_len(buffer);

        if(content_len == 0){
            printf("%s\n", status);
            break;
        }else if(content_len > 0){
            break;
        }
    }

    free(status);
    return content_len;
}

void write_sockfd(char *buffer, int sockfd){

    int size = 0;

    while(strlen(buffer) != 0){

        bzero(buffer, BUFFER);
        if ((size = read(sockfd, buffer, BUFFER)) > 0){
            buffer[size-1] = '\0';
        }

        if(check_for_content(buffer, size)){
            break;
        } 
    }

    while(strlen(buffer) != 0){
        bzero(buffer, BUFFER);
        if ((size = read(sockfd, buffer, BUFFER)) > 0){
            buffer[size-1] = '\0';
        }

        printf("%s", buffer);
    }
    printf("\n");
}

int my_curl(int sockfd, char *buffer){

    if (write(sockfd, buffer, strlen(buffer)) == -1)
    {
        fprintf(stderr, "write() failed\n");
        return 1;
    }

    if (read_sockfd(buffer, sockfd) > 0)
        write_sockfd(buffer, sockfd);

    return 0;
}
