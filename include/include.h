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

#define BUFFER 1000
#define PORT 80

#ifndef ADDRESS_H
#define ADDRESS_H

char *remove_http(char*, char*);
char *get_path(char*, char*);
char *remove_path(char*);

#endif // ADDRESS_H

#ifndef CONTENT_H
#define CONTENT_H

int get_content_len(char*);

#endif // CONTENT_H

#ifndef SOCKET_H
#define SOCKET_H

int socket_connect(char*, int);

#endif // SOCKET_H

#ifndef MY_CURL_H
#define MY_CURL_H

int my_curl(int, char*);

#endif

#ifndef STRING_H
#define STRING_H

char* my_strcat(char*, char*);
size_t my_strlen(char*);
int is_exec(char*);
char *my_strcpy(char*, char*);
int my_strcmp(char*, char*);
int is_digit(char);
int is_char(char);
int arg_count(char*);
int my_getchar();
void my_putstr(char*);
void my_putchar(int, char*);

#endif

