#include <stdio.h>	
#include <string.h>																										 
#include "NUC1xx.h"
#include "LCD_Driver.h"
#include "DrvRTC.h"
static uint8_t Alarm_E=1;
// RTC Interrupt Handler
void RTC_IRQHandler(void)
{
	uint32_t clock;
	char TEXT_RTC[16]="RTC :           ";
	/* tick */
	if(inpw(&RTC->RIIR)&0x2)
 	{
		clock=inpw(&RTC->TLR)&0xFFFFFF;
		sprintf(TEXT_RTC+6,"%02x",(clock>>16)&0xFF);
		sprintf(TEXT_RTC+9,"%02x",((clock)>>8)&0xFF);
		sprintf(TEXT_RTC+12,"%02x",clock&0xFF);
		TEXT_RTC[8]=':';
		TEXT_RTC[11]=':';
		Show_Word(1,13,' ');
		print_lcd(1, TEXT_RTC);
		outpw(&RTC->RIIR,2);
	}
	/* alarm */
	if(inpw(&RTC->RIIR)&0x1) 
	{
		print_lcd(2, "RTC Alarm !!!");
		GPIOC->DOUT&=0xefff;
		Alarm_E=0;
		outpw(&RTC->RIIR,1);
	}
}
int32_t main (void)
{
	UNLOCKREG();
	SYSCLK->PWRCON.XTL32K_EN = 1;//Enable 32KHz for RTC clock source
	SYSCLK->PWRCON.XTL12M_EN = 1;//Enable 12MHz crystal
	SYSCLK->CLKSEL0.HCLK_S = 0;
	LOCKREG();
	Initial_panel();  
	clr_all_panel();
	print_lcd(0,"Smpl_RTC");	                        
	InitRTC();
	START_RTC();/* Step 2. Initiate and unlock RTC module */
	/* Step 3. Initiate Time and Calendar  setting */
	RTC->TSSR.HR24_HR12     =1;//Set 24hour mode
	//Set time and calendar for loading register, Calendar�� 09/1/19, Time�� 13:20:00
	set_CLR(2,3,0,3,1,8);
	set_TLR(1,0,2,8,2,0);
	/* Step 4. Set alarm interrupt */
	//Set time and calendar for alarm register , Calendar�� 09/1/19, Time�� 13:30:00
	set_CAR(2,3,0,3,1,8);
	set_TAR(1,0,3,0,2,0);		
	//Enable alarm interrupt
	RTC->RIER.AIER = 1;
	RTC->RIER.TIER = 1;
	NVIC_EnableIRQ(RTC_IRQn);		 	
	/* Synch field transmission & Request Identifier Field transmission*/
	while(Alarm_E)
	{
		UNLOCKREG();
		WDT->WTCR.WTR =0;//Write 1 to clear for safety
		LOCKREG();	
	}
	while(1)
	{
		__NOP();
	}
}



