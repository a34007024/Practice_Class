#include<reg51.h>
#define seg7 P0
#define scan7seg P1
sbit seg7dp = P0^7;
sbit pb4 = P2^1;//7seg number add one when pressed
sbit pb3 = P2^0;//7seg number sub one when pressed
char seg7hexCode[16] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98};
int seg7number = 0;
char scan7segCode[4] = {0xf7,0xfb,0xfd,0xfe};//使用char比int節省空間
char show4numbers[4] = {0,0,0,0};//千位數至個位數
//===========================================
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
//===========================================
void delay(int ms);
int check7segNumber();
void main(){
	int i;
	while(1){
		seg7 = seg7hexCode[seg7number];//show number on 7Seg
		for(i = 0;i<4;i++){
			scan7seg = scan7segCode[i];
			seg7 = seg7hexCode[show4numbers[i]];
			delay(2);
		}
		if(pb4 == 0){
			delay(10);
			if(pb4 == 0){//判斷是否為雜訊
				if(check7segNumber() == 9) seg7number = 0;
				else seg7number +=1;
				while(pb4 == 0);//wait until button released
			}
			delay(10);
		}
		if(pb3 == 0){
			delay(10);
			if(pb3 == 0){//判斷是否為雜訊
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

