#include <reg51.h>
sbit buzzer=P3^7;
sbit buzzer_sw=P0^0;
sbit buzzer_sw2=P0^1;
void beep(int);
void beepSW2(int);
void delay100us(int);

void main(){
	buzzer = 1;buzzer_sw=1;
	//set buzzer and switch to OFF at startup
	while(1){
		if(!buzzer_sw)beep(1);	// if(!buzzer_sw)  =  if(buzzer_sw==0)
		if(!buzzer_sw2)beepSW2(1);
	}
}
void beep(int beepcount){//one beep last for 0.2s
	int i,j;
	for(i=0;i<beepcount;i++){
		for(j=0;j<100;j++){
			buzzer = 0;delay100us(1);
			buzzer = 1;delay100us(1);
		}
		delay100us(1000); //100ms
	}  
	for(i=0;i<beepcount;i++){
		for(j=0;j<100;j++){
			buzzer = 0;delay100us(2);
			buzzer = 1;delay100us(2);
		}
		delay100us(1000); //100ms
	}
}
void beepSW2(int beepcount){//one beep last for 0.2s
	int i,j;
	for(i=0;i<beepcount;i++){
		for(j=0;j<100;j++){
			buzzer = 0;delay100us(3);
			buzzer = 1;delay100us(3);
		}
		delay100us(1000); //100ms
	}  
	for(i=0;i<beepcount;i++){
		for(j=0;j<100;j++){
			buzzer = 0;delay100us(5);
			buzzer = 1;delay100us(5);
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