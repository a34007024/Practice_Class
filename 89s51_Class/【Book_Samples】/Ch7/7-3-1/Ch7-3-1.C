#include	<reg51.h> 
#define	StepMotor P0			// Port 0連接步進馬達 
#define	STEPS 	100				// 定義步進數 
#define	Speed 	5				// 定義步進馬達速度(每步0.5S) 
sbit  		PB1=P2^0;				// 1相激磁信號100步
sbit  		PB2=P2^1;				// 2相激磁信號100步
sbit  		PB3=P2^2;				// 1-2相激磁信號100步
char code PHASE1[4]={1,2,4,8};	// 1相激磁信號陣列
char code PHASE2[4]={3,6,12,9};	// 2相激磁信號陣列
char code PHASE1_2[8]={1,3,2,6,4,12,8,9}; // 1-2相激磁信號陣列
void	SM_driver(char *, bit);		// 宣告驅動函數  
void	DELAY1ms(int); 				// 宣告延時函數
// =========================================================
main()
{	StepMotor=0;						// 關閉步進馬達 
	PB1=PB2=PB3=1;						// 按鈕開關初始化 
	while(1)							// 無窮盡迴圈 
	{	if (!PB1) 
			SM_driver(PHASE1,0); 		// 1相驅動  
		else if (!PB2)
			SM_driver(PHASE2,0); 		// 2相驅動
		else if (!PB3)
			SM_driver(PHASE1_2,1); 		// 1-2相驅動
	}
}
// =========================================================
void	SM_driver(char *PHASE, bit F4_8) 
{	char i,j,x; 					// 宣告變數
	if(F4_8) x=8; else x=4;			// 判斷一個週期幾步
	for(i=0;i<STEPS/4;i++)			// 執行STEP/4個週期
		for(j=0;j<x;j++)			// 總共x個信號
		{	StepMotor=PHASE[j];		// 輸出到步進馬達
			DELAY1ms(Speed*100);	// 延遲Speed * 0.5秒
		}
	StepMotor=0;						// 關閉步進馬達 
}
// =========================================================
void	DELAY1ms(int x) 
{	int i,j; 					// 宣告變數
	for(i=0;i<x;i++)			// 外迴圈(x*1ms)
		for(j=0;j<120;j++);		// 內迴圈(1ms)
}
