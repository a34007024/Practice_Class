#include	<reg51.h>			// 包含reg51.h標頭檔  
#define	T1  10					// 定義第一段延遲時間(10s) 
#define	T2  3600				// 定義第二段延遲時間(1H=60*60s) 
#define	LED  P1					// 定義LED連接到Port 1 
sbit	PB=P2^0;				// 宣告按鈕開關位址 
void	DELAY1s(int);			// 宣告延時函數 
//==== 主程式 =========================================
main()		 
{	PB=1;							// 初始化 
	LED=0xff;						// 初始化 
	while(1)						// 無窮盡迴圈 
	{	if (!PB)					// 偵測PB按鈕開關 
		{	DELAY1s(T1);			// 延遲T1s
			LED=0;					// LED全亮 
			DELAY1s(T2);			// 延遲T2s
			LED=0xff;				// LED全滅 
		}
	}
}
//==== 延時函數(1s) ==============================
void	DELAY1s(int x) 
{	int	i,j,k;
	for(i=0;i<x;i++) 			// 外迴圈(1s*x)
		for(j=0;j<1000;j++)		// 中迴圈(1s)
			for(k=0;k<130;k++);	// 內迴圈(1ms)
}
