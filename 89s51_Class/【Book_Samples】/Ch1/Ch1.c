#include	<reg51.h>		// �]�treg51.h���Y��  
#define	LED		P1			// �]�w��X��  
void delay1ms(int);			// �ŧi���ɨ��  
//==========================================
void main(void)
{	char  pat=0x0f;			// �ŧi�ܼ�
	LED=pat; 				// ���w���(��X��LED)
	while(1) 				// �L�a�ɰj��
	{	delay1ms(250); 		// �I�s���ɨ��(����250ms)
		LED=~LED; 			// �NLED�Ϭ�
	}
}
//==========================================
void delay1ms(int x)		// ���ɨ��  
{	int	i,j; 				// �ŧi�ܼ�
	for(i=0;i<x;i++)		// �~�j��(x ms)(�S������)
		for(j=0;j<120;j++);	// ���j��(1 ms)(������)
}
