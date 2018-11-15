/*
programmer	:LuckyPig
fuctions	:按住INT0從0數到999，按住再放開INT1則歸零
version		:20181115A
*/
/*
接線說明:
a -> P0.0 (P0^0) a為LSB(最低位元)
b -> P0.1
依序a,b,c,d,e,f,g......
最後為dp -> P0.7 dp為MSB(最高位元)
D0 -> P2^0為LSB
依序接線
D3 -> P2^3為MSB
*/
#include<reg51.h>
#define seg7 P0
#define scan7seg P2
#define led P1
sbit seg7dp = P0^7;
sbit buzzer = P3^7;
char seg7hexCode[20] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98};
// 7-seg對應顯示輸出0~9
char scan7segCode[8] = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};//使用char比int節省空間
//7-seg的掃描碼
char segDisplayNumber[8] = {19,19,19,19,19,0,0,0};
char dataPointer = 0;
void display8digitsData(char dataIn[]);
void delay(int ms);
int timeCount = 0;
char countDown = 0;
void main(){
	IE=0x85;		//	啟用INT 0,INT 1中斷(0x85=10000101)
	IP=0x01;		//	設定高優先等級
	//int i;
	seg7hexCode[19] = 0xff;//清除顯示器
	while(1){
		display8digitsData(segDisplayNumber);
	}
}

void delay(int ms){
	int i,j;
	for(i = 0;i < ms;i++)
		for(j=0;j<120;j++);//do null
}

void display8digitsData(char dataIn[]){
	int i = 0;
	for(i = 0;i<8;i++){
		seg7 = seg7hexCode[dataIn[i]];
		scan7seg = scan7segCode[i];
		delay(1);
		if(timeCount <= 9999)timeCount +=1;
		else timeCount = 0;
	}								 
}
// === INT 0的中斷副程式 ===
void int0_count(void) interrupt 0 using 1	{
	display8digitsData(segDisplayNumber);
	if(timeCount >= 10){//about 100 ms
		if(segDisplayNumber[7] != 9)segDisplayNumber[7] += 1;
		else{
			segDisplayNumber[7] = 0;
			if(segDisplayNumber[6] != 9)segDisplayNumber[6] += 1;
			else{
				segDisplayNumber[6] = 0;
				if(segDisplayNumber[5] != 9)segDisplayNumber[5] += 1;
				else{
					segDisplayNumber[5] = 0;
				}
			}
		}
		timeCount = 0;
	}
}
// === INT 1中斷副程式 ===
void int1_right(void) interrupt 2 using 2 {
	display8digitsData(segDisplayNumber);	
	segDisplayNumber[5] = 0;
	segDisplayNumber[6] = 0;
	segDisplayNumber[7] = 0;
}
