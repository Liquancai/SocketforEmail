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
	unsigned short portnum = 25;
	
	cfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == cfd){
		printf("socket fail!\n");
		return -1;
	}
	printf("socket ok!\n");
	
	bzero(&s_add, sizeof(struct sockaddr_in));
	s_add.sin_family = AF_INET;
	s_add.sin_addr.s_addr = inet_addr("220.181.12.15");
	s_add.sin_port = htons(portnum);
	//printf("s_addr = %#x , port:%#x\n", s_add.sin_addr.s_addr, s_add.sin_port);
	if (-1 == connect(cfd, (struct sockaddr*)(&s_add), sizeof(struct sockaddr))){
	printf("connect fail!\n");
	return -1;
	}
	printf("connect ok!\n");
	char hello1[] = "ehlo gacl\n";
	char auth2[] = "AUTH LOGIN\n";
	char username3[] = "eXVhbnFpYW55aW1pYW45NQ==\n";
	char passwd4[] = "Y2Fpc2h1OTE3MzQ2ODUy\n";
	char from5[] = "mail from:<yuanqianyimian95@163.com>\n";
	char rcpt6[] = "rcpt to:<lqc_nuaa@163.com>\n";
	char data7[] = "DATA\n";
	char from8[] = "from:<yuanqianyimian95@163.com>\n";
	char to9[] = "to:<lqc_nuaa@163.com>\n";
	char subject10[] = "subject:是我，就是我\n";
	char crtf11[] = "\n";
	char body12[] = "shiwo shiwo, wo shi shabi,shabishi wo\n";
	char end13[] = ".\n";
	char quit14[] = "quit\n";
	char MIME[] = "MIME-Version:1.0\n";	
	char type[] = "Content-Type:multipart/mixed;boundary=\"===1caishu######===\"\n\n";
	char bEncode[] = "Content-Transfer-Encoding:7bit\n\n";
	char message[] = "This is a multi-part message in MIME\n\n";
	char boundary[] = "--===1caishu######===\n";
	char atype[] = "Content-Type:text/plain;charset=\"gb2312\"\n";
	char btype[] = "Content-Type:text/plain;name=Mclient.c\n";
	char cEncode[] = "Content- Transfer-Encoding:printable\n\n";
	char fname[] = "Content-Disposition:attachment;filename=\"Mclient.c\"\n\n";
	char Encode[] = "Content-Transfer-Encoding:base64\n";
	char abody[] = "woshishabi shabishiwo";
	if ((recbytes = read(cfd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return -1;
	}
	buffer[recbytes] = '\0';
	printf("%s\n", buffer);
	send(cfd, hello1, strlen(hello1),0);
	if ((recbytes = read(cfd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return -1;
	}
	printf("hello1!\n");
	buffer[recbytes] = '\0';
	printf("%s\n", buffer);
	send(cfd, auth2, strlen(auth2),0);
	if ((recbytes = read(cfd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return -1;
	}
	printf("auth!\n");
	buffer[recbytes] = '\0';
	printf("%s\n", buffer);
	send(cfd, username3, strlen(username3),0);
	if ((recbytes = read(cfd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return -1;
	}
	printf("auth!\n");
	buffer[recbytes] = '\0';
	printf("%s\n", buffer);
	send(cfd, passwd4, strlen(passwd4),0);
	if ((recbytes = read(cfd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return -1;
	}
	printf("auth success or not!\n");
	buffer[recbytes] = '\0';
	printf("%s\n", buffer);
	send(cfd, from5, strlen(from5),0);
	if ((recbytes = read(cfd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return -1;
	}
	printf("Mailfrom!\n");
	buffer[recbytes] = '\0';
	printf("%s\n", buffer);
	send(cfd, rcpt6, strlen(rcpt6),0);
	send(cfd, data7, strlen(data7),0);
	send(cfd, from8, strlen(from8),0);
	send(cfd, to9, strlen(to9),0);
	send(cfd, subject10, strlen(subject10),0);
	send(cfd, MIME, strlen(MIME),0);
	send(cfd, type, strlen(type),0);
//	send(cfd, bEncode, strlen(bEncode),0);
//	send(cfd, message, strlen(message),0);
	send(cfd, boundary, strlen(boundary),0);
	send(cfd, atype, strlen(atype),0);
	send(cfd, cEncode, strlen(cEncode),0);
	send(cfd, body12, strlen(body12),0);
	send(cfd, boundary, strlen(boundary),0);
	send(cfd, btype, strlen(atype),0);
//	send(cfd, Encode, strlen(Encode),0);
	send(cfd, fname, strlen(fname),0);
	send(cfd, abody,  strlen(abody),0);
	send(cfd, crtf11, strlen(crtf11),0);
	send(cfd, end13, strlen(end13),0);
	if ((recbytes = read(cfd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return -1;
	}
	printf("result\n");
	buffer[recbytes] = '\0';
	printf("%s\n", buffer);
	send(cfd, quit14, strlen(quit14),0);
	//if ((recbytes = read(cfd, buffer, 1024)) == -1){
	//	printf("read data fail !\n");
	//	return -1;
	//}
	//printf("read ok!\n");
	//buffer[recbytes] = '\0';
	//printf("%s\n", buffer);
	//getchar();
	close(cfd);
	return 0;
}
	
	
