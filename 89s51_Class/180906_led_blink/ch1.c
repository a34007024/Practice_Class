#include <reg51.h>
#define led P1
void delay(int);

void main(){
	char pat = 0x0f;
	led = pat;
	while(1){
		delay(250);
		led =~ led;
		//=~代表把變數反相	
	}
}

void delay(int millisecond){
	for(int i=0;i < millisecond;i++){
		for(int j=0;j<120;j++)
	}
}