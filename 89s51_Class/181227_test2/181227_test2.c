#include<reg51.h>
#define seg7 P0
#define scan7seg P1
sbit pb0 = P2^0;
sbit pb1 = P2^1;
/*
接線說明:
a -> P0.0 (P0^0) a為LSB(最低位元)
b -> P0.1
依序a,b,c,d,e,f,g......
最後為dp -> P0.7 dp為MSB(最高位元)
共用掃描訊號接至:
	D2 -> P1.2
	D3 -> P1.3
	D4 -> P1.4
	D5 -> P1.5

*/
char seg7hexCode[20] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98};
// 7-seg對應顯示輸出0~9
char scan7segCode[8] = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
// 7-seg對應掃描碼 (使用char比int節省空間)
int displayData[4] = {0,0,0,0};
int countState = 0;
void delay500us(int);
void CheckReset7seg();
void display4digitsData(int[]);
int delayTime = 0;
int btnLock = 0;
void main(){
	scan7seg = 0x00;
	seg7 = seg7hexCode[0];
	
	while(1){
		CheckReset7seg();
		if(pb1 == 0 && btnLock == 0){
			delay500us(2);
			if(pb1 == 0){
				btnLock = 1;
				if(countState == 0)countState = 1;
				else countState = 0;
			}
		}
		if(pb1 == 1){
			btnLock = 0;
		}
		
		if(countState == 0){//暫停計數
			//do nothing
		}
		else if(countState == 1){//開始計數
			CheckReset7seg();
			if(delayTime/2 >= 10){//經過10ms
				if(displayData[3] != 9)displayData[3] += 1;
				else if(displayData[2] != 9){
					displayData[3] = 0;
					displayData[2] += 1;
				}
				else if(displayData[1] != 9){
					displayData[3] = 0;
					displayData[2] = 0;
					displayData[1] += 1;
				}
				else if(displayData[0] != 6){
					displayData[3] = 0;
					displayData[2] = 0;
					displayData[1] = 0;
					displayData[0] += 1;
				}
				if(displayData[0] == 6){
					displayData[0] = 0;
					displayData[1] = 0;
					displayData[2] = 0;
					displayData[3] = 0;
				}
				delayTime = 0;
			}
		}
		display4digitsData(displayData);
	}
	
}

void delay500us(int owo){
	int i,j;
	for(i=0;i<owo;i++){
		for(j=0;j<60;j++);//do nothing 60 times
	}
}

void CheckReset7seg(){
	if(pb0 == 0){
		delay500us(2);
		if(pb0 == 0){
			displayData[0] = 0;
			displayData[1] = 0;
			displayData[2] = 0;
			displayData[3] = 0;
			delayTime = 0;
		}
	}
}

void display4digitsData(int dataIn[]){
	int i = 0;
	for(i = 0;i<4;i++){
		scan7seg = 0xff;//防殘影
		seg7 = seg7hexCode[dataIn[i]];
		scan7seg = scan7segCode[i+2];
		delay500us(1);
		delayTime += 1;
	}
}
