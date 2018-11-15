/*
programmer	:LuckyPig
fuctions	:倒數60秒後beep兩聲的定時炸彈倒數計時器
version		:20181115A
*/
/*
接線說明:
a -> P0.0 (P0^0) a為LSB(最低位元)
b -> P0.1
依序a,b,c,d,e,f,g......
最後為dp -> P0.7 dp為MSB(最高位元)
D0 -> P2^0為LSB
依序接線
D3 -> P2^3為MSB
*/
#include<reg51.h>
#define seg7 P0
#define scan7seg P2
#define led P1
sbit seg7dp = P0^7;
sbit buzzer = P3^7;
char seg7hexCode[20] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98};
// 7-seg對應顯示輸出0~9
char scan7segCode[8] = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};//使用char比int節省空間
//7-seg的掃描碼
char countDownNumber[8] = {19,19,19,19,19,19,6,0};
char dataPointer = 0;
void display8digitsData(char dataIn[]);
void delay(int ms);
void delay100us(int time);
void beep(int beepcount);
int displayTime = 0;
char power = 1;
void main(){
	//int i;
	seg7hexCode[19] = 0xff;//清除顯示器
	while(power == 1){
		if(displayTime <= 100){
			display8digitsData(countDownNumber);
		}
		else {
			if(countDownNumber[7]!=0){
				countDownNumber[7] -= 1;
			}
			else if(countDownNumber[7]==0 && countDownNumber[6]!=0){
				countDownNumber[7] = 9;
				countDownNumber[6] -= 1;
			}
			else{
				countDownNumber[6] = countDownNumber[7] = 19;
				display8digitsData(countDownNumber);
				beep(2);
				power = 0;
				led = 0x00;
			}
			displayTime = 0;
		}
	}
	while(power == 0){
		
	}
}

void delay(int ms){
	int i,j;
	for(i = 0;i < ms;i++)
		for(j=0;j<120;j++);//do null
}

void display8digitsData(char dataIn[]){
	int i = 0;
	for(i = 0;i<8;i++){
		seg7 = seg7hexCode[dataIn[i]];
		scan7seg = scan7segCode[i];
		delay(1);
		displayTime +=1;
	}								 
}
void beep(int beepcount){
	int i,j;
	for(i=0;i<beepcount;i++){
		for(j=0;j<100;j++){
			buzzer = 0;delay100us(1);
			buzzer = 1;delay100us(1);
		}
		delay100us(1000); //100ms
	}  
}
void delay100us(int time){
	int i,j;
	for(i=0;i<time;i++){
		for(j=0;j<12;j++);
	}
}