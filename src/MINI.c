#include<lpc21xx.h>
#include "pinconnectblock.h"
#include "pindefine.h"
#include "LCD.h"
#include "KPM.h"
#include "kpm_defines.h"
#include "RTC.h"
#include "types.h"
#include "ADC.h"
#include "delaydef.h"
#include "ADC_defines.h"
#define EINT0_CHNO 14
#define LEDs 24
#define CH0 (1<<0)
#define SUN 0
#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define SAT 6
void Init_EINT0(void);
void eint0_isr(void)__irq;
volatile int menu_flag;
u32 AdcDval;
f32 eAR;
u32 key;
s32 hour,min,sec,date,month,year,day;
void RTC_Edit_Menu(void);
void Edit_hour(void);
void Edit_Min(void);
void Edit_Sec(void);
void Edit_day(void);
void Edit_date(void);
void Edit_Month(void);
void Edit_year(void);
void Main_Menu(void);
u8 cgramLUT[8] =
{
	0x04,
	0x0E,
	0x0E,
	0x0E,
	0x1F,
	0x1F,
	0x0E,
	0x04
};
void eint0_isr(void)__irq
{
	menu_flag=1;
	//clear EINT0 flag
	EXTINT|=(1<<0);
	//end of interrupt
	VICVectAddr=0;
}
int main()
{
	Init_LCD();
	Init_KPM();
	RTC_Init();
	SetRTCTimeInfo(3,30,00);//hr,min,sec
	SetRTCDateInfo(19,5,2026);//dt,mnth,yr
	SetRTCDay(TUE);//day
	BuildCGRAM(cgramLUT,8);
	IODIR1|=255<<LEDs;
	Init_ADC();
	Init_EINT0();
	IOSET1=255<<LEDs;
	while(1)
	{
		GetRTCTimeInfo(&hour,&min,&sec);
		DisplayRTCTime(hour,min,sec);
		GetRTCDateInfo(&date,&month,&year);
		DisplayRTCDate(date,month,year);
		GetRTCDay(&day);
		DisplayRTCDay(day);
    //Light_display();
     if(hour>=18||hour<=6)
    {
       Read_ADC(CH0,&AdcDval,&eAR);
        CmdLCD(0xC0+10);
        StrLCD("A:");
        if(AdcDval<10)
         StrLCD("000");
        else if(AdcDval<100)
         StrLCD("00");
        else if(AdcDval<1000)
         StrLCD("0");
        U32LCD(AdcDval);
			 if(AdcDval>300)
			 {
				 IOCLR1=255<<LEDs;
			 }
			 else
			 {
				 IOSET1=255<<LEDs;
			 }
			 
		 }
		 else
		 {
			 IOSET1=255<<LEDs;
		 }
      if(menu_flag==1)
	      {
		       menu_flag=0;
		       Main_Menu();
				}
	};
	
}
void Init_EINT0(void)
{
	//P0.16 -> EINT0
	//cfportpin(PORT0,PIN16,FUN2);
	PINSEL1=(PINSEL1&(~0x03))|0x01;
	//clear pending interrupt
	EXTINT=(1<<0);
	//edge trigger
	EXTMODE|=1<<0;
	//falling edge trigger
	EXTPOLAR&=~(1<<0);
	//IRQ mode
	VICIntSelect&=~(1<<EINT0_CHNO);
	//load ISR address
	VICVectAddr0=(u32)eint0_isr;
	//enable slot0 + channel
	VICVectCntl0=(1<<5)|EINT0_CHNO;
	//enable interrupt
	VICIntEnable|=1<<EINT0_CHNO;
}
void Main_Menu(void)
{
	  u32 key;
	while(1)
	{
		CmdLCD(0x01);
		CmdLCD(0x80);
		StrLCD("1.EDIT_RTC");
		CmdLCD(0xC0);
		StrLCD("2.Exit");
		key=ReadNum();
		switch(key)
		{
			case 1: RTC_Edit_Menu();
			         break;
			case 2: CmdLCD(0x01);
			         return;
			default : StrLCD("invalid choice");
			        
		}
		
	}
}
void RTC_Edit_Menu(void)
{
	CmdLCD(0x01);
	CmdLCD(0x80);
	StrLCD("1.H 2.M 3.S 4.D");
	CmdLCD(0xC0);
	StrLCD("5.Dt 6.M 7.Y 8.Ex");
	key=ReadNum();
	switch(key)
	{
		case 1:Edit_hour();
		       break;
		case 2:Edit_Min();
		       break;
		case 3:Edit_Sec();
		       break;
		case 4:Edit_day();
		       break;
		case 5:Edit_date();
		       break;
		case 6:Edit_Month();
		       break;
		case 7:Edit_year();
		       break;
		case 8:return;
		      
		default:StrLCD("invalid choice");
		       
	}
	
}
void Edit_hour(void)
{
	u32 hr;
	CmdLCD(0x01);
	StrLCD("ENTER HOUR");
	CmdLCD(0xC0);
	hr = ReadNum();
	if(hr <= 23)
	{
		HOUR = hr;
		CmdLCD(0x01);
		StrLCD("UPDATED");
	}
	else
	{
		CmdLCD(0x01);
		StrLCD("INVALID");
	}
	delayms(1000);
}
void Edit_Min(void)
{
	u32 min;
	CmdLCD(0x01);
	StrLCD("ENTER MIN");
	CmdLCD(0xC0);
	min=ReadNum();
	if(min<=59)
	{
		MIN=min;
		CmdLCD(0x01);
		StrLCD("UPDATED");
	}
	else
	{
		CmdLCD(0x01);
		StrLCD("INVALID");
	}
	delayms(1000);
}

void Edit_Sec(void)
{
	u32 sec;
	CmdLCD(0x01);
	StrLCD("ENTER SEC");
	CmdLCD(0xC0);
	sec=ReadNum();
	if(sec<=59)
	{
		SEC=sec;
		CmdLCD(0x01);
		StrLCD("UPDATED");
	}
	else
	{
		CmdLCD(0x01);
		StrLCD("INVALID");
	}
	delayms(1000);
}

void Edit_day(void)
{
	u32 day;
	CmdLCD(0x01);
	StrLCD("DAY(0-6)");
	CmdLCD(0xC0);
	day=ReadNum();
	if(day<=6)
	{
		DOW=day;
		CmdLCD(0x01);
		StrLCD("UPDATED");
	}
	else
	{
		CmdLCD(0x01);
		StrLCD("INVALID");
	}
	delayms(1000);
}

void Edit_date(void)
{
	u32 date;
	CmdLCD(0x01);
	StrLCD("ENTER DATE");
	CmdLCD(0xC0);
	date=ReadNum();
	if(date>=1&&date<=31)
	{
		DOM=date;
		CmdLCD(0x01);
		StrLCD("UPDATED");
	}
	else
	{
		CmdLCD(0x01);
		StrLCD("INVALID");
	}
	delayms(1000);
}

void Edit_Month(void)
{
	u32 month;
	CmdLCD(0x01);
	StrLCD("ENTER MONTH");
	CmdLCD(0xC0);
	month=ReadNum();
	if(month>=1&&month<=12)
	{
		MONTH=month;
		CmdLCD(0x01);
		StrLCD("UPDATED");
	}
	else
	{
		CmdLCD(0x01);
		StrLCD("INVALID");
	}
	delayms(1000);
}

void Edit_year(void)
{
	u32 year;
	CmdLCD(0x01);
	StrLCD("ENTER YEAR");
	CmdLCD(0xC0);
	year=ReadNum();
	if(year>=2000&&year<=2099)
	{
		YEAR=year;
		CmdLCD(0x01);
		StrLCD("UPDATED");
	}
	else
	{
		CmdLCD(0x01);
		StrLCD("INVALID");
	}
	delayms(1000);
}
