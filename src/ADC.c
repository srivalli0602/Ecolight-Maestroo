#include<lpc21xx.h>
#include "ADC_defines.h"
#include "pinconnectblock.h"
#include "pindefine.h"
#include "types.h"
#include "delaydef.h"
void Init_ADC(void)
{
	//make 0.27 as gpio
     PINSEL1&=(~(3<<(27-16)*2));
	//cfg p0.27 as analog AINO
	cfportpin(PORT0,PIN27,FUN2);
	//active the adc peripheral,set adc clk
	ADCR=PDN_BIT|CLKDIV_VALUE;
}
void Read_ADC(u32 CHNO, u32 *AdcDval,f32 *eAR)
{
	//clear the channel bits
	ADCR&=~(255<<0);
	//select channel number and start conversion 
	ADCR|=CHNO|START_CONV;
	//wait for conv upto 3usec
	delayus(3);
	//check or wait for done bit status
	while(((ADDR>>DONE_BIT)&1)==0);
	///stop the conversion
	ADCR&=~(START_CONV);
	//extract result from addr
	*AdcDval=(ADDR>>RESULT)&(0x3FF);
	//get the equivalent analog reading
	*eAR=(3.3/1023)*(*AdcDval);
}
