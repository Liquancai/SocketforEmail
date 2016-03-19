#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
int main()
{
	int cfd;
	int recbytes;
	int sin_size;
	char buffer[1024] = {0};
	struct sockaddr_in s_add, c_add;
	unsigned short portnum = 8889;
	printf("Hello, this is the client\n");
	
	cfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == cfd){
		printf("socket fail!\n");
		return -1;
	}
	printf("socket ok!\n");
	
	bzero(&s_add, sizeof(struct sockaddr_in));
	s_add.sin_family = AF_INET;
	s_add.sin_addr.s_addr = inet_addr("115.28.212.73");
	s_add.sin_port = htons(portnum);
	printf("s_addr = %#x , port:%#x\n", s_add.sin_addr.s_addr, s_add.sin_port);
	if (-1 == connect(cfd, (struct sockaddr*)(&s_add), sizeof(struct sockaddr))){
	printf("connect fail!\n");
	return -1;
	}
	printf("connect ok!\n");
	char data[]="shabiiiiiii";
	send(cfd, data, strlen(data),0);
	if ((recbytes = read(cfd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return -1;
	}
	printf("read ok!\n");
	buffer[recbytes] = '\0';
	printf("%s\n", buffer);
	getchar();
	close(cfd);
	return 0;
}
	
	
