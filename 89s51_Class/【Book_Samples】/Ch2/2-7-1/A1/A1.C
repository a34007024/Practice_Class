#include	<reg51.h>		// 包含reg51.h標頭檔  
sbit	DIP_SW=P0^0;		// 宣告指撥開關位址  
sbit	Buzzer=	P3^7;		// 宣告蜂鳴器位址 
void	BEEP(unsigned char);		// 宣告嗶聲函數 
void	DELAY250us(int);	// 宣告0.25ms延時函數 
//==== 主程式 =========================================
main()		 
{	DIP_SW=Buzzer=1;			// 初始設定 
	while(1)					// 無窮盡迴圈
		while(!DIP_SW) BEEP(1);	// 若DIP_SW=0，則呼叫嗶聲函數
}
//==== 嗶聲函數 ==============================
void	BEEP(unsigned char x)
{	unsigned char i,j;
	for(i=0;i<x;i++)		// 產生x聲  
	{	for(j=0;j<200;j++)	// 蜂鳴器吸放200次  
		{	Buzzer=0;DELAY250us(1); // 蜂鳴器吸0.25ms  
			Buzzer=1;DELAY250us(1); // 蜂鳴器放0.25ms
		}
		DELAY250us(400); 	// 蜂鳴器靜音0.1秒(0.25ms*400)  
	}
}
//==== 延時函數(0.25ms) ==============================
void	DELAY250us(int x) 
{	int	i,j;
	for(i=0;i<x;i++) 		// 外迴圈(0.25ms*x)
		for(j=0;j<30;j++);	// 內迴圈(0.25ms)
}
