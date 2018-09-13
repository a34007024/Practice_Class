#include <reg51.h>
#define led P1
#define sw P0
sbit on = P2^0;
sbit off = P2^1;
void delay(int);
void flash();
void main(){
	int enableLED = 0;
	led = 0xff;
	on = off = 1;//初始化按鈕狀態
	while(1){
		if(!on)enableLED = 1;
		if(!off)enableLED = 0;
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