#include	<reg51.h> 
#define	StepMotor P0			// Port 0連接步進馬達 
#define	STEPS 	100				// 定義步進數 
#define	Speed 	5				// 定義步進馬達速度(每步0.5S) 
sbit  	PB1=P2^0;				// 1相激磁信號100步 
sbit  	PB2=P2^1;				// 2相激磁信號100步 
sbit  	PB3=P2^2;				// 1-2相激磁信號100步 
sbit  	STOP=P2^3;				// 停止鍵 
char 	S1=1;					// 1相激磁信號
char 	S2=3;					// 2相激磁信號
void	SM_driver(char);		// 宣告驅動函數  
void	DELAY1ms(int); 			// 宣告延時函數
bit		STOP_F=0;
// =========================================================
main()
{	StepMotor=0;						// 關閉步進馬達 
	PB1=PB2=PB3=STOP=1;					// 按鈕開關初始化 
	while(1)							// 無窮盡迴圈 
	{	if (!PB1)  SM_driver(1); 		// 1相驅動  
		else if (!PB2) SM_driver(2);	// 2相驅動
		else if (!PB3) SM_driver(3);	// 1-2相驅動
		STOP_F=0;
	}
}
// =========================================================
void	SM_driver(char PHASE) 
{	char i,j; 							// 宣告變數
	for(i=0;i<STEPS/4;i++)				// 執行STEP/4個週期
	{	S1=1;S2=3;						// 初始化
		for (j=0;j<4;j++)				// 判斷週期結束
		{	switch (PHASE)
			{	case 1:						
				{	StepMotor=S1;		// 1相驅動步進馬達
					S1<<=1;				// 下一個驅動信號 
					break;
				}
				case 2:						
				{	StepMotor=S2;		// 2相驅動步進馬達
					S2<<=1;				// 下一個驅動信號 
					if(S2==0x18) S2=9;	// 調整驅動信號 
					break;
				}
				case 3:						
				{	StepMotor=S1;		// 1相驅動步進馬達
					S1<<=1;				// 下一個驅動信號 
					DELAY1ms(Speed*100);// 延遲Speed * 0.5秒
					StepMotor=S2;		// 2相驅動步進馬達
					if (STOP_F) break;
					S2<<=1;				// 下一個驅動信號 
					if(S2==0x18) S2=9;	// 調整驅動信號 
					break;
				}
			}
			DELAY1ms(Speed*100);// 延遲Speed * 0.5秒
			if (STOP_F) break;
		}
	}
	StepMotor=0;						// 關閉步進馬達 
}
// =========================================================
void	DELAY1ms(int x) 
{	int i,j; 					// 宣告變數
	for(i=0;i<x;i++)			// 外迴圈(x*1ms)
		for(j=0;j<120;j++)
			if (!STOP)
			{ STOP_F=1;break; }		// 內迴圈(1ms)
}
