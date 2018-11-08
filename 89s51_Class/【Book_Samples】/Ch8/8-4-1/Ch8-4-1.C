#include	<reg51.h> 
// === 定義 LCD 介面 ==================
sbit	E=P3^0;					// 宣告E信號的輸出入埠 
sbit	RW=P3^1;				// 宣告RW信號的輸出入埠 
sbit	RS=P3^2	;				// 宣告RS信號的輸出入埠 
sbit	BF=P0^7;				// 定義忙碌旗標的位址 
#define	LCDP P0					// Port 0連接LCD匯流排 
// === 定義 LED與蜂鳴器介面 ============
#define	LED P1					// Port 1連接LED 
sbit	Buzzer=P3^7;			// 宣告蜂鳴器位址 
// === 定義 Timer 0計時量(50ms) ============
#define	t0H (65536-50000)/256	// 定義計數起點之高8位元 
#define	t0L (65536-50000)%256	// 定義計數起點之低8位元 
char	int_CNT=0;				// 宣告中斷次數計數器 
// === 宣告顯示內容 ============
char code message1[]=	"歡迎使用 LED控制器";
char code message2[]=	"現正展示單燈左移";
char code message3[]=	"現正展示單燈右移";  
// === 宣告LED變數 ============
bit		DIR=0;					// 宣告LED移動方向旗標 
char	LED_CNT=0;				// 宣告LED移動計數器 
// === 宣告函數 ============
void 	INIT8(void); 			// 宣告LCD初始化函數
void 	check_BF(void); 		// 宣告檢查忙碌函數
void 	write_inst(char); 		// 宣告寫入指令函數
void 	write_char(char); 		// 宣告寫入字元函數
void	DELAY500us(int); 		// 宣告延時函數
void	BEEP(char); 			// 宣告嗶聲函數
// =========================================================
main()
{	char i;						// 宣告變數
	LED=0xff;					// 關閉LED 
	INIT8();					// LCD初始化
	write_inst(0x80); 			// LCD定址第0列
	for(i=0;i<16;i++)
		write_char(message1[i]); // LCD顯示第0列
	IE=0x82;					// 啟用Timer 0中斷 
	TMOD |= 0x01;				// 設定Timer 0 Mode 1 
	TH0=t0H; TL0=t0L;			// 設置計數量 
	TR0=1;						// 啟動計數器(LED開動) 
	while(1)					// 無窮盡迴圈 
	{	DIR=0;					// 設定方向旗標
		write_inst(0x90); 		// LCD定址第1列
		for(i=0;i<16;i++)
			write_char(message2[i]); // LCD顯示第1列(左移)
		DELAY500us(20000);		// 單燈左移10秒
		TR0=0; LED=0xff; 		// 停止計時器，關閉LED
		BEEP(2);				// 嗶兩聲
		TH0=t0H; TL0=t0L;		// 設置計數量 
		TR0=1;					// 啟動計數器(LED開動) 
		DIR=1;					// 設定方向旗標
		write_inst(0x90); 		// LCD定址第1列
		for(i=0;i<16;i++)
			write_char(message3[i]); // LCD顯示第1列(右移)
		DELAY500us(20000);		// 單燈右移10秒
		TR0=0; LED=0xff; 		// 停止計時器，關閉LED
		BEEP(2);				// 嗶兩聲
		TH0=t0H; TL0=t0L;		// 設置計數量 
		TR0=1;					// 啟動計數器(LED開動) 
	}
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
void LED_int(void)	interrupt 1	// 中斷副程式
{	if (++int_CNT==2) 					// 判斷是否已中斷2次(0.1S)
	{	int_CNT=0; 						// 中斷次數計數器歸零
		if (++LED_CNT==8) 				// 判斷是否已移動7次
			LED_CNT=0; 					// LED移動計數器歸零
		if (DIR)						// 若方向旗標為1(右移)
			LED=~(0x80>>LED_CNT);		//  LED右移
		else							// 若方向旗標為0(左移)
			LED=~(0x01<<LED_CNT); 		//  LED左移
	}
	TH0=t0H;TL0=t0L;					// 重填計時量
}
// === 8位元傳輸介面之LCM初始化函數 ===
void INIT8(void) 
{	write_inst(0x30); 			// 設定功能(8位元傳輸介面)
	write_inst(0x30); 			// 設定功能(8位元傳輸介面)
	write_inst(0x08); 			// 關閉顯示器
	write_inst(0x01); 			// 清除顯示器
	write_inst(0x06); 			// 設定輸入模式
	write_inst(0x0c); 			// 開啟顯示器
}
// === 檢查忙碌旗標函數 ===
void check_BF(void)
{	E=0; 						// 禁能 
	do
	{	BF=1;					// 設定BF為輸入埠  
		RS=0;RW=1;E=1;			// 讀取BF與AC  
	}while(BF);					// 等待BF旗標為0
}  	 
// === 寫入指令函數 ==
void write_inst(char inst)
{	check_BF();			// 檢查忙錄旗標函數 
	LCDP=inst;			// 指令放入匯流排 
	RS=RW=0;E=1;		// 控制指令 
	check_BF();			// 檢查忙錄旗標函數 
} 
// === 寫入字元函數===
void write_char(char CHAR)
{	check_BF();			// 檢查忙錄旗標函數 
	LCDP=CHAR;			// 字元放入匯流排 
	RS=1;RW=0;E=1;		// 控制指令 
	check_BF();			// 檢查忙錄旗標函數 
} 
