#include	<reg51.h>	// 包含reg51.h標頭檔 
#define	SW	 P2			// 定義SW接至Port 0
#define	LED	 P1			// 定義LED接至Port 1
#define	keys ~SW&0x03	// 定義按鍵遮罩 
char	pat=0x0f;		// 宣告開關信號變數  
void	wait(void);		// 宣告防彈跳函數 
//==主程式======================================
main()				
{	char R_key;
	SW=0xff; 			// 設定SW為輸入埠
	PCON|=0x80;			// 將SMOD位元設定為1
	SCON=0x90;			// 將串列埠採mode 2
	while(1)
	{	R_key=keys;
		wait();			// 防彈跳
		while(keys!=0);	// 等待開關放開 
		wait();			// 防彈跳
		switch (keys) 	// 判斷按鍵  
		{	case 1:		// 傳送單燈左移指令  
		 	{	SBUF=0x0f;
				break;
			}
			case 2:		// 傳送單燈右移指令 
		 	{	SBUF=0xf0;
				break;
			}
		}
		while(!RI);		// 等待接收完成
		RI=TI=0;		// 清除RI,TI旗標(重傳)
		if (SBUF==0x0f) LED=0x00;// 若接收到的開啟指令，則LED全開  
		if (SBUF==0xf0) LED=0xff;// 若接收到的關閉指令，則LED全關  
	} 
} 
//====================================
void	wait(void)
{	char i,j;
	for(i=0;i<30;i++)
		for(j=0;j<120;j++);
} 
