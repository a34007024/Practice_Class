#include	<reg51.h>			// 包含reg51.h標頭檔  
#define	SEGP  P0				// 定義顯示信號埠 
#define	SCANP P2				// 定義掃瞄信號埠 
void	display(void);			// 宣告掃瞄函數 
void	DELAY1ms(int);			// 宣告延時函數 
// 七節顯示器編碼表
char code TAB[10]={	0xc0,0xf9,0xa4,0xb0,0x99,
					0x92,0x83,0xf8,0x80,0x98};	
// 低態驅動掃瞄碼
char code SCAN_CODE[8]={0x7f,0xbf,0xdf,0xef,
						0xf7,0xfb,0xfd,0xfe };	
// 顯示資料
char code DISP[8]={2,0,1,2,0,1,2,3};
//==== 主程式 =========================================
main()		 
{	char i;							// 宣告變數 
	while(1)						// 無窮盡迴圈 
	{	for(i=0;i<64;i++)			// 呼叫掃瞄函數64次 
			display();				// 約16ms*64=0.5s
		{	SEGP=0xff;					// 關閉顯示信號
			DELAY1ms(480);				// 延遲0.48s(滅)
			display();					// 呼叫掃瞄函數(顯示0.48秒)
		}
	}
}
//=== 八位掃瞄函數 ===
void	display(void) 	
{	char i,j;
	for(i=0;i<30;i++)			// 重複掃瞄30次
	{	for(j=0;j<8;j++)		// 每次掃瞄4個字
		{	SCANP=0xff;			// 關閉掃瞄線(防殘影)
			SEGP=TAB[DISP[j]];	//輸出顯示信號
			SCANP=SCAN_CODE[j];	// 輸出掃瞄信號
			DELAY1ms(2);		// 延遲2ms(顯示)
		}
	}
}
//==== 延時函數(1ms) ==============================
void DELAY1ms(int x) 
{	int	i,j;
	for(i=0;i<x;i++) 			// 外迴圈(1ms*x)
		for(j=0;j<120;j++);		// 內迴圈(1ms)
}
