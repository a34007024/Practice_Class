#include <reg51.h>
#define	KEYP P2					// 定義鍵盤埠 
sbit Buzzer=P3^7;		// 宣告蜂鳴器位址 
unsigned int code BaseTone[8]={	// 宣告基本音階陣列
//  0	 1	 2	 3	 4	 5	 6	 7
	956,852,759,716,638,568,506,478};
// 低態驅動掃瞄碼
char code SCAN_CODE[8]={	0x7f,0xbf,0xdf,0xef,
								0xf7,0xfb,0xfd,0xfe };	
int t0H,t0L;			// 宣告變數
void DELAY1ms(int); 	// 宣告延時函數
void Sound(char);	// 宣告發音函數
int	keyscan();			// 宣告鍵盤掃瞄函數 
void	DELAY500us(int);		// 宣告延時函數 

void main()
{	Buzzer=1;	  		// 初始化
	IE=0x82;	  		// 啟用Timer 0中斷
	TMOD=TMOD|1;	  	// 設定Timer 0 Mode 1
	while(1)	  		// 無窮盡迴圈
	{
		keyscan();
	}
}
// ==================================================
void Sound(char x)
{	TH0=t0H=(65536-BaseTone[x])/256;
	// 載入所要播音階之高8位元
	TL0=t0L=(65536-BaseTone[x])%256;
	// 載入所要播音階之低8位元
	TR0=1;DELAY1ms(200);	// 發音
	TR0=0; 					// 停止發音
}
// ==================================================
void DELAY1ms(int x)
{	int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<120;j++);
}
// ==================================================
void TONE_int(void) interrupt 1
{	TH0=t0H; TL0=t0L;// 重新填入計時量
	Buzzer=!Buzzer; 	// 切換蜂鳴器
}
//=== 4 4鍵盤掃瞄函數 ===
int keyscan() 
{	char X,Y,Ycode,Kcode,i;
	for(X=0;X<4;X++)			// 掃瞄4行
	{	
		KEYP=SCAN_CODE[X];		// 輸出掃瞄信號
		Y=~KEYP & 0x0f;			// 讀取鍵盤	 
		if	(Y!=0)		    	// 若有按鍵被按下 
		{	if(Y==1) Ycode=0;		// 第0列有按鍵按下 
			else if (Y==2) Ycode=1;	// 第1列有按鍵按下 
			else if (Y==4) Ycode=2;	// 第2列有按鍵按下 
			else if (Y==8) Ycode=3;	// 第3列有按鍵按下 
			Kcode=4*X + Ycode;		// 計算按鍵值
			switch (Kcode)		// 讀取按鍵
			{	case 0:Sound(0);break;			// Do
				case 1:Sound(1);break;			// Re
				case 2:Sound(2);break;			// Mi
				case 3:Sound(3);break;			// Fa
				case 4:Sound(4);break;			// So
				case 5:Sound(5);break;			// La
				case 6:Sound(6);break;			// Si
				case 7:Sound(7);break;			// Do#
			}
			while(Y!=0) Y=~KEYP & 0x0f;// 等待放開按鍵
		}
		DELAY500us(4);					// 延遲2ms
	}
	return Kcode;
}
//==== 延時函數(0.5ms) ==============================
void DELAY500us(int x) 
{	int	i,j;
	for(i=0;i<x;i++) 				// 外迴圈(0.5ms*x)
		for(j=0;j<60;j++);		// 內迴圈(0.5ms)
}