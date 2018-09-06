sbit buzzer=P3^7;
void delay(int);
void delay100us(int);
void delay25us(int);
void beep(int beepcount){//one beep last for 0.2s
	int i,j;
	for(i=0;i<beepcount;i++){
		for(j=0;j<100;j++){
			buzzer = 0;delay100us(1);
			buzzer = 1;delay100us(1);
		}
		delay100us(1000); //100ms
	}  
	for(i=0;i<beepcount;i++){
		for(j=0;j<100;j++){
			buzzer = 0;delay100us(2);
			buzzer = 1;delay100us(2);
		}
		delay100us(1000); //100ms
	}
}
void beepSW2(int beepcount){//one beep last for 0.2s
	int i,j;
	for(i=0;i<beepcount;i++){
		for(j=0;j<100;j++){
			buzzer = 0;delay100us(3);
			buzzer = 1;delay100us(3);
		}
		delay100us(1000); //100ms
	}  
	for(i=0;i<beepcount;i++){
		for(j=0;j<100;j++){
			buzzer = 0;delay100us(5);
			buzzer = 1;delay100us(5);
		}
		delay100us(1000); //100ms
	}
}
void delay(int millisecond){
	int i,j;
	for(i=0;i<millisecond;i++){
		for(j=0;j<120;j++);
	}
}

void delay100us(int time){
	int i,j;
	for(i=0;i<time;i++){
		for(j=0;j<12;j++);
	}
}
void delay25us(int time){
	int i,j;
	for(i=0;i<time;i++){
		for(j=0;j<3;j++);
	}
}
