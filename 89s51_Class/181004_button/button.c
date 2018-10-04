#include <reg51.h>
#define led P1
sbit pb4 = P2^1;
void delay(int ms);

void main(){
	led = 0x00;
	while(1){
		if(pb4 == 0){
			delay(5);
			if(pb4==0)led =~ led;
			while(pb4==0);//wait until button is released
			delay(5);
		}
		
	}
}

void delay(int ms){
	int i,j;
	for(i = 0;i<ms;i++)
		for(j=0;j<120;j++);//do nothing
}





