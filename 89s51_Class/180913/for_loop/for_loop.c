#include <reg51.h>
sbit sw = P0^0;
sbit buzzer = P3^7;
void delay(int);
void beep(int);

main(){
	buzzer = sw = 1;//disable buzzer and switch所以送高態訊號
	while(1){
		if(!sw)beep(1);// (!sw) = (sw==0)
	}
}
void beep(int beepcount){
	int i,j;
	for(i = 0;i < beepcount;i++){
		for(j = 0;j<100;j++){
			buzzer = 0;delay(1);
			buzzer = 1;delay(1);
		}
		delay(100);
	}
}
void delay(int delayXms){
	int i,j;
	for(i = 0;i < delayXms;i++)
		for(j=0;j<120;j++);
}
