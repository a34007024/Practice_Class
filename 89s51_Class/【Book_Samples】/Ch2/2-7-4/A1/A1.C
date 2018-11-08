#include	<reg51.h>		// 包含reg51.h標頭檔  
sbit	OFF=P2^0;			// 宣告OFF開關位址 
sbit	FORWARD=P2^1;		// 宣告正轉按鈕開關位址 
sbit	REVERSE=P2^2;		// 宣告反轉按鈕開關位址 
sbit	MS_F=P1^0;			// 宣告正轉線圈位址 
sbit	MS_R=P1^1;			// 宣告反轉線圈位址 
//==== 主程式 =========================================
main()		 
{	OFF=FORWARD=REVERSE=1;		// 初始化 
	MS_F=MS_R=1;				// 初始化(關閉電磁開關線圈) 
	while(1)					// 無窮盡迴圈 
	{	if (!OFF) MS_F=MS_R=1;				// 偵測OFF開關 
		else if (!FORWARD && MS_R) MS_F=0;	// 偵測正轉按鈕開關  
		else if (!REVERSE && MS_F) MS_R=0;	// 偵測反轉按鈕開關  
	}
}
