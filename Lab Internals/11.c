#include <stdio.h>
#include "NUC1xx.h"
#include "DrvSYS.h"
#include "DrvADC.h"
#include "DrvPWM.h"
int32_t main()
{
	uint16_t x=0xffff;
	UNLOCKREG();
	SYSCLK->PWRCON.XTL12M_EN=1;
	SYSCLK->CLKSEL0.HCLK_S=0;
	LOCKREG();
	InitPWM();
	while(1)
	{
		PWMA->CMR0=x;
		DrvSYS_Delay(100000);
		x=x-1;
	}
}