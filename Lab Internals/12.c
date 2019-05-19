#include<stdio.h>
#include "NUC1xx.h"
#include "DrvSYS.h"
#include "DrvGPIO.h"
#include "LCD_Driver.h"
int32_t main()
{
	uint16_t num;
	UNLOCKREG();
	DrvSYS_Open(48000000);
	LOCKREG();
	Initial_panel();
	clr_all_panel();
	while(1)
	{
		num=DrvGPIO_GetPortBits(E_GPA);
		if(num==0xffff)
		 	print_lcd(1,"!grounded");
		else
		 	print_lcd(1,"grounded");
	}
}
