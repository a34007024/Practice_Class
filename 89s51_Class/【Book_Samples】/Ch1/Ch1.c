#include	<reg51.h>		// 包含reg51.h標頭檔  
#define	LED		P1			// 設定輸出埠  
void delay1ms(int);			// 宣告延時函數  
//==========================================
void main(void)
{	char  pat=0x0f;			// 宣告變數
	LED=pat; 				// 指定初值(輸出到LED)
	while(1) 				// 無窮盡迴圈
	{	delay1ms(250); 		// 呼叫延時函數(延遲250ms)
		LED=~LED; 			// 將LED反相
	}
}
//==========================================
void delay1ms(int x)		// 延時函數  
{	int	i,j; 				// 宣告變數
	for(i=0;i<x;i++)		// 外迴圈(x ms)(沒有分號)
		for(j=0;j<120;j++);	// 內迴圈(1 ms)(有分號)
}
