#include	<reg51.h>			// 包含reg51.h標頭檔  
#define	wait  20				// 定義防彈跳延遲時間(ms) 
#define	LED  P1					// 定義LED連接到Port 1 
sbit	PB=P2^0;				// 宣告按鈕開關位址 
void	DELAY1ms(int);			// 宣告延時函數 
//==== 主程式 =========================================
main()		 
{	PB=1;						// 初始化 
	LED=0xff;					// 初始化 
	while(1)					// 無窮盡迴圈 
	{	if (!PB)				// 偵測PB按鈕開關 
		{	DELAY1ms(wait);		// 延遲wait ms(按下防彈跳)
			while (!PB);		// 偵測PB按鈕開關按住不放
			LED=~LED;			// PB按鈕開關放開後動作
			DELAY1ms(wait);		// 延遲wait ms(放開防彈跳)
		}
	}
}
//==== 延時函數(1ms) ==============================
void	DELAY1ms(int x) 
{	int	i,j;
	for(i=0;i<x;i++) 			// 外迴圈(1ms*x)
		for(j=0;j<120;j++);		// 內迴圈(1ms)
}
