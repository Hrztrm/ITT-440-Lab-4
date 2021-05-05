#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	int s_client;
	struct sockaddr_in server;
	char message[2000], server_reply[5000];
	
	s_client = socket (AF_INET, SOCK_STREAM, 0);
	if (s_client == -1)
	{
	printf("Could not create socet");
	}

	server.sin_addr.s_addr = inet_addr("192.168.56.104");
	server.sin_family = AF_INET;
	server.sin_port = htons (8888);

	if(connect(s_client, (struct sockaddr *)&server, sizeof(server))< 0)
	{
		puts("Connect Error");
		return 1;
	}

	puts("Connected to server\n\n");
	while (1)
	{
		printf("Client: \t");
		fgets(message, 2000, stdin);
		send(s_client, message, strlen(message), 0);

		if(strcmp(message, ":exit\n") == 0)
		{
			close(s_client);
			printf("Disconnected from server.\n");
			exit(1);
		}
		if (recv(s_client, message, 2000, 0) < 0)
			printf("Error receving data");
		else
		{
			printf("Server: \t%s\n", message);
			bzero(message, sizeof(message));
		}
	}
	return 0;
}
