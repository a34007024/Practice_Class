#include	<reg51.h>	// 包含reg51.h標頭檔
#define	LED	 P1			// 定義LED接至Port 1
void DELAY500us(int);	// 宣告延遲函數 
void LEFT(char);		// 宣告單燈左移函數
void RIGHT(char);		// 宣告單燈右移函數
void BEEP(char);		// 宣告嗶聲函數
sbit Buzzer=P3^7;		// 宣告蜂鳴器位址 
//==主程式================================
main()				 
{	IE=0x85;		//	啟用INT 0,INT 1中斷(0x85=10000101)
	IP=0x01;		//	設定高優先等級
	LED=0;			//	初值(LED全亮)	
	while(1)				//	無窮迴圈,程式一直跑 
	{	DELAY500us(500);	//	延遲0.25秒 
		LED=~LED;			//	LED反相
		BEEP(1);			// 嗶一聲 
	}			
}				
// === INT 0的中斷副程式 - 單燈左移1圈 ===
void int0_LEFT(void) interrupt 0 using 1	
{	unsigned saveLED=LED;	// 儲存中斷前LED狀態
	LEFT(3);					// 單燈左移3圈
	LED=saveLED;				// 恢復中斷前LED狀態
}	
// === INT 1中斷副程式 - 單燈右移1圈 ===
void int1_RIGHT(void) interrupt 2 using 2 
{	unsigned saveLED=LED;		// 儲存中斷前LED狀態
	RIGHT(3);					// 單燈右移3圈
	LED=saveLED;				// 恢復中斷前LED狀態
}	
// === 延時函數(500us) ===
void DELAY500us(int x) 
{	int i,j;					// 宣告整數變數i,j 
	for (i=0;i<x;i++)			// 外迴圈 
		for (j=0;j<60;j++);		// 內迴圈 
}					
// === 單燈左移函數 ==
void LEFT(char x)
{	char i, j;				// 宣告變數i,j
	for(i=0;i<x;i++)		// i迴圈,執行x圈 
	{	LED=0xfe;			// 初始狀態=1111 1110,最右燈亮
		for(j=0;j<7;j++)	//	j迴圈,左移7次
		{	DELAY500us(500);		//	延遲500 0.5m=0.25s
			LED=(LED<<1)|0x01; 	//	左移1位後,LSB設為1
		}			
		DELAY500us(500);	//	延遲0.25s
	}	
}		
// === 單燈右移函數 ===
void RIGHT(char x) 	
{	char i, j;				// 宣告變數i,j
	for(i=0;i<x;i++)		// i迴圈,執行x圈 
	{	LED=0x7f;			// 初始狀態=0111 1111,最左燈亮
		for(j=0;j<7;j++)	//	j迴圈,右移7次
		{	DELAY500us(500);	//	延遲500 0.5m=0.25s
			LED=(LED>>1)|0x80; 	//	右移1位後,MSB設為1
		}			
		DELAY500us(500);	//	延遲0.25s
	}	
}		
// === 嗶聲函數 ===
void BEEP(char x) 
{	int	i,j;
	for(i=0;i<x;i++) 				// 嗶x聲
	{	for(j=0;j<100;j++)		// 重複吸放100次
		{	Buzzer=0;DELAY500us(1);// 蜂鳴器吸
			Buzzer=1;DELAY500us(1);// 蜂鳴器放
		} 
	 	DELAY500us(200);			// 靜音0.1秒
	} 
}
