#include<reg51.h>
#define seg7 P0
#define scan7seg P2
sbit seg7dp = P0^7;
char seg7hexCode[16] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98};
int seg7number = 0;
char scan7segCode[4] = {0xf7,0xfb,0xfd,0xfe};//�ϥ�char��int�`�٪Ŷ�
char show8051[4] = {8,0,5,1};
/*
���u����:
a -> P0.0 (P0^0) a��LSB(�̧C�줸)
b -> P0.1
�̧�a,b,c,d,e,f,g......
�̫ᬰdp -> P0.7 dp��MSB(�̰��줸)
D0 -> P2^0��LSB
�̧Ǳ��u
D3 -> P2^0��MSB
*/
void delay(int ms);
void main(){
	int i;
	int time = 0;
	while(1){
		seg7 = seg7hexCode[seg7number];//show number on 7Seg
		while(time <= 500){
			for(i = 0;i<4;i++){
				scan7seg = scan7segCode[i];
				seg7 = seg7hexCode[show8051[i]];
				delay(2);
				time +=2;
			}
		}
		time = 0;
		seg7 = 0xff;
		delay(500);
	}
}

void delay(int ms){
	int i,j;
	for(i = 0;i < ms;i++)
		for(j=0;j<120;j++);//do null
}

