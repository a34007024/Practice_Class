#include	<reg51.h>		// 包含reg51.h標頭檔 
#define	SW	 P0			// 定義SW接至Port 0
#define	LED	 P1			// 定義LED接至Port 1
//==主程式======================================
main()				
{	SW=0xff; 				// 設定SW輸入埠
	EA=ES=1;				// 設定串列埠中斷
	SBUF=SW;				// 將SW的值透過串列埠輸出
	SCON=0;					// 設定為mode 0、REN=0、TI=0
	while(1) LED=SW;		// 將SW狀態反映在LED
}
// ===================================
void ES_int(void) interrupt 4
{	SBUF=SW; 		 	// 將SW的值透過串列埠輸出
	TI=0; 		 		// 清除TI旗標
}
