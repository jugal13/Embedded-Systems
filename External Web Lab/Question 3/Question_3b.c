#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvGPIO.h"
#include "Driver\DrvUART.h"
#include "Driver\DrvSYS.h"
#include "LCD_Driver.h"

void EINT1Callback(void) 
{
	DrvGPIO_ClrBit(E_GPB,11); // GPB11 = 0 to turn on Buzzer
	DrvGPIO_SetBit(E_GPB,11); // GPB11 = 1 to turn off Buzzer	
	Initial_panel(); 
	clr_all_panel();
	print_lcd(0,"Hello");
	DrvSYS_Delay(10000000);	    
	clr_all_panel();
}

int main (void)
{
	UNLOCKREG();
	DrvSYS_SetOscCtrl(E_SYS_XTL12M, 1); // external 12MHz Crystal
	//DrvSYS_Delay(5000);                 // delay for stable clock
	DrvSYS_SelectHCLKSource(0);         // clock source = 12MHz Crystal
	LOCKREG();
	DrvGPIO_Open(E_GPB, 11, E_IO_OUTPUT); // initial GPIO pin GPB11 for controlling Buzzer
	DrvGPIO_Open(E_GPB, 15, E_IO_INPUT);                             // configure external interrupt pin GP
	DrvGPIO_EnableEINT1(E_IO_BOTH_EDGE, E_MODE_EDGE, EINT1Callback); // configure external interrupt
	while(1)
	{
	}
}
