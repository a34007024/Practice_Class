#include	<reg51.h>				// 包含reg51.h標頭檔  
#define	LED  P1					// 定義LED連接到Port 1 
sbit	ON=P2^0;				// 宣告ON開關位址 
sbit	OFF=P2^1;				// 宣告OFF開關位址 
//==== 主程式 =========================================
main()		 
{	ON=OFF=1;						// 初始化 
	LED=0xff;						// 初始化 
	while(1)						// 無窮盡迴圈 
	{	if (!OFF) LED=0xff;		// 偵測OFF開關 
		else if (!ON) LED=0;		// 偵測OFF開關
	}
}
