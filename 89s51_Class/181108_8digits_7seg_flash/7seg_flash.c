#include<reg51.h>
#define seg7 P0
#define scan7seg P1
sbit seg7dp = P0^7;
char seg7hexCode[20] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98};
// 7-seg對應顯示輸出0~9
char scan7segCode[8] = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};//使用char比int節省空間
//7-seg的掃描碼
char homeNumber[8] = {2,7,0,9,1,6,3,0};
char phoneNumber[8] = {1,2,3,4,5,6,7,8};
char dataPointer = 0;
/*
接線說明:
a -> P0.0 (P0^0) a為LSB(最低位元)
b -> P0.1
依序a,b,c,d,e,f,g......
最後為dp -> P0.7 dp為MSB(最高位元)
D0 -> P1^0為LSB
依序接線
D3 -> P1^3為MSB
*/
void delay(int ms);
void main(){
	int i,j;
	int displayTime = 0;
	seg7hexCode[19] = 0xff;//清除顯示器
	while(1){
		if(displayTime <= 1000){
			for(i = 0;i<8;i++){
				seg7 = seg7hexCode[homeNumber[i]];
				scan7seg = scan7segCode[i];
				delay(1);
				displayTime +=1;
			}
		}
		else if(displayTime <= 2000){
			for(i = 0;i<8;i++){
				seg7 = seg7hexCode[phoneNumber[i]];
				scan7seg = scan7segCode[i];
				delay(1);
				displayTime +=1;
			}
		}
		else displayTime = 0;
	}
}

void delay(int ms){
	int i,j;
	for(i = 0;i < ms;i++)
		for(j=0;j<120;j++);//do null
}