#include	<reg51.h>		// 包含reg51.h標頭檔  
#define	SEGP  P0			// 定義顯示信號埠 
#define	SCANP P1			// 定義掃瞄埠 
#define	KEYP  P2			// 定義鍵盤埠 
#define	count0 250			// 預設計數量(0.25ms)
char	int0_CNT=0; 		// 宣告預設中斷重複次數
char	SEGX=0; 			// 宣告掃瞄指標
void	keyscan(void);		// 宣告鍵盤掃瞄函數 
void	DELAY500us(int);	// 宣告延時函數 
void	BEEP(char);			// 宣告嗶聲函數 
sbit	Buzzer=P3^7;		// 宣告蜂鳴器位址
// 七節顯示器編碼表
char code TAB[11]={	0xc0,0xf9,0xa4,0xb0,0x99,
					0x92,0x82,0xf8,0x80,0x98, 0xff};	
// 低態驅動掃瞄碼 
char code SCAN_CODE[8]={0x7f,0xbf,0xdf,0xef,
						0xf7,0xfb,0xfd,0xfe };	
// 顯示資料
char DISP[8]={0,10,10,10, 10,10,10,10};// 初值為0 
//==== 主程式 =========================================
main()		 
{	IE=0x82;				// 啟用Timer 0中斷  
	TMOD=0x02;				// 設定Timer 0為Mode 2 
	TH0=TL0=256-count0;		// 設置計數量 
	TR0=1;					// 啟動Timer 0(開始計時) 
	while(1) keyscan();		// 呼叫鍵盤掃瞄函數 
}
//=== 八位七節顯示器掃瞄中斷副程式(T0) ===
void segscan(void) interrupt 1 using 1	
{	if (++int0_CNT==4)			// 中斷次數超過4次(即1ms)
	{	int0_CNT=0; 			// 中斷次數歸零 
		if (++SEGX==8) SEGX=0;	// 調整掃瞄指標
		SEGP=0xff;				// 關閉顯示信號(防殘影)
		SCANP=SCAN_CODE[7-SEGX];// 輸出掃瞄信號
		SEGP=TAB[DISP[SEGX]];	// 輸出顯示信號
	}	
}	
//=== 4 4鍵盤掃瞄函數 ===
void keyscan(void) 	
{	char X,Y, Ycode,Kcode,i;
	for(X=0;X<4;X++)			// 掃瞄4行
	{	KEYP=SCAN_CODE[X];		// 輸出掃瞄信號
		Y=~KEYP & 0x0f;			// 讀取鍵盤 
		if	(Y!=0)		    	// 若有按鍵被按下 
		{	if(Y==1) Ycode=0;	// 第0列有按鍵按下 
			else if (Y==2) Ycode=1;	// 第1列有按鍵按下 
			else if (Y==4) Ycode=2;	// 第2列有按鍵按下  
			else if (Y==8) Ycode=3;	// 第3列有按鍵按下 
			Kcode=4*X + Ycode;		// 計算按鍵值
			if (Kcode<10 && Kcode>=0)	// 偵測數值鍵
			{	for(i=0;i<7;i++)	
					DISP[7-i]=DISP[6-i];// 顯示資料移位
				DISP[0]=Kcode;			// 將鍵值存入個位數
			}
			BEEP(1);					// 嗶一聲 
			while(Y!=0) Y=~KEYP & 0x0f;	// 等待放開按鍵
			DELAY500us(2);				// 延遲1ms
		}
	}
}
//==== 延時函數(0.5ms) ==============================
void DELAY500us(int x) 
{	int	i,j;
	for(i=0;i<x;i++) 			// 外迴圈(0.5ms*x)
		for(j=0;j<60;j++);		// 內迴圈(0.5ms)
}
//==== 嗶聲函數 ==============================
void BEEP(char x) 
{	int	i,j;
	for(i=0;i<x;i++) 			// 嗶x聲 
	{	for(j=0;j<100;j++)		// 重複吸放100次
		{	Buzzer=0;DELAY500us(1);// 蜂鳴器吸 
			Buzzer=1;DELAY500us(1);// 蜂鳴器放
		} 
	 	DELAY500us(200);		// 靜音0.1秒
	} 
}
