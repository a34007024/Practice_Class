#include<reg51.h>
#define seg7 P2
sbit seg7dp = P2^7;
char seg7hexCode[16] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98};
/*
接線說明:
a -> P2.0 (P2^0)
b -> P2.1
依序a,b,c,d,e,f,g......
最後為dp -> P2.7
*/
void delay(int ms);
void main(){
	while(1){
		int i = 0;
		for(i = 0;i<10;i++){
			seg7 = seg7hexCode[i];
			delay(300);
			seg7 = 0xff;//turn off 7seg
			delay(300);
		}
		seg7 = 0xff;
		delay(1000);
		for(i = 9;i>=0;i--){
			seg7 = seg7hexCode[i];
			delay(300);
			seg7 = 0xff;//turn off 7seg
			delay(300);
		}
		seg7 = 0xff;
		delay(1000);
	}
}

void delay(int ms){
	int i,j;
	for(i = 0;i < ms;i++)
		for(j=0;j<120;j++);//do null
}
