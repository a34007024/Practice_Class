#include	<reg51.h>	// 包含reg51.h標頭檔 
#define	LED	 P1			// 定義LED接至Port 1
sbit	PB=P2^0;		// 宣告按鈕開關位址 
char	pat=0x0f;		// 宣告開關信號變數  
void	wait(void);		// 宣告防彈跳函數 
void	LEFT(void);		// 宣告單燈左移函數
void	RIGHT(void);	// 宣告單燈右移函數
void	DELAY1ms(int);	// 宣告延時函數
//==主程式======================================
main()				
{	PB=1; 				// 設定PB為輸入埠
	PCON|=0x80;			// 將SMOD位元設定為1
	SCON=0x90;			// 將串列埠採mode 2
	while(1)
	{	if (!PB) 		// 若開關按下 
		{	wait();		// 防彈跳   		
			while(!PB);	// 等待開關放開 
			wait();		// 防彈跳   		
			SBUF=pat;	// 輸出指令 
			pat=~pat;	// 切換狀態 
		}
		while(!RI);		// 等待接收完成
		RI=TI=0;		// 清除RI,TI旗標(重傳)
		if (SBUF==0x0f) LEFT();	// 若接收到的單燈左移指令，則執行單燈左移 
		if (SBUF==0xf0) RIGHT();// 若接收到的單燈右移指令，則執行單燈右移 
	} 
} 
//====================================
void	wait(void)
{	char i,j;
	for(i=0;i<30;i++)
		for(j=0;j<120;j++);
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
