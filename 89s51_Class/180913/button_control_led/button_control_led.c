#include <reg51.h>
#define led P1
#define sw P0
sbit button = P2^0;
void delay(int);
void flash();
void main(){
	int enableLED = 0;
	led = 0xff;
	button = 1;//初始化按鈕狀態
	while(1){
		if(!button){
			delay(10);// 等待雜訊過去
			if(!button){//確定按鈕訊號非雜訊
				if(enableLED == 1)enableLED = 0;
				else enableLED = 1;
				while(!button);//當按鈕一直被按下就卡在這
			}
			//按鈕被放開就跳出
		}
		if(enableLED == 1)flash();
		else led = 0xff;
	}
}
void flash(){
	led = 0xff;
	delay(100);
	led = 0x00;
	delay(100);
}
void delay(int delayXms){
	int i,j;
	for(i = 0;i < delayXms;i++)
		for(j=0;j<120;j++);
}