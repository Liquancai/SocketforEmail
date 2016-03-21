#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define serport 8888
#define cliport 25


char buffer[1024] = {0};
char a[1024], b[1366];
int len = 0;
void sendEmail();
void base64(char *a, char *b);
int main()
{
	int serfd, accfd;
	struct sockaddr_in s_add;

	serfd = socket(AF_INET, SOCK_STREAM,0);
	if (serfd == -1){
		printf("server socket init fail!\n");
		return 0;
	}
	bzero(&s_add, sizeof(struct sockaddr_in));
	s_add.sin_family = AF_INET;
	s_add.sin_addr.s_addr = htonl(INADDR_ANY);
	s_add.sin_port = htons(serport);
	if (bind(serfd, (struct sockaddr*)&s_add, sizeof(struct sockaddr)) == -1){
		printf("server bind fail!\n");
		return 0;
	}
	if (listen(serfd,5) == -1){
		printf("server listen fail!\n");
		return 0;
	}
	while (1){
		accfd = accept(serfd, NULL, NULL);
		if (accfd == -1){
			printf("server accept fail!\n");
			return 0;
		}
		while (1){	
			len = recv(accfd, buffer, sizeof(buffer), 0);
			if (len != 0){
				buffer[len] = '\0';
				printf("%s\n", buffer);
				if (strcmp(buffer,"ex") == 0){
					sendEmail();
					break;
				}
			}
		}
		close(accfd);
	}
	close(serfd);
	return 0;
}

void sendEmail(){

	int clifd;
	struct sockaddr_in c_add;

	clifd = socket(AF_INET, SOCK_STREAM, 0);
	if (clifd == -1){
		printf("client socket fail!\n");
		return;
	}
	
	bzero(&c_add, sizeof(struct sockaddr_in));
	c_add.sin_family = AF_INET;
	c_add.sin_addr.s_addr = inet_addr("220.181.12.15");
	c_add.sin_port = htons(cliport);
	if (connect(clifd, (struct sockaddr*)(&c_add), sizeof(struct sockaddr)) == -1){
		printf("client connect fail!\n");
		return;
	}
	char hello1[] = "ehlo gacl\n";
	char auth2[] = "AUTH LOGIN\n";
//	char username3[] = "eXVhbnFpYW55aW1pYW45NQ==\n";
//	char passwd4[] = "Y2Fpc2h1OTE3MzQ2ODUy\n";
	strcpy(a, "yuanqianyimian95");
	base64(a, b);
	char username3[1366];
	strcpy(username3, b);
	
	strcpy(a, "caishu917346852");
	base64(a, b);
	char passwd4[1366];
	strcpy(passwd4, b);	
	char from5[] = "mail from:<yuanqianyimian95@163.com>\n";
	char rcpt6[] = "rcpt to:<lqc_nuaa@163.com>\n";
	char data7[] = "DATA\n";
	char from8[] = "from:<yuanqianyimian95@163.com>\n";
	char to9[] = "to:<lqc_nuaa@163.com>\n";
	char subject10[] = "subject:";
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

	strcpy(subject10+8, buffer);

	if ((len = read(clifd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return;
	}
	printf("start!\n");
	buffer[len] = '\0';
	printf("%s\n", buffer);

	send(clifd, hello1, strlen(hello1),0);
	if ((len = read(clifd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return;
	}
	printf("to hello!\n");
	buffer[len] = '\0';
	printf("%s\n", buffer);

	send(clifd, auth2, strlen(auth2),0);
	if ((len = read(clifd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return;
	}
	printf("ask username!\n");
	buffer[len] = '\0';
	printf("%s\n", buffer);

	send(clifd, username3, strlen(username3),0);
	send(clifd, crtf11, strlen(crtf11),0);
	if ((len = read(clifd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return;
	}
	printf("ask passwd!\n");
	buffer[len] = '\0';
	printf("%s\n", buffer);

	send(clifd, passwd4, strlen(passwd4),0);
	send(clifd, crtf11, strlen(crtf11),0);
	if ((len = read(clifd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return;
	}
	printf("login result!\n");
	buffer[len] = '\0';
	printf("%s\n", buffer);

	send(clifd, from5, strlen(from5),0);
	send(clifd, rcpt6, strlen(rcpt6),0);
	send(clifd, data7, strlen(data7),0);
	send(clifd, from8, strlen(from8),0);
	send(clifd, to9, strlen(to9),0);
	send(clifd, subject10, strlen(subject10),0);
	send(clifd, crtf11, strlen(crtf11),0);
	send(clifd, MIME, strlen(MIME),0);
	send(clifd, type, strlen(type),0);
//	send(clifd, bEncode, strlen(bEncode),0);
//	send(clifd, message, strlen(message),0);
	send(clifd, boundary, strlen(boundary),0);
	send(clifd, atype, strlen(atype),0);
	send(clifd, cEncode, strlen(cEncode),0);
	send(clifd, body12, strlen(body12),0);
	send(clifd, boundary, strlen(boundary),0);
	send(clifd, btype, strlen(atype),0);
//	send(clifd, Encode, strlen(Encode),0);
	send(clifd, fname, strlen(fname),0);
	send(clifd, abody,  strlen(abody),0);
	send(clifd, crtf11, strlen(crtf11),0);
	send(clifd, end13, strlen(end13),0);

	if ((len = read(clifd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return;
	}
	printf("send result!\n");
	buffer[len] = '\0';
	printf("%s\n", buffer);

	send(clifd, quit14, strlen(quit14),0);
	close(clifd);
	return;
}

void base64(char *a, char *b){
	int  c[6];
	char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int i = 0, j = 0;
	while (strlen(a)/3 > i){
	//	printf("%c %c %c\n", a[i*3], a[i*3+1], a[i*3+2]);
		c[0] = (a[i*3] & 0x80) / 128;
		c[1] = (a[i*3] & 0x40)/ 64;
		c[2] = (a[i*3] & 0x20) /32;
		c[3] = (a[i*3] & 0x10) /16;
		c[4] = (a[i*3] & 0x08) /8;	
		c[5] = (a[i*3] & 0x04) /4;
		b[j++] = base[c[0]*32 + c[1]*16 + c[2]*8 + c[3]*4 + c[4]*2 + c[5]];
		c[0] = (a[i*3] & 0x02) / 2;
		c[1] = (a[i*3] & 0x01)/ 1;
		c[2] = (a[i*3+1] & 0x80) /128;
		c[3] = (a[i*3+1] & 0x40) /64;
		c[4] = (a[i*3+1] & 0x20) /32 ;	
		c[5] = (a[i*3+1] & 0x10) /16;
		b[j++] = base[c[0]*32 + c[1]*16 + c[2]*8 + c[3]*4 + c[4]*2 + c[5]];
		c[0] = (a[i*3+1] & 0x08)/8;
		c[1] = (a[i*3+1] & 0x04)/4;
		c[2] = (a[i*3+1] & 0x02)/2;
		c[3] = a[i*3+1] & 0x01;
		c[4] = (a[i*3+2] & 0x80)/128;	
		c[5] = (a[i*3+2] & 0x40)/64;
		b[j++] = base[c[0]*32 + c[1]*16 + c[2]*8 + c[3]*4 + c[4]*2 + c[5]];
		
		c[0] = (a[i*3+2] & 0x20)/32;
		c[1] = (a[i*3+2] & 0x10)/16;
		c[2] = (a[i*3+2] & 0x08)/8;
		c[3] = (a[i*3+2] & 0x04)/4;
		c[4] = (a[i*3+2] & 0x02)/2;	
		c[5] = a[i*3+2] & 0x01;
		b[j++] = base[c[0]*32 + c[1]*16 + c[2]*8 + c[3]*4 + c[4]*2 + c[5]];
		i++;
	}
	if (a[3*i] == '\0'){
	}else if (a[3*i+1] == '\0'){	
		c[0] = (a[i*3] & 0x80) / 128;
		c[1] = (a[i*3] & 0x40)/ 64;
		c[2] = (a[i*3] & 0x20) /32;
		c[3] = (a[i*3] & 0x10) /16;
		c[4] = (a[i*3] & 0x08) /8;	
		c[5] = (a[i*3] & 0x04) /4;
		b[j++] = base[c[0]*32 + c[1]*16 + c[2]*8 + c[3]*4 + c[4]*2 + c[5]];
		
		c[0] = (a[i*3] & 0x02) / 2;
		c[1] = (a[i*3] & 0x01)/ 1;
		c[2] = 0;
		c[3] = 0;
		c[4] = 0;	
		c[5] = 0;
		b[j++] = base[c[0]*32 + c[1]*16 + c[2]*8 + c[3]*4 + c[4]*2 + c[5]];
		b[j++] = '=';
		b[j++] = '=';
	}else if(a[3*i+2] == '\0'){		
		c[0] = (a[i*3] & 0x80) / 128;
		c[1] = (a[i*3] & 0x40)/ 64;
		c[2] = (a[i*3] & 0x20) /32;
		c[3] = (a[i*3] & 0x10) /16;
		c[4] = (a[i*3] & 0x08) /8;	
		c[5] = (a[i*3] & 0x04) /4;
		b[j++] = base[c[0]*32 + c[1]*16 + c[2]*8 + c[3]*4 + c[4]*2 + c[5]];
		
		c[0] = (a[i*3] & 0x02) / 2;
		c[1] = (a[i*3] & 0x01)/ 1;
		c[2] = (a[i*3+1] & 0x80) /128;
		c[3] = (a[i*3+1] & 0x40) /64;
		c[4] = (a[i*3+1] & 0x20) /32 ;	
		c[5] = (a[i*3+1] & 0x10) /16;
		b[j++] = base[c[0]*32 + c[1]*16 + c[2]*8 + c[3]*4 + c[4]*2 + c[5]];
		c[0] = (a[i*3+1] & 0x08)/8;
		c[1] = (a[i*3+1] & 0x04)/4;
		c[2] = (a[i*3+1] & 0x02)/2;
		c[3] = (a[i*3+1] & 0x01)/1 ;
		c[4] = 0;	
		c[5] = 0;
		b[j++] = base[c[0]*32 + c[1]*16 + c[2]*8 + c[3]*4 + c[4]*2 + c[5]];
		b[j++] = '=';
	}
	b[j] = '\0';
}

	
	
