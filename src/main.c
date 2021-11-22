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
#include<stdio.h> //printf
#include<string.h> //strcpy
#include<sys/socket.h>
#include<netdb.h>	//hostent
#include<arpa/inet.h>

int main(int argc , char *argv[])
{
	char *hostname = "www.google.com";
	char ip[100];
	struct hostent *he;
	struct in_addr **addr_list;
    int socket_desc;
	struct sockaddr_in server;
	char *message , server_reply[2000];
	int i;

	if ( (he = gethostbyname( argv[1] ) ) == NULL)
	{
		//gethostbyname failed
		herror("gethostbyname");
		return 1;
	}

	//Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
	addr_list = (struct in_addr **) he->h_addr_list;

	for(i = 0; addr_list[i] != NULL; i++)
	{
		//Return the first one;
		strcpy(ip , inet_ntoa(*addr_list[i]) );
	}

	printf("%s resolved to : %s\n" , hostname , ip);


    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket\n");
	}

	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	server.sin_port = htons( 8080 );

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}

	puts("Connected\n");

	//Send some data
	message = "GET / HTTP/1.1\r\n\r\n";
	if( send(socket_desc , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");

	//Receive a reply from the server
	if( recv(socket_desc, server_reply , 2000 , 0) < 0)
	{
		puts("recv failed");
	}
	puts("Reply received\n");
	puts(server_reply);

	return 0;
}
