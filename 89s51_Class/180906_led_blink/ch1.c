#include <reg51.h>
#define led P1
void delay(int);
int status = 0;//0為往左移，1為往右移
void main(){
	led = 0xfe;
	while(1){
		if(status == 0){
			delay(250);
			led = led<<1|0x01;
			if(led==0x7f)status = 1;
		}
		else if(status == 1){
			delay(250);
			led = led>>1|0x80;
			if(led==0xfe)status = 0;
		}
	}
}
/* led shift table	  0 = bright 1 = dark
1111 1111 0xff
1111 1110 
1111 1101
1111 1011
1111 0111
1110 1111
1101 1111
1011 1111
0111 1111 0x7f
1011 1111
1101 1111
1110 1111
1111 0111
1111 1011
1111 1101
1111 1110
1000 0000 0x80
0000 0001 0x01
*/
void delay(int millisecond){
	int i,j;
	for(i=0;i < millisecond;i++){
		for(j=0;j<120;j++);
	}
}