#include<reg51.h>
#define seg7 P2
sbit seg7dp = P2^7;
/*
接線說明:
a -> P2.0 (P2^0)
b -> P2.1
依序a,b,c,d,e,f,g......
最後為dp -> P2.7
*/
void segShow(int number,int dotEnable);
void delay(int ms);
void main(){
	while(1){
		segShow(0,1);delay(300);
		segShow(1,1);delay(300);
		segShow(2,1);delay(300);
		segShow(3,1);delay(300);
		segShow(4,1);delay(300);
		segShow(5,1);delay(300);
		segShow(6,1);delay(300);
		segShow(7,1);delay(300);
		segShow(8,1);delay(300);
		segShow(9,1);delay(300);
		segShow(-1,1);delay(1000);
		segShow(0,0);delay(300);
		segShow(1,0);delay(300);
		segShow(2,0);delay(300);
		segShow(3,0);delay(300);
		segShow(4,0);delay(300);
		segShow(5,0);delay(300);
		segShow(6,0);delay(300);
		segShow(7,0);delay(300);
		segShow(8,0);delay(300);
		segShow(9,0);delay(300);
		segShow(-1,1);delay(1000);
	}
}

void delay(int ms){
	int i,j;
	for(i = 0;i < ms;i++)
		for(j=0;j<120;j++);//do null
}

void segShow(int number,int dotEnable){
	switch(number){
		case 0:
			seg7 = 0xc0;
			break;
		case 1:
			seg7 = 0xf9;
			break;
		case 2:
			seg7 = 0xa4;
			break;
		case 3:
			seg7 = 0xb0;
			break;
		case 4:
			seg7 = 0x99;
			break;
		case 5:
			seg7 = 0x92;
			break;
		case 6:
			seg7 = 0x82;
			break;
		case 7:
			seg7 = 0xf8;
			break;
		case 8:
			seg7 = 0x80;
			break;
		case 9:
			seg7 = 0x98;
			break;
		default:
			seg7 = 0xff;
			break;
	}
	if(dotEnable == 0) seg7dp = 0;
	else seg7dp = 1;
}