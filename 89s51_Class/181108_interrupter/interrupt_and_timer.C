#include	<reg51.h>	// �]�treg51.h���Y��
#define	LED	 P1
#define	seg7Scan	 P1			// �w�q�C�q��ܾ����y�T������Port 1
#define seg7	P0	//�C�q��ܾ���a b c ...����P0
void delay(int);	
void left(char);		// �ŧi��O�������
void right(char);		// �ŧi��O�k�����
void BEEP(char);		// �ŧi���n���
char seg7hexCode[20] = {0xc0,0xf9,0xa4,0xb0,0x99,
						0x92,0x82,0xf8,0x80,0x98};
						// 7-seg������ܿ�X0~9
char seg7scanCode[8] = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
sbit Buzzer=P3^7;		// �ŧi���ﾹ��} 
int i=0;
int countNumber=0;
//==�D�{��================================
main()				 
{	IE=0x85;		//	�ҥ�INT 0,INT 1���_(0x85=10000101)
	IP=0x01;		//	�]�w���u������
	LED=0;			//	���(LED���G)	
	while(1){				//	�L�a�j��,�{���@���] 	
		seg7Scan = seg7scanCode[7];//�T�w�̫�@��seg7���
		seg7 = seg7hexCode[countNumber];
		delay(300);
		if(countNumber < 9)countNumber += 1;
		else countNumber = 0;
	}			
}
void int0_blink0() interrupt 0 using 1{
	int owo;
	for(owo=0;owo<3;owo++){
		seg7Scan = seg7scanCode[7];
		seg7 = seg7hexCode[0];
		delay(100);
		seg7 = 0xff;//turn off
		delay(100);
	}
	seg7 = seg7hexCode[countNumber];
}	
/*
// === INT 0�����_�Ƶ{�� - ��O����1�� ===
void int0_left(void) interrupt 0 using 1	
{	unsigned saveLED=LED;	// �x�s���_�eLED���A
	left(3);					// ��O����3��
	LED=saveLED;				// ��_���_�eLED���A
}
// === INT 1���_�Ƶ{�� - ��O�k��1�� ===
void int1_right(void) interrupt 2 using 2 
{	unsigned saveLED=LED;		// �x�s���_�eLED���A
	right(3);					// ��O�k��3��
	LED=saveLED;				// ��_���_�eLED���A
}	
*/

void delay(int ms) 
{	int i,j;		
	for (i=0;i<ms;i++)	
		for (j=0;j<120;j++);	
}					
// === ��O������� ==
void left(char x)
{	char i, j;				// �ŧi�ܼ�i,j
	for(i=0;i<x;i++)		// i�j��,����x�� 
	{	LED=0xfe;			// ��l���A=1111 1110,�̥k�O�G
		for(j=0;j<7;j++)	//	j�j��,����7��
		{	delay(500);		//	����500 0.5m=0.25s
			LED=(LED<<1)|0x01; 	//	����1���,LSB�]��1
		}			
		delay(500);	//	����0.25s
	}	
}		
// === ��O�k����� ===
void right(char x) 	
{	char i, j;				// �ŧi�ܼ�i,j
	for(i=0;i<x;i++)		// i�j��,����x�� 
	{	LED=0x7f;			// ��l���A=0111 1111,�̥��O�G
		for(j=0;j<7;j++)	//	j�j��,�k��7��
		{	delay(500);	//	����500 0.5m=0.25s
			LED=(LED>>1)|0x80; 	//	�k��1���,MSB�]��1
		}			
		delay(500);	//	����0.25s
	}	
}		
// === ���n��� ===
void BEEP(char x) 
{	int	i,j;
	for(i=0;i<x;i++) 				// ��x�n
	{	for(j=0;j<100;j++)		// ���Ƨl��100��
		{	Buzzer=0;delay(1);// ���ﾹ�l
			Buzzer=1;delay(1);// ���ﾹ��
		} 
	 	delay(200);			// �R��0.1��
	} 
}