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
#include<reg51.h>
#define seg7Output P0
#define keyInput P2
sbit seg7dp = P0^7;
sbit Buzzer = P3^7;
char seg7hexCode[20] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98,0xa0,0x83,0xa7,0xa1,0x86,0x8e,0xff};
char SCAN_CODE[8]={	0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe };	
char DisplayData[4]={16,16,16,16};
void DELAY500us(int);
void keyscan();
void BEEP(char);
void DELAY100us(int);

void main(){
	while(1){
		keyscan();
	}
}
//=== 4x4鍵盤掃瞄函數 ===
void keyscan() {
	char X,Y,Ycode,Kcode,i;
	for(X=0;X<4;X++){			// 掃瞄4行
		seg7Output=0xff;				// 關閉顯示信號(防殘影)
		keyInput=SCAN_CODE[X];		// 輸出掃瞄信號
		seg7Output=seg7hexCode[DisplayData[X]];		// 輸出顯示信號
		Y=~keyInput & 0x0f;			// 讀取鍵盤	 
		if	(Y!=0){		    	// 若有按鍵被按下 
			if(Y==8) Ycode=0;	 
			else if (Y==4) Ycode=1; 
			else if (Y==2) Ycode=2; 
			else if (Y==1) Ycode=3; 
			Kcode=4*Ycode + X;		// 計算按鍵值
			for(i=0;i<3;i++)
				DisplayData[3-i]=DisplayData[2-i];// 顯示資料移位
			DisplayData[0]=Kcode;			// 將鍵值存入個位數
			BEEP(1);					// 嗶一聲 
			while(Y!=0) Y=~keyInput & 0x0f;// 等待放開按鍵
		}
		DELAY500us(4);					// 延遲2ms
	}
}

void DELAY500us(int time){
	int i,j;
	for(i = 0;i<time;i++)
		for(j=0;j<60;j++);//do nothing
}
void DELAY100us(int time){
	int i,j;
	for(i = 0;i<time;i++)
		for(j=0;j<12;j++);//do nothing
}
//==== 嗶聲函數 ========
void BEEP(char x) 
{	int	i,j;
	for(i=0;i<x;i++) 				// 嗶x聲
	{	for(j=0;j<100;j++)		// 重複吸放100次
		{	Buzzer=0;DELAY100us(1);// 蜂鳴器吸
			Buzzer=1;DELAY100us(1);// 蜂鳴器放
		} 
	 	DELAY500us(200);			// 靜音0.1秒
	} 
}