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
char seg7hexCode[20] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98,0xa0,0x83,0xa7,0xa1,0x86,0x8e,0xf7};
char SCAN_CODE[8]={	0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe };	
char DisplayData[4]={16,16,16,16};
char password[4] = {0,0,0,0};
char keyPressCount = 0;
char check;
void DELAY500us(int);
void keyscan();
void BEEP(char);
void DELAY100us(int);

void main(){
	while(1){
		keyscan();
		if(keyPressCount==4){
			keyPressCount = 0;
			for(check=0;check<4;check++){
				if(DisplayData[check]==password[check])
					BEEP(3);
				else{
					BEEP(5);
					seg7Output=0xff;// 關閉顯示信號
				}
			}
		}
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
			keyPressCount += 1;
			if(Y==1) Ycode=0;		// 第0列有按鍵按下 
			else if (Y==2) Ycode=1;	// 第1列有按鍵按下 
			else if (Y==4) Ycode=2;	// 第2列有按鍵按下 
			else if (Y==8) Ycode=3;	// 第3列有按鍵按下 
			Kcode=4*X + Ycode;		// 計算按鍵值
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