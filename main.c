#include <reg51.h>

typedef unsigned int u16;
int jishu=0;
sbit led1 = P1^5; 
sbit led2 = P1^4;
sbit led3 = P1^6;
sbit led4 = P1^1;
sbit k1 = P1^0;

void delay1(u16 i) //软延时_按键消抖函数
{
  while(i--);
} 

void delay(int i)		//50000微秒@11.0592MHz
{
	unsigned int h;
	TMOD &= 0xF0;	//设置定时器模式
	TMOD |= 0x01;
 
	for(h = 0;h < i;h++)  //定时时间设置
	{		
	TL0 = 0x00;		//设置定时初始值
	TH0 = 0x4C;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	while(!TF0);
	TF0 = 0;		//清除TF0标志
	TR0 = 0;		//关闭定时器
	}
}

/*高精度延时函数*/
//delay(20) 1秒	  
//delay(12000) 10分钟
//delay(24000) 20分钟
//delay(36000) 30分钟

void keysk()  //按键&时间设置函数
{
   
   if(k1==0)
   {
	  delay1(1000);
	  if(k1==0)
	  {
	   while(!k1)  //时间设置
	   {
	   	 delay(20);
		 jishu++;
		 if(jishu==2)	//设置10分钟延时
		 {
		    led1=0;
		 }
		 else if(jishu==5)  //设置20分钟延时
		 {
		    led1=1;
			led2=0;
		 }
		 else if(jishu==8)	//设置30分钟延时
		 {
		 led2=1;
		 led3=0;
		 }
	   }
	  }
   }

}
	   
void main()
{
   while(1)
   {
     keysk();  //按键&时间设置
	 /*定时判断*/
	 if(jishu>2&&jishu<5) 
	 {
	   led4=0;
	   delay(20);
	   jishu=0;
	   led4=1;
	   led1=1;
	 }
	 if(jishu>5&&jishu<8)
	 {
	   led4=0;
	   delay(20);
	   jishu=0;
	   led4=1;
	   led2=1;
	 }
	 if(jishu>8)
	 {
	   led4=0;
	   delay(20);
	   jishu=0;
	   led4=1;
	   led3=1;
	 }
	 
   }
}