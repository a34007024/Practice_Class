#include <reg51.h>
#define  LED P1			// 定義 LED 位址 
#define  KEY P2			// 定義按鍵位址 
sbit Buzzer=P3^7;		// 宣告蜂鳴器位址 
unsigned int code BaseTone[8]={	// 宣告基本音階陣列
//  0	 1	 2	 3	 4	 5	 6	 7
	956,852,759,716,638,568,506,478};
int t0H,t0L;			// 宣告變數
void DELAY1ms(int); 	// 宣告延時函數
void Sound(char);	// 宣告發音函數
// ==================================================
main()
{	Buzzer=1;	  		// 初始化
	KEY=0xff;	  		// 初始化
	IE=0x82;	  		// 啟用Timer 0中斷
	TMOD=TMOD|1;	  	// 設定Timer 0 Mode 1
	while(1)	  		// 無窮盡迴圈
	{	switch (~KEY)		// 讀取按鍵
		{	case 0x01:Sound(0);break;			// Do
			case 0x02:Sound(1);break;			// Re
			case 0x04:Sound(2);break;			// Mi
			case 0x08:Sound(3);break;			// Fa
			case 0x10:Sound(4);break;			// So
			case 0x20:Sound(5);break;			// La
			case 0x40:Sound(6);break;			// Si
			case 0x80:Sound(7);break;			// Do#
		}
	}
}
// ==================================================
void Sound(char x)
{	TH0=t0H=(65536-BaseTone[x])/256;
	// 載入所要播音階之高8位元
	TL0=t0L=(65536-BaseTone[x])%256;
	// 載入所要播音階之低8位元
	LED=~(1<<x);	// 發音
	TR0=1;DELAY1ms(200);	// 發音
	TR0=0;LED=0xff;			// 停止發音
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
