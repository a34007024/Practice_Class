#include	<reg51.h>			// 包含reg51.h標頭檔  
#define	SEGP  P0				// 定義顯示信號埠 
#define	SCANP P1				// 定義掃瞄埠 
#define	count0 50000			// 預設計數量(50ms)
#define	count1 1000				// 預設計數量(1ms)
#define	t0H (65536-count0)/256	// 預設計數起點(50ms)
#define	t0L (65536-count0)%256	// 預設計數起點(50ms)
#define	t1H (65536-count1)/256	// 預設計數起點(1ms)
#define	t1L (65536-count1)%256	// 預設計數起點(1ms)
#define	speed 500				// 預設調整速度(500=250ms)
								// 即0.25s，每秒跳4次
//char	T0_H,T0_L,T1_H,T1_L;	// 宣告計量變數 
char	int0_CNT=0;				// 宣告預設中斷重複次數
char	SEGX=0; 				// 宣告掃瞄指標
void	DELAY500us(int);		// 宣告延時函數 
void	BEEP(char);				// 宣告嗶聲函數 
bit		_mode=0;				// 宣告模式旗標
		// _mode=0：計時模式、_mode=1：調整模式
sbit	_H=P2^0;				// 宣告時調整鍵位址
sbit	_M=P2^1;				// 宣告分調整鍵位址
sbit	_Shift=P2^2;			// 宣告Shift鍵位址
sbit	Buzzer=P3^7;			// 宣告蜂鳴器位址
// 七節顯示器編碼表
char code TAB[12]={	0xc0,0xf9,0xa4,0xb0,0x99,
					0x92,0x82,0xf8,0x80,0x98, 
					0xff,0xbf};//	0xbf=1011 1111(-)
// 低態驅動掃瞄碼 
char code SCAN_CODE[8]={0x7f,0xbf,0xdf,0xef,
						0xf7,0xfb,0xfd,0xfe };	
// 顯示資料
// 			 S0 S1 - M0 M1 -  H0 H1
char DISP[8]={0, 0,11,0,0,11,0, 0};// 初值為00-00-00 
// 時：H1=DISP[7], H0=DISP[6]
// 分：M1=DISP[4], M0=DISP[3]
// 秒：S1=DISP[1], S0=DISP[0]
//==== 主程式 =========================================
main()		 
{	IE=0x8b;					// 啟用int0,T0,T1中斷 
	PT1=1;						// Timer 1高優先等級 
	IT0=1;						// 0=低態觸發,1=邊緣觸發 
	TMOD=0x11;					// 設定T0,T1都為Mode 1
	TH0=t0H;TL0=t0L;			// T0填入計量  
	TH1=t1H;TL1=t1L;			// T1填入計量  
	TR1=1;						// 啟動Timer 1(開始掃瞄) 
	// Timer 0：計秒、Timer 1：掃瞄(顯示) 
	while(1)
	{	while(_mode)			
		// ===== 調整模式 =====
 		{	TR0=0;					// 停止計時
			DISP[0]=DISP[1]=0;		// 秒數歸零 
			// _H：時調整鍵
			// _M：分調整鍵
			// _Shift：Shift鍵
	 		// =======================
			// == 從00到23 ==(時數上調)
			// =======================
			if(!_H && _Shift)		// _H
			{	if (DISP[7]==2 && DISP[6]==3)// 23時
				{	DISP[7]=0;DISP[6]=0;}		// 調回00時
				else if (DISP[6]!=9) DISP[6]++; 	// 時個位數加1
					else
					{	DISP[6]=0; 		// 時個位數進位
						DISP[7]++; 		// 時十位數加1
					}
			}
			// =======================
			// == 從23到00 ==(時數下調)
			// =======================
			if(!_H && !_Shift)	// _Shift+_H
			{	if (DISP[7]==0 && DISP[6]==0)	// 00時
				{	DISP[7]=2;DISP[6]=3;}		// 調回23時
				else if (DISP[6]!=0) DISP[6]--; // 時個位數減1
					else
					{	DISP[6]=9; 		// 時個位數借位
						DISP[7]--; 		// 時十位數減1
					}
			}
			// =======================
			// == 從00到59 ==(分數上調)
			// =======================
			if(!_M && _Shift)	// _Shift+_M
			{	if (DISP[4]==5 && DISP[3]==9)// 59分
				{	DISP[4]=0;DISP[3]=0;}		// 調回00分
				else if (DISP[3]!=9) DISP[3]++; 	// 分個位數加1
					else
					{	DISP[3]=0; 		// 分個位數進位
						DISP[4]++; 		// 分十位數加1
					}
			}
			// =======================
			// == 從59到00 ==(分數下調)
			// =======================
			if(!_M && !_Shift)	// _M
			{	if (DISP[4]==0 && DISP[3]==0)// 00分
				{	DISP[4]=5;DISP[3]=9;}		// 調回59分
				else if (DISP[3]!=0) DISP[3]--; // 分個位數減1
					else
					{	DISP[3]=9; 		// 分個位數借位
						DISP[4]--; 		// 分十位數減1
					}
			}
			DELAY500us(speed);// 延遲speed ms
		}
		// =====計時模式 =====
		TR0=1;						// 開始計時 
		if (	DISP[7]==0 && DISP[6]==0 && 
				DISP[4]==0 && DISP[3]==0 && DISP[1]==0 && DISP[0]==0)
		{	BEEP(2); DELAY500us(2000);}// 00時嗶兩聲 
	}
}
//=== 切換模式(int0) ===
void mode_toggle(void) interrupt 0	
{	_mode=!_mode;				// 切換模式旗標
}	
//=== 秒產生中斷副程式(T0) ===
// ====== 時：H1=DISP[7], H0=DISP[6] ======
// ====== 分：M1=DISP[4], M0=DISP[3] ======
// ====== 秒：S1=DISP[1], S0=DISP[0] ======
void Oclock(void) interrupt 1 using 1	
{	TH0=t0H;TL0=t0L;			// T0填入計量  
	if (++int0_CNT==20)			// 中斷次數超過20次(即1ms)
	{	int0_CNT=0; 				// 中斷次數歸零 
		if (DISP[0]<9) DISP[0]++;
		// 秒個位數加1
		else 
		// 秒個位數進位
		{	if (DISP[1]<5) 
			{	DISP[1]++;DISP[0]=0;  }
			else
			// 秒十位數進位
			{ 	if (DISP[3]<9) 
				{	DISP[3]++;DISP[1]=DISP[0]=0;  }
				else
				// 分個位數進位
				{ 	if (DISP[4]<5) 
					{	DISP[4]++;
						DISP[3]=DISP[1]=DISP[0]=0; 
					}
					else
					// 分十位數進位
					{ 	if (DISP[7]==2 && DISP[6]==3) 
						{	DISP[7]=DISP[6]=0;// 時歸零 
							DISP[4]=DISP[3]=0;// 分歸零 
							DISP[1]=DISP[0]=0;// 秒歸零 
						}
						else if (DISP[6]<9) 
						{	DISP[6]++;
							DISP[4]=DISP[3]=0;// 分歸零 
							DISP[1]=DISP[0]=0;// 秒歸零 
						}
						else
						// 時個位數進位
						{ 	DISP[7]++;DISP[6]=0;
							DISP[4]=DISP[3]=0;// 分歸零 
							DISP[1]=DISP[0]=0;// 秒歸零 
						}
					}
				} 
			}
		}
	}	
}	
//=== 八位七節顯示器掃瞄中斷副程式(T1) ===
void segscan(void) interrupt 3 using 2
{	TH1=t1H;TL1=t1L;			// T1填入計量  
	if (++SEGX==8) SEGX=0;		// 調整掃瞄指標 
	SEGP=0xff;					// 關閉顯示信號(防殘影)
	SCANP=SCAN_CODE[7-SEGX];	// 輸出掃瞄信號 
	SEGP=TAB[DISP[SEGX]];		// 輸出顯示信號 
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
	for(i=0;i<x;i++) 				// 嗶x聲 
	{	for(j=0;j<100;j++)			// 重複吸放100次
		{	Buzzer=0;DELAY500us(1);// 蜂鳴器吸
			Buzzer=1;DELAY500us(1);// 蜂鳴器放
		} 
	 	DELAY500us(200);			// 靜音0.1秒
	} 
}

