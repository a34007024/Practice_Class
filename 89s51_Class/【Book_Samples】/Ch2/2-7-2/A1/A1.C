#include	<reg51.h>			// 包含reg51.h標頭檔  
#define	LED  P1					// 定義LED連接到Port 1 
sbit	PB = P2^0;				// 宣告按鈕開關位址 
void	DELAY1ms(int);			// 宣告1ms延時函數 
void	LEFT(char);				// 宣告雙燈左移函數
void	FLASH(char);			// 宣告8燈閃爍函數
//==== 主程式 =========================================
main()		 
{	LED=0xff;						// 初始設定(LED全滅)
	PB=1;							// 按鈕設定為輸入埠
	while(1)						// 無窮盡迴圈
		while(!PB)					// 若按下PB函數
		{	LEFT(1);				// 單燈左移一圈
			FLASH(3);				// 8燈閃爍一次
		}
}
//==== 單燈左移函數 ==============================
void	LEFT(char x)
{	char i,j;
	for(i=0;i<x;i++)		// 產生x圈單燈左移  
	{	LED=0xfc;			// 設定單燈雙移初值0xfc=1111 1100 
		for(j=0;j<6;j++)	// 移位7次  
		{	DELAY1ms(100);	// 延遲0.1秒(即顯示0.1秒)  
			LED=(LED<<1)|1;	// LED左移一位，而最右邊強制為1
		}
		DELAY1ms(100); 		// 延遲0.1秒(即顯示0.1秒) 
	}
}
//==== 8燈閃爍函數 ==============================
void	FLASH(char x)
{	char i;
	for(i=0;i<x;i++)
	{	LED=0; DELAY1ms(100);		// 8燈全亮0.1秒
		LED=0xff; DELAY1ms(100);	// 8燈全滅0.1秒
	}
}
//==== 延時函數(1ms) ==============================
void	DELAY1ms(int x) 
{	int	i,j;
	for(i=0;i<x;i++) 			// 外迴圈(1ms*x)
		for(j=0;j<120;j++);		// 內迴圈(1ms)
}
