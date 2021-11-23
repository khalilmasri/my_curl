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

#ifndef ADDRESS_H
#define ADDRESS_H

char *remove_http(char*, char*);
char *get_path(char*, char*);
char *remove_path(char*, char*);

#endif // ADDRESS_H

#ifndef CONTENT_H
#define CONTENT_H

int get_content_len(char*);

#endif // CONTENT_H

#ifndef SOCKET_H
#define SOCKET_H

int socket_connect(char*, int);

#endif // SOCKET_H

