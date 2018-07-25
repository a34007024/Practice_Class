#include <reg51.h>
#define ledPin P1
#define sw P0	//sw means switch
void delay(int ms);
//-----------------------------
int main(){
	while(1){
		if(sw == 0xfc){
			ledPin = 0x00;
			delay(100);
			ledPin = 0xff;
			delay(100);
		}
		else if(sw == 0xff){
			ledPin = 0x00;
		}
		else if(sw == 0x00){
			ledPin = 0xff;
		}
		else if(sw == 0xfe){
			for(ledPin = 0x00;ledPin<=0xff;ledPin++){
				if(sw!=0xfe)delay(100);
				else break;//離開for迴圈
			}
		}
		else{
			ledPin = sw;
		}
	}
	return 0;
}
//-------------------------------
void delay(int ms){
	int i,j;
	for(i=0;i<ms;i++)
		for(j=0;j<120;j++);
	//120是依據這塊板子上的石英晶體
	//(12MHz)推算出來的
}