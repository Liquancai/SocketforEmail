#include <string.h>
#include <stdio.h>
int main(){
	char a[1024], b[1366];
	int  c[6];
	char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int i = 0, j = 0;
	scanf("%s", a);
	while (strlen(a)/3 > i){
	//	printf("%c %c %c\n", a[i*3], a[i*3+1], a[i*3+2]);
		c[0] = (a[i*3] & 0x80) /128;
		c[1] = (a[i*3] & 0x40)/64;
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
		c[3] = (a[i*3+1] & 0x01)/1;
		c[4] = (a[i*3+2] & 0x80)/128;	
		c[5] = (a[i*3+2] & 0x40)/64;
		b[j++] = base[c[0]*32 + c[1]*16 + c[2]*8 + c[3]*4 + c[4]*2 + c[5]];
		
		c[0] = (a[i*3+2] & 0x20)/32;
		c[1] = (a[i*3+2] & 0x10)/16;
		c[2] = (a[i*3+2] & 0x08)/8;
		c[3] = (a[i*3+2] & 0x04)/4;
		c[4] = (a[i*3+2] & 0x02)/2;	
		c[5] = (a[i*3+2] & 0x01)/1;
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
	puts(b);
	return 0;
}
