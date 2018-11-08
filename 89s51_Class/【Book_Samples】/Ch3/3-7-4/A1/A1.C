#include	<reg51.h>				// 包含reg51.h標頭檔  
#define	SEGP P0					// 定義顯示信號埠 
#define	KEYP P2					// 定義鍵盤埠 
void	keyscan(void);			// 宣告鍵盤掃瞄函數 
void	DELAY500us(int);		// 宣告延時函數(1ms) 
void	BEEP(char);				// 宣告嗶聲函數 
void	Dcount(void);			// 宣告倒數函數 
void	SCAN_SEG(void);			// 宣告掃瞄函數 
void	Modify(void);			// 宣告調整函數		
sbit	HP=P1^0;				// 宣告高功率輸出埠位址
sbit	MP=P1^1;				// 宣告中功率輸出埠位址
sbit	LP=P1^2;				// 宣告低功率輸出埠位址
sbit	Buzzer=P3^7;			// 宣告蜂鳴器位址
bit	BF=0;					// 宣告嗶聲旗標(預設不響)
bit	HP_F=0;					// 宣告高功率旗標(預設不動作)
bit	MP_F=0;					// 宣告中功率旗標(預設不動作)
bit	LP_F=0;					// 宣告低功率旗標(預設不動作)
// 七節顯示器編碼表
char code TAB[11]={	0xc0,0xf9,0xa4,0xb0,0x99,
					0x92,0x82,0xf8,0x80,0x98,  0xff};	
// 低態驅動掃瞄碼
char code SCAN_CODE[8]={	0x7f,0xbf,0xdf,0xef,
							0xf7,0xfb,0xfd,0xfe };	
// 顯示資料
char DISP[4]={0,10,10,10};// 初值為0 
//==== 主程式 =========================================
main()		 
{	HP=MP=LP=1; 		// 關閉負載輸出
while(1)
	{	keyscan();		// 呼叫鍵盤掃瞄函數 
		if (HP_F)		// 高功率輸出
		{	HP=0; 		// 開啟高功率輸出
			Dcount();	// 倒數	
			HP_F=0;		// 取消HP_F旗標  
			HP=1;		// 關閉高功率輸出	
			BEEP(2);	// 嗶兩聲 
		} 
		if (MP_F)		// 中功率輸出
		{	MP=0; 		// 開啟中功率輸出
			Dcount();	// 倒數	
			MP_F=0;		// 取消MP_F旗標  
			MP=1;		// 關閉中功率輸出	
			BEEP(2);	// 嗶兩聲 
		} 
		if (LP_F)		// 低功率輸出
		{	LP=0; 		// 開啟低功率輸出
			Dcount();	// 倒數	
			LP_F=0;		// 取消LP_F旗標  
			LP=1;		// 關閉低功率輸出	
			BEEP(2);	// 嗶兩聲 
		} 
	}
}
//=== 4 4鍵盤掃瞄函數 ===
void keyscan(void) 	// 掃瞄後將傳回按鍵值
{	char X,Y, Ycode,Kcode,i;
	for(X=0;X<4;X++)			// 掃瞄4行
	{	SEGP=0xff;				// 關閉顯示信號(防殘影)
		KEYP=SCAN_CODE[X];	// 輸出掃瞄信號
		SEGP=TAB[DISP[X]];	// 輸出顯示信號
		Y=~KEYP & 0x0f;		// 讀取鍵盤
		if	(Y!=0)		    	// 若有按鍵被按下
		{	if(Y==1) Ycode=0;		// 第0列有按鍵按下
			else if (Y==2) Ycode=1;	// 第1列有按鍵按下
			else if (Y==4) Ycode=2;	// 第2列有按鍵按下
			else if (Y==8) Ycode=3;	// 第3列有按鍵按下
			Kcode=4*X + Ycode;		// 計算按鍵值
			if (BF) BEEP(1);			// 嗶一聲
			// === 數字鍵 ===
			if (Kcode<10 && Kcode>=0 )	// 若是數字鍵
			{	for(i=0;i<3;i++)			
					DISP[3-i]=DISP[2-i];// 顯示資料移位
				DISP[0]=Kcode;			// 將鍵值存入個位數
			}
			while(Y!=0) Y=~KEYP & 0x0f;// 等待放開按鍵
			// === 功能鍵 ===
			// === F 鍵 ===
			if (Kcode==0x0f ) BF=!BF;	// 切換嗶聲
			// === e 鍵 ===
			if (Kcode==0x0e )			// 清除
			{	for(i=0;i<3;i++)			
					DISP[i]=10;			// 千位~十位數填入空白
				DISP[0]=0;					// 個位數填入0
			}
			// === d 鍵 ===
			if (Kcode==0x0d )			// 刪字
			{	for(i=0;i<3;i++)			
					DISP[i]=DISP[i+1];	// 顯示資料右移
				DISP[3]=10;				// 千位數填入空白
			}
			// === c 鍵 ===
			if (Kcode==0x0c ) 			// 高功率
			{	HP_F=1; Modify();	}
			// === b 鍵 ===
			if (Kcode==0x0b ) 			// 中功率
			{	MP_F=1; Modify();	}
			// === a 鍵 ===
			if (Kcode==0x0a ) 			// 低功率
			{	LP_F=1; Modify();	}
		}
		DELAY500us(4);					// 延遲2ms
	}
}
//==== 延時函數(0.5ms) ==============================
void DELAY500us(int x) 
{	int	i,j;
	for(i=0;i<x;i++) 				// 外迴圈(0.5ms*x)
		for(j=0;j<60;j++);		// 內迴圈(0.5ms)
}
//==== 嗶聲函數 ==============================
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
//==== 倒數函數 ==============================
void	Dcount(void)			
{	char i;						// 宣告變數	
	for(i=0;i<4;i++)			// 非0~9轉變為0	
		if(DISP[i]>9 || DISP[i]<0) DISP[i]=0;
	while(1)
	{	if(DISP[3]==0 && DISP[2]==0 && DISP[1]==0 && DISP[0]==0)
		{	DISP[3]=DISP[2]=DISP[1]=10;	   // 千位數~十位數填入空白
			break;				// 結束倒數
		}	
		// === 延遲1s ===
		for(i=0;i<50;i++)		// 延遲掃瞄50次(約1s)
			SCAN_SEG();			// 每次掃瞄約20ms
		// === 倒數 ===
		if (DISP[0]!=0)	DISP[0]--;	// 秒之個位數減1
		else	
		{	DISP[0]=9; 			// 秒之個位數改為9(借位)
			if (DISP[1]!=0) 	DISP[1]--;	// 秒之十位數減1
			else	
			{	DISP[1]=5; 		// 秒之十位數改為5(借位)
				if (DISP[2]!=0) 	DISP[2]--;// 分之個位數減1
				else
				{	DISP[2]=9; 	// 分之個位數改為9(借位)
					DISP[3]--;	// 分之十位數減1
				}
			}
		}						// 結束倒數
	}
}
//==== 掃瞄函數 ==============================
void	SCAN_SEG(void)			// 20ms	
{	char X;						// 宣告變數	
	for(X=0;X<4;X++)			// 掃瞄4行 
	{	SEGP=0xff;				// 關閉顯示信號(防殘影)
		KEYP=SCAN_CODE[X];	// 輸出掃瞄信號 
		SEGP=TAB[DISP[X]];	// 輸出顯示信號 
		DELAY500us(8);		// 延遲4ms
	}
	DELAY500us(8);		// 延遲4ms
}
//==== 調整函數 ============================
void	Modify(void)					
{	bit i=0;						// 宣告變數	
	if (DISP[3]<10 && DISP[3]>5)	// 調整分之十位數  
	{	DISP[3]=5;i=1; }
	if (DISP[1]<10 && DISP[1]>5)	// 調整秒之十位數   		
	{	DISP[1]=5;i=1; }
	if (i) { BEEP(2); i=0;}			// 嗶聲    
}
