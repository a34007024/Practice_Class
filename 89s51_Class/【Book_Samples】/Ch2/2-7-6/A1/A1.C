#include	<reg51.h>			// 包含reg51.h標頭檔  
#define	LED  P1					// 定義LED連接到Port 1 
#define	DIP_SW  P0				// 定義指撥開關連接到Port 0 
#define	Read_SW ~DIP_SW&0x03	// 定義篩選bit0與bit1 
void	DELAY1ms(int);			// 宣告1ms延時函數 
void	LEFT(char);			// 宣告單燈左移函數 
void	RIGHT(char);			// 宣告單燈右移函數 
//==== 主程式 =========================================
main()		 
{	DIP_SW=0xff;					// 初始化 
	LED=0xff;						// 初始化 
	while(1)						// 無窮盡迴圈 
	{	switch (Read_SW)			// 讀取指撥開關 
		{	case 0:					// 若bit1=0、bit0=0
			{	LED=0xff;			// 關閉LED
				break;				// 跳出 
			}
			case 1:					// 若bit1=0、bit0=1
			{	LEFT(1);			// LED單燈左移  
				break;				// 跳出 
			}
			case 2:					// 若bit1=1、bit0=0
			{	RIGHT(1);			// LED單燈右移  
				break;				// 跳出	    
			}
			case 3:					// 若bit1=1、bit0=1
			{	LEFT(1);			// LED單燈左移  
				RIGHT(1);			// LED單燈右移   
				break;				// 跳出 
			}
		}
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
		DELAY1ms(100); 	// 延遲0.1秒(即顯示0.1秒) 
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
		DELAY1ms(100); 	// 延遲0.1秒(即顯示0.1秒) 
	}
}
//==== 延時函數(1ms) ==============================
void	DELAY1ms(int x) 
{	int	i,j;
	for(i=0;i<x;i++) 			// 外迴圈(1ms*x)
		for(j=0;j<120;j++);	// 內迴圈(1ms)
}
