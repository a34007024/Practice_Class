#include	<reg51.h>	// 包含reg51.h標頭檔 
#define	LED	 P1			// 定義LED接至Port 1
sbit	load=P3^2;		// 定義load接腳的位址
//==主程式======================================
main()				
{	SCON=0x11;			// 設定為mode 0、REN=1、RI=1
	while(1)
	{	load=0;load=1;	// 產生負脈波
		RI=0;	 		// 清除RI旗標
		while(!RI);	 	// 等待串列輸入中斷(RI旗標=1)
		LED=SBUF;			// 將串列輸入反映到LED
	}
}
