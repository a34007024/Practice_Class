#include	<reg51.h>				// �]�treg51.h���Y��  
#define	LED  P1						// �w�qLED�s����Port 1 
sbit	Buzzer=	P3^7;				// �ŧi���ﾹ��} 
void	BEEP(char);					// �ŧi���n��� 
void	DELAY500us(int);			// �ŧi0.5ms���ɨ�� 
void	DELAY1ms(int);				// �ŧi1ms���ɨ�� 
void	LEFT(char);					// �ŧi��O������� 
void	RIGHT(char);				// �ŧi��O�k����� 
//==== �D�{�� =========================================
main()		 
{	while(1)						// �L�a�ɰj�� 
	{	LEFT(1);BEEP(1);			// ��O�����@�� 
		RIGHT(1);BEEP(2);			// ��O�k���@�� 
	}
}
//==== ��O������� ==============================
void	LEFT(char x)
{	char i,j;
	for(i=0;i<x;i++)		// ����x���O����  
	{	LED=0xfe;			// �]�w��O�������0xfe=1111 1110 
		for(j=0;j<7;j++)	// ����7��
		{	DELAY1ms(100);	// ����0.1��(�Y���0.1��)  
			LED=(LED<<1)|1;// LED�����@��A�ӳ̥k��j�1
		}
		DELAY1ms(100); 		// ����0.1��(�Y���0.1��) 
	}
}
//==== ��O�k����� ==============================
void	RIGHT(char x)
{	char i,j;
	for(i=0;i<x;i++)		// ����x���O�k��  
	{	LED=0x7f;			// �]�w��O�k�����0x7f=0111 1111 
		for(j=0;j<7;j++)	// ����7��  
		{	DELAY1ms(100);	// ����0.1��(�Y���0.1��)  
			LED=(LED>>1)|0x80;// LED�k���@��A�ӳ̥���j�1
		}
		DELAY1ms(100); 		// ����0.1��(�Y���0.1��) 
	}
}
//==== ���ɨ��(1ms) ==============================
void	DELAY1ms(int x) 
{	int	i,j;
	for(i=0;i<x;i++) 			// �~�j��(1ms*x)
		for(j=0;j<120;j++);		// ���j��(1ms)
}
//==== ���n��� ==============================
void	BEEP(char x)
{	char i,j;
	for(i=0;i<x;i++)			// ����x�n  
	{	for(j=0;j<100;j++)		// ���ﾹ�l��100��  
		{	Buzzer=0;DELAY500us(1); // ���ﾹ�l0.5ms  
			Buzzer=1;DELAY500us(1); // ���ﾹ��0.5ms
		}
		DELAY500us(200); 		// ���ﾹ�R��0.1��(0.5ms*200)  
	}
}
//==== ���ɨ��(0.5ms) ==============================
void	DELAY500us(int x) 
{	int	i,j;
	for(i=0;i<x;i++) 			// �~�j��(0.5ms*x)
		for(j=0;j<60;j++);		// ���j��(0.5ms)
}
