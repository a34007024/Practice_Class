#include	<reg51.h>	 
#define	SEGP  P0	
#define	KEYP P2			
void	keyscan();	
void	DELAY500us(int);
void	BEEP(char);	
sbit	Buzzer=P3^7;
// 七段顯示器編碼表
char seg7hexCode[20] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98,0xa0,0x83,0xa7,0xa1,0x84,0x8e,0xff};	
// 低態驅動掃瞄碼
char SCAN_CODE[8]={	0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe };	
char DISP[4]={16,16,16,16};
// 顯示資料，初值為空白 

//==== 主程式 ============
void main()		 
{	while(1)
	keyscan();//呼叫鍵盤掃瞄函數 
}
//=== 4 4鍵盤掃瞄函數 ===
void keyscan(void) 
{	char X,Y,Ycode,Kcode,i;
	for(X=0;X<4;X++)			// 掃瞄4行
	{	SEGP=0xff;				// 關閉顯示信號(防殘影)
		KEYP=SCAN_CODE[X];		// 輸出掃瞄信號
		SEGP=TAB[DISP[X]];		// 輸出顯示信號
		Y=~KEYP & 0x0f;			// 讀取鍵盤	 
		if	(Y!=0)		    	// 若有按鍵被按下 
		{	if(Y==1) Ycode=0;		// 第0列有按鍵按下 
			else if (Y==2) Ycode=1;	// 第1列有按鍵按下 
			else if (Y==4) Ycode=2;	// 第2列有按鍵按下 
			else if (Y==8) Ycode=3;	// 第3列有按鍵按下 
			Kcode=4*X + Ycode;		// 計算按鍵值
			for(i=0;i<3;i++)
				DISP[3-i]=DISP[2-i];// 顯示資料移位
			DISP[0]=Kcode;			// 將鍵值存入個位數
			BEEP(1);					// 嗶一聲 
			while(Y!=0) Y=~KEYP & 0x0f;// 等待放開按鍵
		}
		DELAY500us(4);					// 延遲2ms
	}
}
//==== 延時函數(0.5ms) ==============================
void DELAY500us(int x) 
{	int	i,j;
	for(i=0;i<x;i++)
		for(j=0;j<60;j++);
}
//==== 嗶聲函數 ========
void BEEP(char x) 
{	int	i,j;
	for(i=0;i<x;i++) 				// 嗶x聲
	{	for(j=0;j<100;j++)		// 重複吸放100次
		{	Buzzer=0;DELAY500us(1);// 蜂鳴器吸
			Buzzer=1;DELAY500us(1);// 蜂鳴器放
		} 
	 	DELAY500us(200);			// 靜音0.1秒
	} 
}
