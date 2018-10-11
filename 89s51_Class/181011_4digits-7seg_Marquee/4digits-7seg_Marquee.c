#include<reg51.h>
#define seg7 P0
#define scan7seg P1
sbit seg7dp = P0^7;
char seg7hexCode[20] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98};
char scan7segCode[4] = {0xf7,0xfb,0xfd,0xfe};//使用char比int節省空間
char DisplayData[4];
char mydata[8] = {8,0,5,1,19,19,19,19};
char dataPointer = 0;
/*
接線說明:
a -> P0.0 (P0^0) a為LSB(最低位元)
b -> P0.1
依序a,b,c,d,e,f,g......
最後為dp -> P0.7 dp為MSB(最高位元)
D0 -> P1^0為LSB
依序接線
D3 -> P1^3為MSB
*/
void delay(int ms);
void main(){
	int i;
	int delayTime = 0;
	seg7hexCode[19] = 0xff;
	for(i = 0;i<4;i++){
		DisplayData[i] = 19;//19在seg7hexCode裡為null
	}
	while(1){
		for(i = 0;i<4;i++){
			scan7seg = scan7segCode[i];
			seg7 = seg7hexCode[DisplayData[i]];
			delay(2);delayTime +=2;
		}
		if(delayTime >= 300){
			for(i = 0;i<4;i++){
				if(i<=2) DisplayData[i] = DisplayData[i+1];
				if(i==3){
					DisplayData[i] = mydata[dataPointer];
					if(dataPointer == 7) dataPointer = 0;
					else dataPointer += 1;
				}
			}
			delayTime = 0;
		}
	}
}

void delay(int ms){
	int i,j;
	for(i = 0;i < ms;i++)
		for(j=0;j<120;j++);//do null
}