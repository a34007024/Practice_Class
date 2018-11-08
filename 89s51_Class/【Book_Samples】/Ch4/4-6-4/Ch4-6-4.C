#include	<reg51.h>	// 包含reg51.h標頭檔 
#define	LED	 P1			// 定義LED接至Port 1
sfr	WDTRST=0xa6;		// 宣告WDTRST位址
#define	counts 142		// 定義追狗速度
#define	t0H (65536-1000)/256	// 定義T0計數起點之高8位元
#define	t0L (65536-1000)%256	// 宣告T0計數起點之高8位元
unsigned int x;  			// 宣告無號整數變數x(佔2Bytes)
void DELAY1ms(int);		// 宣告延遲函數
//==主程式======================================
main()					// 主程式開始 	
{	unsigned char i;	// 宣告無號數字元變數i(佔1Bytes)
	EA=ET0=PT0=1; 		// 設定Timer 0中斷
	TH0=t0H;			// 填入高8位元
	TL0=t0L;			// 填入低8位元
	TR0=1;				// 啟動Timer 0
	WDTRST = 0x1e;		// 啟用看門狗計時器
	WDTRST = 0xe1;		// 啟用看門狗計時器
	LED=0xfe;				// 初值=1111 1110,只有最右1燈亮	
	while(1)				// 無窮迴圈,程式一直跑 
	{	for(i=0;i<7;i++)	// 左移7次
		{	DELAY1ms(100);	// 延遲0.1s 
			LED=(LED<<1)|0x01;	// 左移1位,並設定最低位元為1 
		}			
		for(i=0;i<7;i++)	// 右移7次 
		{	DELAY1ms(100);	// 延遲0.1s 
			LED=(LED>>1)|0x80;	// 右移1位,並設定最高位元為1
		}		
	}			
}				
// === 延時函數 ===
void DELAY1ms(int x) 
{	int i,j;				// 宣告整數變數i,j 
	for(i=0;i<x;i++)		// 外迴圈,延遲x*ms 
		for(j=0;j<120;j++);	// 內迴圈，延遲1ms 
} 
// === Timer 0中斷副程式 ===
void  Feed(void)  interrupt 1	// 餵狗副程式開始 
{	TH0=t0H;			// 填入高8位元
	TL0=t0L;			// 填入低8位元
	// 軟體模擬：75以下ok, 76(含)以上追不上WDT
	// 硬體實驗：142以下 ok, 143(含)以上追不上WDT
	if (++x == counts)	
	{	x=0;			// 重新計數  
		WDTRST = 0x1e;	// 重置看門狗計時器 
		WDTRST = 0xe1;	// 重置看門狗計時器
	}
}				
