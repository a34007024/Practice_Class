#include	<reg51.h>			// 包含reg51.h標頭檔  
#define	wait  20				// 定義防彈跳延遲時間(ms) 
#define	LED  P1					// 定義LED連接到Port 1 
sbit	PB=P2^0;				// 宣告按鈕開關位址 
void	DELAY1ms(int);			// 宣告延時函數 
sbit	Buzzer=	P3^7;			// 宣告蜂鳴器位址 
void	BEEP(char);				// 宣告嗶聲函數 
void	DELAY500us(int);		// 宣告0.5ms延時函數 
//==== 主程式 =========================================
main()		 
{	PB=1;						// 初始化 
	LED=0xff;					// 初始化 
	while(1)					// 無窮盡迴圈 
	{	if (!PB)				// 偵測PB按鈕開關 
		{	BEEP(1);			// 以嗶聲代替按下防彈跳
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
//==== 嗶聲函數 ==============================
void	BEEP(char x)
{	char i,j;
	for(i=0;i<x;i++)		// 產生x聲  
	{	for(j=0;j<100;j++)// 蜂鳴器吸放100次  
		{	Buzzer=0;DELAY500us(1); // 蜂鳴器吸0.5ms  
			Buzzer=1;DELAY500us(1); // 蜂鳴器放0.5ms
		}
		DELAY500us(200); // 蜂鳴器靜音0.1秒(0.5ms*200)  
	}
}
//==== 延時函數(0.5ms) ==============================
void	DELAY500us(int x) 
{	int	i,j;
	for(i=0;i<x;i++) 			// 外迴圈(0.5ms*x)
		for(j=0;j<60;j++);	// 內迴圈(0.5ms)
}
