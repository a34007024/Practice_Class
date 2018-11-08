#include	<reg51.h>		// 包含reg51.h標頭檔 
#define	SW	 P0			// 定義SW接至Port 0
#define	LED	 P1			// 定義LED接至Port 1
void LEFT(void);		// 宣告LEFT函數  
void DELAY1ms(int);		// 宣告延時函數  
//==主程式======================================
main()				
{	SW=0xff; 				// 設定SW輸入埠
	EA=ES=1;				// 設定串列埠中斷
	SBUF=SW;				// 將SW的值透過串列埠輸出
	SCON=0;					// 設定為mode 0、REN=0、TI=0
	while(1) LEFT();		// 單燈左移 
}
// ===================================
void ES_int(void) interrupt 4
{	SBUF=SW; 		 	// 將SW的值透過串列埠輸出
	TI=0; 		 		// 清除TI旗標
}
// ===================================
void LEFT(void) 
{	char i;
	LED=0xfe;			// 單燈左移初值 
	for(i=0;i<7;i++)
	{	DELAY1ms(100);	// 延遲100ms
		LED=(LED<<1)|1; // 單燈左移
	}
	DELAY1ms(100);	// 延遲100ms
} 
// ===================================
void DELAY1ms(int x)  
{	int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<120;j++);
}