#include <reg51.h>
#define  B0 50000		// 定義基本節拍
sbit Buzzer=P3^7;		// 宣告蜂鳴器位址 
unsigned int code BaseTone[37]={	// 宣告基本音階陣列
// 中音 
//  0	1		2		3		4		5		6		7
	1,	956,	852,	759,	716,  638,	568,	506,
//  8	9	10
	1,	1, 1,
// 低音 
//  11		12		13		14		15		16		17
	1908,	1701,	1515,	1433, 	1276,	1136,	1012,
//  18	19	20
	1,	1, 1,
// 高音 
//  21		22		23		24		25		26		27
	478,	426,	379,	358, 	319,	284,	253,
//  28	29	30
	1,	1, 1,
// 中音(Do#, Re#,-,Fa#,So#,La# ) 
//  31		32		33		34		35		36		
	903,	804,	1,		676, 	602,	526	};
/*// 點仔膠 音調表 
char code SONG[]={
	6,6,6,  	5,3,6, 	22,21,22,	6,5,6,			//1	
	21,21,22,23,23,22,22,21,21,6,6, 5,7,6,  100};	//2
// 點仔膠 節拍表 
char code BEAT[]={
	4,4,6,  	4,4,6, 	4,4,6,		4,4,6,		//1
	4,4,6,2,  	4,4,6, 	4,4,4,4,	4,4,6};		//2
//========================================*/
// flower dance 音調表 
char code SONG[]={
	3,2,6,2,3,2,6,2,	3,2,6,2,3,2,6,2,	3,2,6,2,3,2,6,2,	3,2,6,2,3,2,6,2,
	3,2,6,2,3,2,6,2,	3,2,6,2,3,2,6,2,	3,2,6,2,3,2,6,2,	3
	,100}; //100為空的陣列格，表示歌曲結尾
// flower dance 節拍表 
char code BEAT[]={
	4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,4,	32
	};
//========================================
int t0H,t0L;			// 宣告變數
void beat(char); 		// 宣告節拍函數
void DELAY(int); 		// 宣告延時函數
void DELAY1ms(int); 	// 宣告延時函數
// ==================================================
main()
{	unsigned char i; 	// 宣告播歌指標
	Buzzer=1;	  		// 初始化
	IE=0x82;	  		// 啟用Timer 0中斷
	TMOD=TMOD|1;	  	// 設定Timer 0 Mode 1
	while(1)	  		// 若開關on
	{	i=0;			// 若播歌指標歸零
		TR0=1;			// 開始播歌
		while(SONG[i]!=100)	// 若非結束符號，則播歌
		{	TH0=t0H=(65536-BaseTone[SONG[i]])/256;
		 	// 載入所要播音階之高8位元
		 	TL0=t0L=(65536-BaseTone[SONG[i]])%256;
		 	// 載入所要播音階之低8位元
		 	beat(BEAT[i]); 	// 等待節拍結束
		 	i++; 			// 下一個音
		}
		TR0=0;				// 停止播放 
		DELAY1ms(30000); 	// 等30秒
	} 
} 
// ==================================================
void beat(char x)
{	char i;
	for (i=0;i<x;i++)
		DELAY((B0-23)/12);	
}	
// ==================================================
void DELAY1ms(int x)  	// 宣告延時函數
{	int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<120;j++);
}
// ==================================================
void DELAY(int x)
{	int i;
	for(i=0;i<x;i++);
}
// ==================================================
void TONE_int(void) interrupt 1
{	TH0=t0H; TL0=t0L;	// 重新填入計時量
	Buzzer=!Buzzer; 	// 切換蜂鳴器
}
