#include<lpc21xx.h>
#include "delaydef.h"
#include "defines.h"
#include "lcd_defines.h"
#include "types.h"
void write_lcd(u8 data)
{
	//perfom write operation r/w=0
	SCLRBIT(IOCLR0,RW_PIN);
	//write data into lcd
	//IOPIN0=IOPIN0&~255<<lcd_data|data<<lcd_data
	WRITEBYTE(IOPIN0,LCD_DATA,data);///modifying here only
	//apply high pulse to latch the data into the lcd on E_pin
	SSETBIT(IOSET0,EN_PIN);//high pulse on enable
	delayus(1);
	SCLRBIT(IOCLR0,EN_PIN);//low pulse on enable
	//delay for internal process
	delayms(2);
}
void CmdLCD(u8 cmd)
{
	//select cmd register by making RS=0
	SCLRBIT(IOCLR0,RS_PIN);
	//write cammand into LCD
	write_lcd(cmd);
	
}
void CharLCD(u8 ascii)
{
	//select data reg RS=1;
    SSETBIT(IOSET0,RS_PIN);
	   write_lcd(ascii);
}
void Init_LCD(void)
{
	//config port p0.0 to p0.7(LCD data pins) as o/p pins
	WRITEBYTE(IODIR0,LCD_DATA,0xFF);
	//WRITEBYTE(IODIR1,LCD_DATA,0xFF);
	//config p0.8,p0.9,p0.10(rs,rw,en)as o/p pins
	SETBIT(IODIR0,RS_PIN);
	SETBIT(IODIR0,RW_PIN);
	SETBIT(IODIR0,EN_PIN);
	//wait for 15ms at 5 volts supply
	delayms(15);
	CmdLCD(0x30);
	delayms(5);
	CmdLCD(0x30);
	delayus(100);
	CmdLCD(0x30);//8 bit mode functionset
	CmdLCD(0x38);//8 bit mode 2 lines
	CmdLCD(0x0C);//dipla_on cur_on
	CmdLCD(0x01);//clr lcd_curser
	CmdLCD(0x06);//shift cursor right
	
}
void StrLCD(char *str)
{
	while(*str)
	{
		CharLCD(*str);
		*str++;
	}
}
void U32LCD(u32 n)
{
	u8 a[10];
	s32 i=0;
	if(n==0)
	{
		CharLCD('0');
	}
	else
	{
		while(n)
		{
			a[i++]=n%10+'0';
			n/=10;
		}
		for(--i;i>=0;i--)
		{
			CharLCD(a[i]);
		}
	}
}
void S32LCD(s32 n)
{
	if(n<0)
	{
		CharLCD('-');
		n=-n;
	}
	U32LCD(n);
	
}
void BuildCGRAM(u8 *p,u32 nbytes)
{
	s32 i;
	//go to cgram
	CmdLCD(0x40);
	for(i=0;i<nbytes;i++)
	{
		CharLCD(p[i]);
	}
	//go back to ddram
	CmdLCD(0xC0);
	
}
void F32LCD(f32 f,u8 ndp)
{
	u32 n;
	int i;
	if(f<0.0)
	{
		CharLCD('-');
		f=-f;
	}
	n=f;
	U32LCD(n);
	CharLCD('.');
	for(i=0;i<ndp;i++)
	{
		
		f=(f-n)*10;
		n=f;
		CharLCD(n+48);
	}
	
}
void BinLCD(int num)//binary value display
{
	int bitpos;
for(bitpos=7;bitpos>=0;bitpos--)
	{
		if(((num>>bitpos)&1))
		{
			CharLCD('1');
		}
		else
		{
			CharLCD('0');
		}
	}
}




