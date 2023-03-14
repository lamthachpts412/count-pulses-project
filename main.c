#include <REGX51.H>
#include <LCD_16X2.C>

#define HIGH 	P2_6
#define LOW 	P2_7
#define START 	P1_0
#define STOP 	P1_1


unsigned int xung, f, t, begin;

// Canh bao muc HIGH or LOW
void canhBao_HIGH()
{
	if(f >= 80)		{HIGH = 0;}
	else			{HIGH = 1;}
}

void canhBao_LOW()
{
	if(f <= 10)		{LOW = 0;}
	else			{LOW = 1;}
}

// Thiet lap cac gia tri dau
void setup()
{
	TMOD = T0_M0_; //timer 1, mode 1
	EX0 = 1;
	IT0 = 1;
	ET0 = 1;
	EA = 1;
	
	xung = 0;
	t = 0;
}

//	Dem xung ngoai 
void demXung() interrupt 0
{
	xung++;
}

// Ngat Timer sau 1 s
void ngatTimer() interrupt 1
{
	t++;
	TH0 = begin>>8;
	TL0 = begin;
	if(t == 20)
	{
		f = xung;
		xung = 0;
		t = 0;
	}		
}

//------------------------------
void main()
{
	begin = 15536;
	lcd_init();
	setup();
	while(1)
	{
		//Dieu khien Chuong Trinh
		if(START == 0) 			{while(!START);		TR0 = 1;		xung=0;}
		if(STOP == 0)			{while(!STOP);		TR0 = 0;}
		
		//Den bao HIGH_LOW
		canhBao_HIGH();
		canhBao_LOW();
		
		//Hien thi LCD
		lcd_gotoXY(0,0);
		lcd_word("HELLO WORLD!");
		lcd_gotoXY(0,1);
		lcd_word("f=");
		lcd_gotoXY(7,1);
		lcd_word("Hz");
		lcd_gotoXY(3,1);
		lcd_number(f);
	}
}