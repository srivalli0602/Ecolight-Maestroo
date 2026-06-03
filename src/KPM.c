#include<lpc21xx.h>
#include "types.h"
#include "kpm_defines.h"
#include "defines.h"
#include "lcd.h"
/*u32 kpmLUT[4][4]={{'1','2','3','/'},
									{'4','5','6','*'},
									{'7','8','9','-'},
									{'C','0','=','+'}};*/
u8 kpmLUT[4][4]={{'7','8','9','/'},
									{'4','5','6','*'},
									{'1','2','3','-'},
									{'C','0','=','+'}};
void Init_KPM(void)
{
	//cfg rows(p0.16 to p0.19) as output pins
	WRITENIBBLE(IODIR1,ROW0,15);
}
u32 ColScan(void)
{
	//scan the 4 cols at a time
	if((READNIBBLE(IOPIN1,COL0))<15) //when switch is pressed
	{
		return 0;
	}
	else //when no switch is pressed
		return 1;
}
u32 RowCheck(void)
{
	u32 rno;
	for(rno=0; rno<4; rno++)
	{
		WRITENIBBLE(IOPIN1,ROW0,~(1<<rno));
		if(ColScan()==0)
		{
			break;
		}
	}
	//make ROWs as defaults
	WRITENIBBLE(IOPIN1,ROW0,0x0);
	
	return rno;
}
u32 ColCheck(void)
{
	u32 cno;
	for(cno=0; cno<4; cno++)
	{
		if(READBIT(IOPIN1,(COL0+cno))==0)
			break;
	}
	
	return cno;
}
u32 KeyScan(void)
{
	u32 rno, cno, keyv;
	//wait for switch press
	while(ColScan());
	//find rno
	rno=RowCheck();
	//find cno
	cno=ColCheck();
	//take key from kpmLUT
	keyv=kpmLUT[rno][cno];
	
	//wait for switch release
	while(!ColScan());
	//return keyv
	return keyv;
}
u32 ReadNum(void)
{
	u8 key;
	u32 sum=0;
	while(1)
	{
		key=KeyScan();
		if(key>='0' && key<='9')
		{
			sum= (sum*10)+(key-'0');
			CharLCD(key);
		}
		else if(key=='C')
		{
			sum=0;
			CmdLCD(0xC0);
			StrLCD("                ");
			CmdLCD(0xC0);
		}
		else 
		{
			break;
		}
		
	}
	return sum;
}
void CALCULATOR(void)
{
	u32 key;
	u8 choice;
	u32 num1=0,num2=0,res=0;
	CmdLCD(0x01);
	CmdLCD(0x80);
	StrLCD("Menu1.+2.-3.*4./");
	choice=KeyScan();
	CharLCD(choice);
	if(choice< '1' || choice >'4')
	{
		CmdLCD(0xC0);
		StrLCD("invalid choice");
		return ;
	}
	
// ---- Read num1 ----
CmdLCD(0xC0);
StrLCD("N1:(=end)   "); 
CmdLCD(0xC9);            
num1 = ReadNum();
// ---- Read num2 ----
CmdLCD(0xC0);
StrLCD("N2:(=end)   ");
CmdLCD(0xC9);
num2 = ReadNum();
	switch(choice)
	{
		case '1': res=num1+num2;
		        break;
		case '2': res=num1-num2;
		        break;
		case '3': res=num1*num2;
		        break;
		case '4': 
		if(num2!=0)
		{
			res=num1/num2;
		}
		else
		{
			CmdLCD(0xC0);
			StrLCD("Div error");
			return ;
		}
		break;
			
	}
	CmdLCD(0xC0);
	StrLCD("            ");
	CmdLCD(0xC0);
	StrLCD("RES:");
	CmdLCD(0xC4);
	U32LCD(res);
	
	
	
}








