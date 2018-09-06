#include <reg51.h>
#define led P1
void delay(int);

void main(){
	char pat = 0xff;
	led = pat;
	while(1){
		led = 0xff;
		delay(500);
		led = 0xe7;
		delay(500);
		led = 0xc3;
		delay(500);
		led = 0x81;
		delay(500);
		led = 0x00;
		delay(500);
		//=~代表把變數反相	
	}
}
/* blink table (0 = bright 1 = dark)
1111 1111 0xff
1110 0111 0xe7
1100 0011 0xc3
1000 0001 0x81
0000 0000 0x00
*/
void delay(int millisecond){
	int i,j;
	for(i=0;i < millisecond;i++){
		for(j=0;j<120;j++);
	}
}