#include	<reg51.h>	// 包含reg51.h標頭檔 
#define	LED	 P1			// 定義LED接至Port 1
#define	counts	 50000	// 定義計數量(50000) 
#define t0H (65536-counts)/256	// 定義計數起點(TH) 
#define t0L (65536-counts)%256	// 定義計數起點(TL) 
sbit	load=P3^2;		// 定義load接腳的位址 
void 	DELAY1ms(int);		// 宣告延遲函數
//==主程式======================================
main()				
{	EA=ES=ET0=1;		// 設定T0,ES中斷
	TH0=t0H;TL0=t0L;	// 填入計數量起點 
	TMOD=0x01;			// 設定Timer 0為Mode 1 
	TR0=1;				// 啟動Timer 0 
	SCON=0x11;			// 設定為mode 0、REN=1、RI=1
	while(1) 
	{	LED=~LED;		// LED交互閃爍
		DELAY1ms(250);
	}
}
void T0_int(void) interrupt 1
{	TH0=t0H;TL0=t0L;	// 填入計數量起點 
	load=0;load=1;		// 產生負脈波 
}
void ES_int(void) interrupt 4
{	LED=SBUF;			// 將串列輸入反映到LED
	RI=0;	 			// 清除RI旗標
}
void 	DELAY1ms(int x)
{	int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<120;j++);
}

