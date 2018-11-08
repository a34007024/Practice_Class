#include	<reg51.h>				// 包含reg51.h標頭檔  
#define	LED  P1						// 定義LED連接到Port 1 
sbit	Buzzer=	P3^7;				// 宣告蜂鳴器位址 
void	BEEP(char);					// 宣告嗶聲函數 
void	DELAY500us(int);			// 宣告0.5ms延時函數 
void	DELAY1ms(int);				// 宣告1ms延時函數 
void	LEFT(char);					// 宣告單燈左移函數 
void	RIGHT(char);				// 宣告單燈右移函數 
//==== 主程式 =========================================
main()		 
{	while(1)						// 無窮盡迴圈 
	{	LEFT(1);BEEP(1);			// 單燈左移一圈 
		RIGHT(1);BEEP(2);			// 單燈右移一圈 
	}
}
//==== 單燈左移函數 ==============================
void	LEFT(char x)
{	char i,j;
	for(i=0;i<x;i++)		// 產生x圈單燈左移  
	{	LED=0xfe;			// 設定單燈左移初值0xfe=1111 1110 
		for(j=0;j<7;j++)	// 移位7次
		{	DELAY1ms(100);	// 延遲0.1秒(即顯示0.1秒)  
			LED=(LED<<1)|1;// LED左移一位，而最右邊強制為1
		}
		DELAY1ms(100); 		// 延遲0.1秒(即顯示0.1秒) 
	}
}
//==== 單燈右移函數 ==============================
void	RIGHT(char x)
{	char i,j;
	for(i=0;i<x;i++)		// 產生x圈單燈右移  
	{	LED=0x7f;			// 設定單燈右移初值0x7f=0111 1111 
		for(j=0;j<7;j++)	// 移位7次  
		{	DELAY1ms(100);	// 延遲0.1秒(即顯示0.1秒)  
			LED=(LED>>1)|0x80;// LED右移一位，而最左邊強制為1
		}
		DELAY1ms(100); 		// 延遲0.1秒(即顯示0.1秒) 
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
	for(i=0;i<x;i++)			// 產生x聲  
	{	for(j=0;j<100;j++)		// 蜂鳴器吸放100次  
		{	Buzzer=0;DELAY500us(1); // 蜂鳴器吸0.5ms  
			Buzzer=1;DELAY500us(1); // 蜂鳴器放0.5ms
		}
		DELAY500us(200); 		// 蜂鳴器靜音0.1秒(0.5ms*200)  
	}
}
//==== 延時函數(0.5ms) ==============================
void	DELAY500us(int x) 
{	int	i,j;
	for(i=0;i<x;i++) 			// 外迴圈(0.5ms*x)
		for(j=0;j<60;j++);		// 內迴圈(0.5ms)
}
