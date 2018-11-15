#include <reg51.h>
#define LED P1
#define count 	50000
#define TH_M1	(65536-count)/256
#define TL_M1	(65536-count)%256

void main(){
	int i;
	TMOD = 1;
	LED = 0xf0;
	while(1){
		for(i=0;i<5;i++){
			TH0 = TH_M1;
			TL0 = TL_M1;
			TR0 = 1;
			while(!TF0);
			TF0=0;
		}
		LED =~ LED;
	}
}

void delay(int ms){
	
}