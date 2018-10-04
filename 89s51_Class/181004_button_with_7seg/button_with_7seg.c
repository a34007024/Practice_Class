#include<reg51.h>
#define seg7 P0
sbit seg7dp = P0^7;
sbit pb4 = P2^1;//7seg number add one when pressed
sbit pb3 = P2^0;//7seg number sub one when pressed
char seg7hexCode[16] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98};
int seg7number = 0;
/*
接線說明:
a -> P0.0 (P0^0) a為LSB(最低位元)
b -> P0.1
依序a,b,c,d,e,f,g......
最後為dp -> P0.7 dp為MSB(最高位元)
*/
void delay(int ms);
int check7segNumber();
void main(){
	while(1){
		seg7 = seg7hexCode[seg7number];//show number on 7Seg
		if(pb4 == 0){
			delay(10);
			if(pb4 == 0){
				if(check7segNumber() == 9) seg7number = 0;
				else seg7number +=1;
				while(pb4 == 0);//wait until button released
			}
			delay(10);
		}
		if(pb3 == 0){
			delay(10);
			if(pb3 == 0){
				if(check7segNumber() == 0) seg7number = 9;
				else seg7number -=1;
				while(pb3 == 0);//wait until button released
			}
			delay(10);
		}
	}
}

void delay(int ms){
	int i,j;
	for(i = 0;i < ms;i++)
		for(j=0;j<120;j++);//do null
}

int check7segNumber(){
	if(seg7number >= 9) return 9;
	else if(seg7number <= 0) return 0;
	else return -1;
}
