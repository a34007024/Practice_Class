#include	<reg51.h>		// 包含reg51.h標頭檔 
#define	LED	 P1				// 定義LED接至Port 1
void	FLASH(char);		// 宣告閃爍函數
void	LEFT(void);			// 宣告單燈左移函數
void	RIGHT(void);		// 宣告單燈右移函數
void	DELAY1ms(int);		// 宣告延時函數
//==主程式======================================
main()				
{	char RevChar;			// 宣告變數
	TMOD |= 0x20;			// 設定Timer 1採Mode 2
	PCON &= 0x7f;			// 設定SMOD=0
	TH1=TL1=0xfd;			// 填入計時量 
	TR1=1;					// 啟動Timer 1
	SCON=0x50;				// 設定串列埠採Mode 1
	while(1)
	{	while(!RI);			// 等待接收完成
		RevChar=(SBUF-0x30);// 將接收到的資料轉為數字 
		switch (RevChar)
		{	case 1:			// 閃爍指令 
			{	FLASH(3);
				break;
			}
			case 2:			// 單燈左移指令 
			{	LEFT();
				break;
			}
			case 3:			// 單燈右移指令 
			{	RIGHT();
				break;
			}
		}
		RI=0;			// 清除RI旗標(重新接收)
	} 
} 
//====================================
void	FLASH(char x)
{	char i;
	LED=0xff;
	for(i=0;i<x;i++)
	{	DELAY1ms(100);
		LED=0;
		DELAY1ms(100);
		LED=0xff;
	}	
}
//====================================
void	LEFT(void)
{	char i;
	LED=0xfe;
	for(i=0;i<7;i++)
	{	DELAY1ms(100);
		LED=(LED<<1)|0x01;
	}
	DELAY1ms(100);LED=0xff;
}
//====================================
void	RIGHT(void)
{	char i;
	LED=0x7f;
	for(i=0;i<7;i++)
	{	DELAY1ms(100);
		LED=(LED>>1)|0x80;
	}
	DELAY1ms(100);LED=0xff;
}
//====================================
void	DELAY1ms(int x)
{	char i,j;
	for(i=0;i<x;i++)
		for(j=0;j<120;j++);
}
