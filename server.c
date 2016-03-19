#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
int main()
{
	int sfp, nfp;
	struct sockaddr_in s_add, c_add;
	int sin_size;
	unsigned short portnum = 8889;
	printf("Hello, this is the server!\n");
	sfp = socket(AF_INET, SOCK_STREAM, 0);
	if (sfp == -1)
	{
		printf("socket fail!\n");
		return -1;
	}
	printf("socket ok!\n");
	
	bzero(&s_add, sizeof(struct sockaddr_in));
	s_add.sin_family = AF_INET;
	s_add.sin_addr.s_addr = htonl(INADDR_ANY);
	s_add.sin_port = htons(portnum);

	if (bind(sfp, (struct sockaddr*)(&s_add),sizeof(struct sockaddr)) == -1)	{
		printf("bind fail!\n");
		return -1;
	}
	printf("bind ok!\n");
	
	if(listen(sfp,5) == -1)
	{
		printf("listen fail!\n");
		return -1;
	}
	printf("listen ok!\n");
	char buffer[100];
	int len;
	while (1)
	{
		sin_size = sizeof(struct sockaddr_in);
		nfp = accept(sfp, (struct sockaddr*)(&c_add), &sin_size);
		if (nfp == -1)
		{
			printf("accept fail!\n");
			return -1;
		}
		printf("accept ok!\n");
		printf("Server get connect from %#x: %#x\n", ntohl(c_add.sin_addr.s_addr), ntohs(c_add.sin_port));
		len = recv(nfp, buffer, sizeof(buffer),0);
		buffer[len] = '\0';
		fprintf(stdout, buffer);
		fprintf(stdout, "\n");
		if (write(nfp, "hello,welcome to my server\n", 32) == -1)
		{
			printf("write fail!\n");
			return -1;
		}
		printf("write ok!\n");
		close(nfp);
	}
	close(sfp);
	return 0;
} 
