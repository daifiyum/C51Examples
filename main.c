#include <reg51.h>

typedef unsigned int u16;
unsigned int count;
sbit led1 = P1^5; 
sbit led2 = P1^4;
sbit led3 = P1^6;
sbit led4 = P1^1;

void delay1(u16 i)
{
  while(i--);
} 

void delay()		//50000??@11.0592MHz
{
	
	TMOD &= 0xF0;	
	TMOD |= 0x01;
 	
	TL0 = 0x00;		
	TH0 = 0x4C;	
  EA = 1;
  ET0 = 1;
  TR0 = 1;
	
}

	   
void main()
{
   while(1)
   {
      led1 = 0;
		  delay1(1000);
		  led1 = 1;
		  delay();
		  led2 = 0;
		  while(1);
	 
   }
}

void stcc() interrupt 1
{
	TL0 = 0x00;		
	TH0 = 0x4C;	
	if(count++ == 1200)
	{
		count = 0;
	  led2 = 1;
	}
}