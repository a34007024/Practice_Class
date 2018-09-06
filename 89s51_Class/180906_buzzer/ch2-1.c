#include <reg51.h>
sbit buzzer P3^7;
sbit buzzer_sw P0^0;
void beep(int);
void delay500us(int);

void main(){
	buzzer = 1;buzzer_sw=1;
	//set buzzer and switch to OFF at startup
	while(1){
		if(!buzzer_sw) beep(1);
	}
}
void beep(int beepcount){//one beep last for 0.2s
	int i,j;
	for(i=0;i<beepcount;i++){
		for(j=0;j<100;j++){
			buzzer = 0;delay500us(1);
			buzzer = 1;delay500us(1);
		}
		delay500us(200); //100ms
	}
}
void delay500us(int time){
	int i,j;
	for(i=0;i<time;i++){
		for(j=0;j<60;j++);
	}
}