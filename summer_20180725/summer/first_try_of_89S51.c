//20180725育廷主任的89S51及C語言實習課
#include <reg51.h>
#define ledPin P1
sbit switch1 = P0^0;//宣告單一位元
void delay(int ms);//ms means millisecond
//-----------------------------------
main(){
	while(1){
		if(switch1 == 0){
			for(ledPin = 0x00;ledPin<=0xff;ledPin++){
				if(switch1==0)delay(100);
				else break;//離開for迴圈
			}
		}
		else{
			ledPin = 0x00;
			/*特別解說
			數值以0x開頭，表示使用16進制
			例如:0xFF即為十進制中的255*/
			delay(100);
			ledPin = 0xff;
			delay(100);
		}
	}
	
}
//=====================================
void delay(int ms){
	int i,j;
	for(i=0;i<ms;i++)
		for(j=0;j<120;j++);
	//120是依據這塊板子上的石英晶體
	//(12MHz)推算出來的
}










