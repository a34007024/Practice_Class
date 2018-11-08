#include	<reg51.h>			// 包含reg51.h標頭檔  
#define	LED  P1					// 定義LED連接到Port 1 
#define	DIP_SW  P0				// 定義指撥開關連接到Port 0 
#define	Read_SW ~DIP_SW&0x03	// 定義篩選bit0與bit1 
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
			{	LED=0xf0;			// LED高四位元滅、高四位元亮  
				break;				// 跳出 
			}
			case 2:					// 若bit1=1、bit0=0
			{	LED=0x0f;			// LED高四位元亮、高四位元滅 
				break;				// 跳出	    
			}
			case 3:					// 若bit1=1、bit0=1
			{	LED=0;				// LED全亮 
				break;				// 跳出 
			}
		}
	}
}
