#include	<reg51.h> 
#include	"BMP.h" 
// === 定義 LCD 介面 ==================
sbit		E=P3^0;				// 宣告E信號的輸出入埠 
sbit		RW=P3^1;			// 宣告RW信號的輸出入埠 
sbit		RS=P3^2	;			// 宣告RS信號的輸出入埠 
sbit		BF=P0^7;			// 宣告忙碌旗標的位址 
#define	LCDP P0					// Port 0連接LCD匯流排 
// === 定義蜂鳴器介面 ============
sbit	Buzzer=P3^7;			// 宣告蜂鳴器位址 
// === 宣告函數 ============
void 	INIT8(void); 			// 宣告LCD初始化函數
void 	check_BF(void); 		// 宣告檢查忙碌函數
void 	write_inst(char); 		// 宣告寫入指令函數
void 	write_bmp(void);		// 宣告圖形顯示函數
void	flash(bit,char,int); 	// 宣告閃爍函數
void	DELAY500us(int); 		// 宣告延時函數
void	BEEP(char); 			// 宣告嗶聲函數
// =========================================================
main()
{	INIT8();					// LCD初始化
	write_bmp();	 			// 顯示靚圖
	while(1)					// 無窮盡迴圈  
	{	flash(1,5,400); 		// 閃爍5次
		BEEP(3);				// 嗶三聲 
	} 
}
// =========================================================
void	DELAY500us(int x) 
{	int i,j; 					// 宣告變數
	for(i=0;i<x;i++)			// 外迴圈(x*1ms)
		for(j=0;j<60;j++);		// 內迴圈(0.5ms)
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
{	E=0; 				// 禁能 
	do
	{	BF=1;			// 設定BF為輸入埠  
		RS=0;RW=1;E=1;	// 讀取BF與AC  
	}while(BF);		// 等待BF旗標為0
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
{	check_BF();		// 檢查忙錄旗標函數 
	LCDP=CHAR;			// 字元放入匯流排 
	RS=1;RW=0;E=1;		// 控制指令 
	check_BF();		// 檢查忙錄旗標函數 
} 
// === 圖形顯示函數 ===
void write_bmp(void)
{	int i,j;						// 宣告變數
	write_inst(0x36);				// 切換為擴充指令
	for(i=0;i<Height;i++)			// Height為圖高之列數
	{	write_inst(0x80+(31-i));	// 設定GDRAM之Y軸 
		write_inst(0x80);			// 設定GDRAM之X軸 
		for(j=0;j<32;j++)			// 圖最大32 Bytes(即256 bit)
			if(j < Width)			// 若在圖寬之內
				write_char(~BMPpic[Width*i+j]);// 寫入圖形內容
			else write_char(0x00);// 寫入空白
	}
} 
// === 閃爍函數(TG=0文字，TG=1圖形) ===
void flash(bit TG,char count,int time)
{	char i;							// 宣告變數
	for(i=0;i<count;i++)			// 閃爍count次
	{	if(!TG)						// 文字介面 
			write_inst(0x08);		// 關閉顯示器 
		else						// 圖形介面
			write_inst(0x34);		// 關閉顯示器 
		DELAY500us(time);			// 延遲time*0.5ms
		if(!TG)						// 文字介面 
			write_inst(0x0c);		// 開啟顯示器 
		else						// 圖形介面
			write_inst(0x36);		// 開啟顯示器 
		DELAY500us(time);			// 延遲time*0.5ms
	}
} 
