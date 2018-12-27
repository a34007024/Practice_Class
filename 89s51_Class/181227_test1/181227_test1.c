#include<reg51.h>
#define led P1
#define seg7 P0
sbit pb0 = P3^0;
sbit pb1 = P3^1;
sbit pb2 = P3^2;
sbit pb3 = P3^3;
sbit buzzer = P3^7;
/*
接線說明:
*共用掃描訊號D0接至GND
a -> P0.0 (P0^0) a為LSB(最低位元)
b -> P0.1
依序a,b,c,d,e,f,g......
最後為dp -> P0.7 dp為MSB(最高位元)

右側按鈕 (PB0) R0 -> P3.0
		 (PB1) R1 -> P3.1
		 (PB2) R2 -> P3.2
		 (PB3) R3 -> P3.3
		 ***重要c0-c3全都接到GND***
*/
char seg7hexCode[20] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98};
// 7-seg對應顯示輸出0~9
int seg7Number = 0;
void delay(int);
void ledmoveleft();
void ledmoveright();
void led_and_seg7_flash(int);
void beep(int);
void delay100us(int);

void main(){
	led = 0x00;
	seg7 = seg7hexCode[0];
	seg7Number = 0;
	while(1){
		if(pb0 == 0){
			delay(5);
			if(pb0 == 0){
				ledmoveleft();
				if(seg7Number != 9)seg7Number += 1;
				else seg7Number = 0;
				seg7 = seg7hexCode[seg7Number];
			}
		}
		else if(pb1 == 0){
			delay(5);
			if(pb1 == 0){
				ledmoveright();
				if(seg7Number != 0)seg7Number -= 1;
				else seg7Number = 9;
				seg7 = seg7hexCode[seg7Number];
			}
		}
		else if(pb2 == 0){
			delay(5);
			if(pb2 == 0){
				seg7Number = 0;
				seg7 = seg7hexCode[seg7Number];
				beep(2);
			}
		}
		else if(pb3 == 0){
			delay(5);
			if(pb3 == 0){
				led_and_seg7_flash(seg7Number);
			}
		}
	}
}

void delay(int ms){
	int i,j;
	for(i=0;i<ms;i++){
		for(j=0;j<120;j++);//do nothing 120 times
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
void led_and_seg7_flash(int seg7State){
	//led =~ led;	// =~ 為將變數取反相
	led = 0xff;
	seg7 = 0xff;
	delay(200);
	led = 0x00;
	seg7 = seg7hexCode[seg7State];
	delay(200);
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
void delay100us(int delayXms){
	int i,j;
	for(i = 0;i < delayXms;i++)
		for(j=0;j<12;j++);
}