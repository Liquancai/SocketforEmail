#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define serport 8888
#define cliport 25

void sendEmail1(int clifd, int accfd);
void sendEmail2(int clifd, int accfd);
void sendEmail0(int clifd, int accfd);
void base64(char *a, char *b);
int verify(int clifd, char *u, char *p);
void authlogin(int clifd, char *u, char *p);
void clientinit(int *c, int flag);
	
char username[200], passwd[200], rcpt[1024], subject[1024], body[2048], attach[65536];
int main()
{
	int serfd, accfd, clifd;


	char buffer[1024];
	int len = 0; //用于表示接收字符长度
	int verifyresult; //用于表示验证结果
	int sendagain = 1;
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
	if (listen(serfd,10) == -1){
		printf("server listen fail!\n");
		return 0;
	}
	while (1){
		accfd = accept(serfd, NULL, NULL);
		if (accfd == -1){
			printf("server accept fail!\n");
			return 0;
		}else{	
			while(1){
				len = recv(accfd, username, sizeof(username), 0);
				username[len] = '\0';
				printf("u %s\n", username);
				len = recv(accfd, passwd, sizeof(passwd), 0);
				passwd[len] = '\0';
				printf("p %s\n", passwd);
				if (strstr(username,"@163.com") == NULL)
					clientinit(&clifd, 2);
				else 
					clientinit(&clifd, 1);
				verifyresult = verify(clifd, username, passwd);
				close(clifd);
				if (verifyresult == 2)
					send(accfd, "error2", strlen("error2"),0);
				else if (verifyresult == 3)
					send(accfd, "error3", strlen("error3"),0);
				else if (verifyresult == 0){
					send(accfd, "success", strlen("success"),0);
					break;
				}	
			}
			while (sendagain){
				if (strstr(username,"@163.com") == NULL)
					clientinit(&clifd, 2);
				else 
					clientinit(&clifd, 1);
				authlogin(clifd, username, passwd);
				
				len = recv(accfd, buffer, sizeof(buffer), 0);
				if (buffer[0] == '1')
					sendagain = 1;
				else 
					break;			
	
				len = recv(accfd, buffer, sizeof(buffer), 0);
				if (buffer[0] == '1')
					sendEmail1(clifd, accfd);
				else if (buffer[0] == '2')
					sendEmail2(clifd, accfd);
				else 		
					sendEmail0(clifd, accfd);
			}
		}
		close(accfd);
	}
	close(serfd);
	close(clifd);
	return 0;
}
void sendEmail0(int clifd, int accfd){
	char buffer[1024];
        int len;
	
	len = recv(accfd, rcpt, sizeof(rcpt), 0);
	rcpt[len] = '\0';
	printf("1 %s\n", rcpt);

	send(accfd, "get2", strlen("get2"),0);
	len = recv(accfd, subject, sizeof(subject), 0);
	subject[len] = '\0';
	printf("2 %s\n", subject);


	len = recv(accfd, body, sizeof(body), 0);
	body[len] = '\0';
	printf("3 %s\n", body);
	
	
	char from5[300];
	strcpy(from5, "mail from:<");
	strcat(from5, username);
	strcat(from5, ">\n");

	char rcpt6[300];
	strcpy(rcpt6, "rcpt to:<");
	strcat(rcpt6, rcpt);
	strcat(rcpt6, ">\n");

	char data7[] = "DATA\n";

	char from8[300];
	strcpy(from8, "from:<");
	strcat(from8, username);
	strcat(from8, ">\n");
	
	char to9[300];
	strcpy(to9, "to:<");
	strcat(to9, rcpt);
	strcat(to9, ">\n");
	
	char subject10[1024];
	strcpy(subject10, "subject:");
	strcat(subject10, subject);
	strcat(subject10, "\n");
	
	char crtf11[] = "\n";
	
	char body12[2048];
	strcpy(body12, body);
	strcat(body12, "\n");
	
	char end13[] = ".\n";
	
	char quit14[] = "quit\n";
	
	char MIME[] = "MIME-Version:1.0\n";	
	
	char type[] = "Content-Type:multipart/mixed;boundary=\"===1caishu######===\"\n\n";
	char bEncode[] = "Content-Transfer-Encoding:7bit\n\n";
	char message[] = "This is a multi-part message in MIME\n\n";
	char boundary[] = "--===1caishu######===\n";
	char bodytype[] = "Content-Type:text/plain;charset=\"gb2312\"\n";
	char attachtype[] = "Content-Type:text/plain;name=Mclient.c\n";
	char bodyEncode[] = "Content- Transfer-Encoding:printable\n\n";
	char fname[] = "Content-Disposition:attachment;filename=\"Mclient.c\"\n\n";
	char Encode[] = "Content-Transfer-Encoding:base64\n";

	send(clifd, from5, strlen(from5),0);
	send(clifd, rcpt6, strlen(rcpt6),0);
	send(clifd, data7, strlen(data7),0);
	send(clifd, from8, strlen(from8),0);
	send(clifd, to9, strlen(to9),0);
	send(clifd, subject10, strlen(subject10),0);
//	send(clifd, MIME, strlen(MIME),0);
//	send(clifd, type, strlen(type),0);
//	send(clifd, boundary, strlen(boundary),0);
//	send(clifd, bodytype, strlen(bodytype),0);
//	send(clifd, bodyEncode, strlen(bodyEncode),0);
//	send(clifd, body12, strlen(body12),0);
//	send(clifd, boundary, strlen(boundary),0);
//	send(clifd, attachtype, strlen(attachtype),0);
//	send(clifd, fname, strlen(fname),0);
//	send(clifd, abody, strlen(abody),0);
	send(clifd, crtf11, strlen(crtf11),0);
	send(clifd, body12, strlen(body12),0);
	send(clifd, end13, strlen(end13),0);

	if ((len = read(clifd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return;
	}
	printf("send result:");
	buffer[len] = '\0';
	printf("%s\n", buffer);

	send(clifd, quit14, strlen(quit14),0);
	send(accfd, buffer, strlen(buffer),0);
	return;
}
void sendEmail2(int clifd, int accfd){
	char buffer[1024];
        int len;
	
	len = recv(accfd, rcpt, sizeof(rcpt), 0);
	rcpt[len] = '\0';
	printf("1 %s\n", rcpt);

	send(accfd, "get2", strlen("get2"),0);
	len = recv(accfd, subject, sizeof(subject), 0);
	subject[len] = '\0';
	printf("2 %s\n", subject);

	len = recv(accfd, body, sizeof(body), 0);
	body[len] = '\0';
	printf("3 %s\n", body);
	
	send(accfd, "get2", strlen("get2"),0);

	char attachname[100];
	len = recv(accfd, attachname, sizeof(attachname), 0);
	attachname[len] = '\0';
	printf("4 %s\n", attachname);

	int length, i = 0;
	len = recv(accfd, buffer, sizeof(buffer), 0);
	length = buffer[0] - '0';
	printf("5 %d\n", length);
	
	send(accfd, "get2", strlen("get2"),0);
	for (; i<=length; i++){
		len = recv(accfd, buffer, sizeof(buffer), 0);
		buffer[len] = '\0';
		if (i < length)
			send(accfd, "get", strlen("get"),0);
		strcat(attach, buffer);
	}

	printf("6 %s\n", attach);
	
	char from5[300];
	strcpy(from5, "mail from:<");
	strcat(from5, username);
	strcat(from5, ">\n");

	char rcpt6[300];
	strcpy(rcpt6, "rcpt to:<");
	strcat(rcpt6, rcpt);
	strcat(rcpt6, ">\n");

	char data7[] = "DATA\n";

	char from8[300];
	strcpy(from8, "from:<");
	strcat(from8, username);
	strcat(from8, ">\n");
	
	char to9[300];
	strcpy(to9, "to:<");
	strcat(to9, rcpt);
	strcat(to9, ">\n");
	
	char subject10[1024];
	strcpy(subject10, "subject:");
	strcat(subject10, subject);
	strcat(subject10, "\n");
	
	char crtf11[] = "\n";
	
	char body12[2048];
	strcpy(body12, body);
	strcat(body12, "\n");
	
	char end13[] = ".\n";
	
	char quit14[] = "quit\n";
	
	char MIME[] = "MIME-Version:1.0\n";	
	
	char type[] = "Content-Type:multipart/mixed;boundary=\"===1caishu######===\"\n\n";
	char bEncode[] = "Content-Transfer-Encoding:7bit\n\n";
	char message[] = "This is a multi-part message in MIME\n\n";
	char boundary[] = "--===1caishu######===\n";
	char bodytype[] = "Content-Type:text/plain;charset=\"gb2312\"\n";
	char attachtype[] = "Content-Type:image/gif\n";
	char bodyEncode[] = "Content- Transfer-Encoding:printable\n\n";
	char fname[300];
	strcpy(fname, "Content-Disposition:attachment;filename=\"");
	strcat(fname, attachname);
	strcat(fname, "\"\n\n");
	char attachEncode[] = "Content-Transfer-Encoding:base64\n";

	send(clifd, from5, strlen(from5),0);
	send(clifd, rcpt6, strlen(rcpt6),0);
	send(clifd, data7, strlen(data7),0);
	send(clifd, from8, strlen(from8),0);
	send(clifd, to9, strlen(to9),0);
	send(clifd, subject10, strlen(subject10),0);
	send(clifd, MIME, strlen(MIME),0);
	send(clifd, type, strlen(type),0);
	send(clifd, boundary, strlen(boundary),0);
	send(clifd, bodytype, strlen(bodytype),0);
	send(clifd, bodyEncode, strlen(bodyEncode),0);
	send(clifd, body12, strlen(body12),0);
	send(clifd, boundary, strlen(boundary),0);
	send(clifd, attachtype, strlen(attachtype),0);
	send(clifd, attachEncode, strlen(attachEncode),0);
	send(clifd, fname, strlen(fname),0);
	send(clifd, attach, strlen(attach),0);
	send(clifd, crtf11, strlen(crtf11),0);
	send(clifd, end13, strlen(end13),0);

	if ((len = read(clifd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return;
	}
	printf("send result:");
	buffer[len] = '\0';
	printf("%s\n", buffer);

	send(clifd, quit14, strlen(quit14),0);
	send(accfd, buffer, strlen(buffer),0);
	return;
}
void sendEmail1(int clifd, int accfd){
	char buffer[1024];
        int len;
	
	len = recv(accfd, rcpt, sizeof(rcpt), 0);
	rcpt[len] = '\0';
	printf("1 %s\n", rcpt);

	send(accfd, "get2", strlen("get2"),0);
	len = recv(accfd, subject, sizeof(subject), 0);
	subject[len] = '\0';
	printf("2 %s\n", subject);

	len = recv(accfd, body, sizeof(body), 0);
	body[len] = '\0';
	printf("3 %s\n", body);
	
	send(accfd, "get2", strlen("get2"),0);

	char attachname[100];
	len = recv(accfd, attachname, sizeof(attachname), 0);
	attachname[len] = '\0';
	printf("5 %s\n", attachname);

	len = recv(accfd, attach, sizeof(attach), 0);
	attach[len] = '\0';
	printf("4 %s\n", attach);
	char from5[300];
	strcpy(from5, "mail from:<");
	strcat(from5, username);
	strcat(from5, ">\n");

	char rcpt6[300];
	strcpy(rcpt6, "rcpt to:<");
	strcat(rcpt6, rcpt);
	strcat(rcpt6, ">\n");

	char data7[] = "DATA\n";

	char from8[300];
	strcpy(from8, "from:<");
	strcat(from8, username);
	strcat(from8, ">\n");
	
	char to9[300];
	strcpy(to9, "to:<");
	strcat(to9, rcpt);
	strcat(to9, ">\n");
	
	char subject10[1024];
	strcpy(subject10, "subject:");
	strcat(subject10, subject);
	strcat(subject10, "\n");
	
	char crtf11[] = "\n";
	
	char body12[2048];
	strcpy(body12, body);
	strcat(body12, "\n");
	
	char end13[] = ".\n";
	
	char quit14[] = "quit\n";
	
	char MIME[] = "MIME-Version:1.0\n";	
	
	char type[] = "Content-Type:multipart/mixed;boundary=\"===1caishu######===\"\n\n";
	char bEncode[] = "Content-Transfer-Encoding:7bit\n\n";
	char message[] = "This is a multi-part message in MIME\n\n";
	char boundary[] = "--===1caishu######===\n";
	char bodytype[] = "Content-Type:text/plain;charset=\"gb2312\"\n";
	char attachtype[] = "Content-Type:text/plain\n";
	char bodyEncode[] = "Content- Transfer-Encoding:printable\n\n";
	char fname[300];
	strcpy(fname, "Content-Disposition:attachment;filename=\"");
	strcat(fname, attachname);
	strcat(fname, "\"\n\n");
	char Encode[] = "Content-Transfer-Encoding:base64\n";

	send(clifd, from5, strlen(from5),0);
	send(clifd, rcpt6, strlen(rcpt6),0);
	send(clifd, data7, strlen(data7),0);
	send(clifd, from8, strlen(from8),0);
	send(clifd, to9, strlen(to9),0);
	send(clifd, subject10, strlen(subject10),0);
	send(clifd, MIME, strlen(MIME),0);
	send(clifd, type, strlen(type),0);
	send(clifd, boundary, strlen(boundary),0);
	send(clifd, bodytype, strlen(bodytype),0);
	send(clifd, bodyEncode, strlen(bodyEncode),0);
	send(clifd, body12, strlen(body12),0);
	send(clifd, boundary, strlen(boundary),0);
	send(clifd, attachtype, strlen(attachtype),0);
	send(clifd, fname, strlen(fname),0);
	send(clifd, attach, strlen(attach),0);
	send(clifd, crtf11, strlen(crtf11),0);
	send(clifd, end13, strlen(end13),0);

	if ((len = read(clifd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return;
	}
	printf("send result:");
	buffer[len] = '\0';
	printf("%s\n", buffer);

	send(clifd, quit14, strlen(quit14),0);
	send(accfd, buffer, strlen(buffer),0);
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

int verify(int clifd, char *u, char *p){
	int len;
	char username[250], passwd[250], buffer[1024];
	base64(u, username);
	base64(p, passwd);
	
	send(clifd, "auth login\n", strlen("auth login\n"),0);
	if ((len = read(clifd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return;
	}
	printf("ask username:");
	buffer[len] = '\0';
	printf("%s\n", buffer);
	
	send(clifd, username, strlen(username),0);
	send(clifd, "\n", strlen("\n"),0);
	if ((len = read(clifd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return;
	}
	printf("ask passwd:");
	buffer[len] = '\0';
	printf("%s\n", buffer);
	if (buffer[0] == '5'){
		printf("error2\n");
		return 2;
	}

	send(clifd, passwd, strlen(passwd),0);
	send(clifd, "\n", strlen("\n"),0);
	if ((len = read(clifd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return;
	}
	printf("login result:");
	buffer[len] = '\0';
	printf("%s\n", buffer);
	if (buffer[0] == '5'){
		printf("error3\n");
		return 3;
	}

	send(clifd, "quit\n", strlen("quit\n"),0);
	return 0;
}
void clientinit(int *c, int flag){

	struct sockaddr_in c_add;
	char buffer[1024];
	int len = 0; //用于表示接收字符长度
	*c = socket(AF_INET, SOCK_STREAM, 0);
	if (*c == -1){
		printf("client socket fail!\n");
		return;
	}
	
	bzero(&c_add, sizeof(struct sockaddr_in));
	c_add.sin_family = AF_INET;
	if (flag == 1)
		c_add.sin_addr.s_addr = inet_addr("220.181.12.15");
	else
		c_add.sin_addr.s_addr = inet_addr("220.181.15.111");
	c_add.sin_port = htons(cliport);
	if (connect(*c, (struct sockaddr*)(&c_add), sizeof(struct sockaddr)) == -1){
		printf("client connect fail!\n");
		return;
}
	if ((len = read(*c, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return;
	}
	printf("start:");
	buffer[len] = '\0';
	printf("%s\n", buffer);
	
	send(*c, "ehlo gacl\n", strlen("ehlo gacl\n"),0);
	if ((len = read(*c, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return;
	}
	printf("to hello:");
	buffer[len] = '\0';
	printf("%s\n", buffer);

}

void authlogin(int clifd, char *u, char *p){
	int len;
	char username[250], passwd[250], buffer[1024];
	base64(u, username);
	base64(p, passwd);
	
	send(clifd, "auth login\n", strlen("auth login\n"),0);
	if ((len = read(clifd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return;
	}
//	printf("ask username:");
	buffer[len] = '\0';
//	printf("%s\n", buffer);
	
	send(clifd, username, strlen(username),0);
	send(clifd, "\n", strlen("\n"),0);
	if ((len = read(clifd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return;
	}

	send(clifd, passwd, strlen(passwd),0);
	send(clifd, "\n", strlen("\n"),0);
	if ((len = read(clifd, buffer, 1024)) == -1){
		printf("read data fail !\n");
		return;
	}

}
