#include	<reg51.h> 
#define	StepMotor P0			// Port 0連接步進馬達 
#define	LED P1					// 定義LED位址 
#define	SW 	P2					// 定義開關位址 
#define	Speed 	5				// 定義步進馬達速度(每步0.5S) 
char code PHASE1[4]={1,2,4,8};	// 1相激磁信號陣列
char code PHASE2[4]={3,6,12,9};	// 2相激磁信號陣列
void	DELAY1ms(int); 				// 宣告延時函數
// =========================================================
main()
{	char i;							// 宣告變數 
	LED=0xff;						// 關閉 LED 
	StepMotor=0;					// 關閉步進馬達 
	SW=0xff;						// 開關初始化 
	while(1)						// 無窮盡迴圈 
	{	switch (~SW&0x03)
		{	case 1: 
			{	for(i=0;i<4;i++)  		// 正轉
				{	StepMotor=PHASE1[i];// 輸出到步進馬達
					LED=~StepMotor;		// 輸出到 LED
					DELAY1ms(Speed*100);// 延遲Speed * 0.5秒
				}
				break; 	
			}
			case 2: 
			{	for(i=0;i<4;i++)  			// 反轉
				{	StepMotor=PHASE1[3-i];	// 輸出到步進馬達
					LED=~StepMotor;		// 輸出到 LED
					DELAY1ms(Speed*100);	// 延遲Speed * 0.5秒
				}
				break; 	
			}
		}
		LED=0xff;
	}
}
// =========================================================
void	DELAY1ms(int x) 
{	int i,j; 						// 宣告變數
	for(i=0;i<x;i++)				// 外迴圈(x*1ms)
		for(j=0;j<120;j++);		// 內迴圈(1ms)
}
