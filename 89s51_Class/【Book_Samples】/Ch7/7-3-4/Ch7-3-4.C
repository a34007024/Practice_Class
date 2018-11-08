#include	<reg51.h> 
#define	StepMotor P0			// Port 0連接步進馬達 
#define	LED P1					// Port 1連接LED 
#define	STEPS 	100				// 定義步數 
#define	Speed 	5				// 定義步進馬達速度(每步0.5S) 
#define	t0H (65536-50000)/256	// 定義計數起點之高8位元 
#define	t0L (65536-50000)%256	// 定義計數起點之低8位元 
char code PHASE1[4]={1,2,4,8};	// 1相激磁信號陣列 
sbit	Buzzer=P3^7;			// 宣告蜂鳴器位址 
bit		FR_Flag=0;				// 宣告正反轉旗標 
char	int_CNT=0;				// 宣告中斷次數計數器 
char	i=0,j=0;				// 宣告變數 
void	DELAY1ms(int); 			// 宣告延時函數
void	DELAY500us(int); 		// 宣告延時函數
void	BEEP(char); 			// 宣告嗶聲函數
void	LEFT(char); 			// 宣告單燈左移函數
void	RIGHT(char); 			// 宣告單燈左移函數
// =========================================================
main()
{	StepMotor=0;					// 關閉步進馬達 
	IE=0x82;						// 啟用Timer 0中斷 
	TMOD |= 0x01;					// 設定Timer 0 Mode 1 
	TH0=t0H; TL0=t0L;				// 設置計數量 
	TR0=1;							// 啟動計數器(步進馬達開動) 
	while(1)						// 無窮盡迴圈 
	{	LEFT(1);					// 單燈左移
		RIGHT(1);					// 單燈右移
		BEEP(2);					// 嗶兩聲
	} 
}
// =========================================================
void	DELAY1ms(int x) 
{	int i,j; 						// 宣告變數
	for(i=0;i<x;i++)				// 外迴圈(x*1ms)
		for(j=0;j<120;j++);			// 內迴圈(1ms)
}
// =========================================================
void	DELAY500us(int x) 
{	int i,j; 						// 宣告變數
	for(i=0;i<x;i++)				// 外迴圈(x*1ms)
		for(j=0;j<60;j++);			// 內迴圈(0.5ms)
}
// =========================================================
void	BEEP(char x) 
{	char i,j; 						// 宣告變數
	for(i=0;i<x;i++)				// 外迴圈(x聲)
	{	for(j=0;j<100;j++)			// 吸放100次 
		{	Buzzer=0;DELAY500us(1);	// 吸0.5ms
			Buzzer=1;DELAY500us(1);	// 放0.5ms
		}	
		DELAY500us(200);			// 靜音(0.1s)
	}	
}
// =========================================================
void SM_int(void)	interrupt 1			// 中斷副程式
{	if (++int_CNT==10) 					// 若已中斷10次(0.5S)
	{	int_CNT=0; 						// 中斷計數器歸零
		if (++i==STEPS)					// 若已STEPS步
		{	i=0; 						// 計數器歸零
			FR_Flag=!FR_Flag;			// 改變方向旗標
		}
		if (++j==4) j=0;				// 調整激磁指標
		if (FR_Flag) StepMotor=PHASE1[j];	// 正轉 
		else StepMotor=PHASE1[3-j];			// 反轉
		DELAY1ms(200);					// 延遲0.2秒
	}
	TH0=t0H;TL0=t0L;					// 重填計時量
}
// =========================================================
void	LEFT(char x) 				// 單燈左移函數
{	char i,j; 						// 宣告變數
	for(i=0;i<x;i++)				// 外迴圈(x圈)
	{	LED=0xfe;					// LED初值
		for(j=0;j<7;j++)			// 內迴圈(7次)
		{	DELAY1ms(100);			// 延遲0.1秒
			LED=(LED<<1)|1;			// 左移
		} 
		DELAY1ms(100);				// 延遲0.1秒
	} 
}
// =========================================================
void	RIGHT(char x) 				// 單燈右移函數
{	char i,j; 						// 宣告變數
	for(i=0;i<x;i++)				// 外迴圈(x圈)
	{	LED=0x7f;					// LED初值
		for(j=0;j<7;j++)			// 內迴圈(7次)
		{	DELAY1ms(100);			// 延遲0.1秒
			LED=(LED>>1)|0x80;		// 右移
		} 
		DELAY1ms(100);				// 延遲0.1秒
	} 
}
