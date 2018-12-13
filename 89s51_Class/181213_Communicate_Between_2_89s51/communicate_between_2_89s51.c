#include	<reg51.h>		// 包含reg51.h標頭檔 
#define	SW	 P0			// 定義SW接至Port 0
#define	LED	 P1			// 定義LED接至Port 1
//==主程式======================================
main()				
{	SW=0xff; 				// 設定SW輸入埠
	PCON|=0x80;			// 將SMOD位元設定為1
	SCON=0x90;				// 將串列埠採mode 2
	while(1)
	{	SBUF=SW;			// 將SW的值透過串列埠輸出
		while(!RI);		// 等待接收完成
		LED=SBUF;			// 將接收到的資料反映到LED
		RI=TI=0;			// 清除RI,TI旗標(重傳)
	} 
} 
