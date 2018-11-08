#include	<reg51.h>	// 包含reg51.h標頭檔
#define	LED	 P1
#define	seg7Scan	 P1			// 定義七段顯示器掃描訊號接至Port 1
#define seg7	P0	//七段顯示器的a b c ...接到P0
void delay(int);	
void left(char);		// 宣告單燈左移函數
void right(char);		// 宣告單燈右移函數
void BEEP(char);		// 宣告嗶聲函數
char seg7hexCode[20] = {0xc0,0xf9,0xa4,0xb0,0x99,
						0x92,0x82,0xf8,0x80,0x98};
						// 7-seg對應顯示輸出0~9
char seg7scanCode[8] = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
sbit Buzzer=P3^7;		// 宣告蜂鳴器位址 
int i=0;
int countNumber=0;
//==主程式================================
main()				 
{	IE=0x85;		//	啟用INT 0,INT 1中斷(0x85=10000101)
	IP=0x01;		//	設定高優先等級
	LED=0;			//	初值(LED全亮)	
	while(1){				//	無窮迴圈,程式一直跑 	
		seg7Scan = seg7scanCode[7];//固定最後一個seg7顯示
		seg7 = seg7hexCode[countNumber];
		delay(1000);
		if(countNumber < 9)countNumber += 1;
		else countNumber = 0;
		//BEEP(1);			// 嗶1聲 
	}			
}
void int0_blink0() interrupt 0 using 1{
	int owo;
	for(owo=0;owo<3;owo++){
		seg7Scan = seg7scanCode[7];
		seg7 = seg7hexCode[0];
		delay(300);
		seg7 = 0xff;//turn off
		delay(300);
	}
	seg7 = seg7hexCode[countNumber];
}	
/*
// === INT 0的中斷副程式 - 單燈左移1圈 ===
void int0_left(void) interrupt 0 using 1	
{	unsigned saveLED=LED;	// 儲存中斷前LED狀態
	left(3);					// 單燈左移3圈
	LED=saveLED;				// 恢復中斷前LED狀態
}
// === INT 1中斷副程式 - 單燈右移1圈 ===
void int1_right(void) interrupt 2 using 2 
{	unsigned saveLED=LED;		// 儲存中斷前LED狀態
	right(3);					// 單燈右移3圈
	LED=saveLED;				// 恢復中斷前LED狀態
}	
*/

void delay(int ms) 
{	int i,j;		
	for (i=0;i<ms;i++)	
		for (j=0;j<120;j++);	
}					
// === 單燈左移函數 ==
void left(char x)
{	char i, j;				// 宣告變數i,j
	for(i=0;i<x;i++)		// i迴圈,執行x圈 
	{	LED=0xfe;			// 初始狀態=1111 1110,最右燈亮
		for(j=0;j<7;j++)	//	j迴圈,左移7次
		{	delay(500);		//	延遲500 0.5m=0.25s
			LED=(LED<<1)|0x01; 	//	左移1位後,LSB設為1
		}			
		delay(500);	//	延遲0.25s
	}	
}		
// === 單燈右移函數 ===
void right(char x) 	
{	char i, j;				// 宣告變數i,j
	for(i=0;i<x;i++)		// i迴圈,執行x圈 
	{	LED=0x7f;			// 初始狀態=0111 1111,最左燈亮
		for(j=0;j<7;j++)	//	j迴圈,右移7次
		{	delay(500);	//	延遲500 0.5m=0.25s
			LED=(LED>>1)|0x80; 	//	右移1位後,MSB設為1
		}			
		delay(500);	//	延遲0.25s
	}	
}		
// === 嗶聲函數 ===
void BEEP(char x) 
{	int	i,j;
	for(i=0;i<x;i++) 				// 嗶x聲
	{	for(j=0;j<100;j++)		// 重複吸放100次
		{	Buzzer=0;delay(1);// 蜂鳴器吸
			Buzzer=1;delay(1);// 蜂鳴器放
		} 
	 	delay(200);			// 靜音0.1秒
	} 
}
