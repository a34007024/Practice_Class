#include	<reg51.h>		// 包含reg51.h標頭檔 
#define	SW	 P0			// 定義SW接至Port 0
#define	LED	 P1			// 定義LED接至Port 1
//==主程式======================================
main()				
{	SW=0xff; 				// 設定SW輸入埠
	TMOD |= 0x20;			// 設定Timer 1採Mode 2
	PCON &= 0x7f;			// 設定SMOD=0
	TH1=TL1=0xfd;			// 填入計時量 
	TR1=1;					// 啟動Timer 1
	SCON=0x50;				// 設定串列埠採Mode 1
	while(1)
	{	SBUF=SW;			// 將SW的值透過串列埠輸出
		while(!RI);			// 等待接收完成
		LED=SBUF;			// 將接收到的資料，反映到LED
		TI=RI=0;			// 清除RI,TI旗標(重傳)
	} 
} 
