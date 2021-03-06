#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	char *hostname = "www.google.com";
	char ip[100];
	struct hostent *he;
	struct in_addr **addr_list;
	int i;

	if ((he = gethostbyname(hostname)) == NULL)
	{
		//gethostbyname failed
		herror("gethostbyname");
		return 1;
	}

	//Cast the h_addr_list to in_addr since h_addr_list alsho has the ip adress in long format only
	addr_list = (struct in_addr**) he->h_addr_list;

	for(i = 0; addr_list[i] != NULL; i++)
	{
		//Return the first one;
		strcpy(ip, inet_ntoa(*addr_list[i]));
	}

	printf("%s resolved to :%s\n", hostname, ip);
	return 0;
}
