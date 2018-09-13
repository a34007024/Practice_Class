#include <reg51.h>
#define led P1
#define sw P0
#define readSW ~sw & 0x03
sbit buzzer = P3^7;
sbit resetled = P2^0;
void delay(int);
void ledmoveleft();
void ledmoveright();
void ledflash();
void beep(int);
void delay100us(int);
void main(){
	led = 0x00;
	buzzer = 1;//disable buzzer and switch所以送高態訊號
	delay(200);
	led = 0xfe;
	while(1){
		switch(readSW){
			case 0:
				led = 0xff;
				break;
			case 1:
				ledmoveleft();
				break;
			case 2:
				ledmoveright();
				break;
			case 3:
				ledmoveleft();beep(1);
				ledmoveright();beep(2);
				break;
		}
	}
}
void ledmoveleft(){
	int i; led = 0xfe;
	for(i = 0;i<8;i++){
		delay(100);
		led = led<<1 | 1;
	}
}
void ledmoveright(){
	int i; led = 0x7f;
	for(i = 0;i<8;i++){
		delay(100);
		led = led>>1 | 0x80;
	}
}
void ledflash(){
	//led =~ led;	// =~ 為將變數取反相
	led = 0xff;
	delay(300);
	led = 0x00;
	delay(300);
}
void beep(int beepcount){
	int i,j;
	for(i = 0;i < beepcount;i++){
		for(j = 0;j<200;j++){
			buzzer = 0;delay100us(1);
			buzzer = 1;delay100us(1);
		}
		delay(100);
	}
}
void delay(int delayXms){
	int i,j;
	for(i = 0;i < delayXms;i++)
		for(j=0;j<120;j++);
}
void delay100us(int delayXms){
	int i,j;
	for(i = 0;i < delayXms;i++)
		for(j=0;j<12;j++);
}