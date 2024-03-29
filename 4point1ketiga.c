#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <string.h>

int main(int argc, char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;
	char *message,server_reply[2000];

	//Create socket
	socket_desc=socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc==-1)
	{
		printf("Could not create socket");
	}

	server.sin_addr.s_addr=inet_addr("10.1.1.85"); //Enter server address
	server.sin_family=AF_INET;
	server.sin_port=htons( 8888 );

	//Connect to remote server
	if(connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}

	puts("Connected");
	return 0;

	//Send some data
	message="connect";
	if(send(socket_desc, message, strlen(message), 0)<0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");
	
	//Receive a reply from the server
	if(recv(socket_desc, server_reply, 2000, 0)<0)
	{
		puts("Recv failed");
	}
	
	puts("Reply received\n");
	puts(server_reply);
	
	return 0;
}
