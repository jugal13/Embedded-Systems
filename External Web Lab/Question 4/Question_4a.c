#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "DrvPWM.h"
#include "DrvADC.h"
#include "LCD_Driver.h"

int32_t main(void)
{
	char TEXT[16];
	UNLOCKREG();
	SYSCLK->PWRCON.XTL12M_EN = 1; //Enable 12Mhz and set HCLK->12Mhz
	SYSCLK->CLKSEL0.HCLK_S = 0;
	LOCKREG();
	InitPWM();
	Initial_panel();
	clr_all_panel();
	print_lcd(0, "variable reistor");
	DrvADC_Open(ADC_SINGLE_END, ADC_SINGLE_OP, 0x80, INTERNAL_HCLK, 1);
	while (1)
	{
		DrvADC_StartConvert(); // start A/D conversion
		while (DrvADC_IsConversionDone() == FALSE);
		PWMA->CMR0 = ADC->ADDR[7].RSLT << 4;
		sprintf(TEXT, "%d", ADC->ADDR[7].RSLT);
		print_lcd(1, TEXT);
	}
}
