#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "Driver\DrvGPIO.h"

void EINT1Callback() {
	DrvGPIO_ClrBit(E_GPC, 15); // output Low to turn on LED
	DrvSYS_Delay(300000);	   // delay 
	DrvGPIO_SetBit(E_GPC, 15); // output Hi to turn off LED
	DrvSYS_Delay(300000);	   // delay
	DrvGPIO_ClrBit(E_GPC, 14); // output Low to turn on LED
	DrvSYS_Delay(300000);	   // delay 
	DrvGPIO_SetBit(E_GPC, 14); // output Hi to turn off LED
	DrvSYS_Delay(300000);	 
	DrvGPIO_ClrBit(E_GPC, 13); // output Low to turn on LED
	DrvSYS_Delay(300000);	   // delay 
	DrvGPIO_SetBit(E_GPC, 13); // output Hi to turn off LED
	DrvSYS_Delay(300000);	 
	DrvGPIO_ClrBit(E_GPC, 12); // output Low to turn on LED
	DrvSYS_Delay(300000);	   // delay 
	DrvGPIO_SetBit(E_GPC, 12); // output Hi to turn off LED
	DrvSYS_Delay(300000);
}
	
void Init_LED() // Initialize GPIO pins{
	DrvGPIO_Open(E_GPC, 15, E_IO_OUTPUT); // GPC12 pin set to output mode
	DrvGPIO_SetBit(E_GPC, 15);
	DrvGPIO_Open(E_GPC, 14, E_IO_OUTPUT); // GPC12 pin set to output mode
	DrvGPIO_SetBit(E_GPC, 14);
	DrvGPIO_Open(E_GPC, 13, E_IO_OUTPUT); // GPC12 pin set to output mode
	DrvGPIO_SetBit(E_GPC, 13);
	DrvGPIO_Open(E_GPC, 12, E_IO_OUTPUT); // GPC12 pin set to output mode
	DrvGPIO_SetBit(E_GPC, 12);
}

int main (void){
	UNLOCKREG();			    // unlock register for programming
  	DrvSYS_Open(48000000);      // set System Clock to run at 48MHz
	LOCKREG();				    // lock register from programming
	Init_LED();        // Initialize LEDs (four on-board LEDs below LCD panel)	
	DrvGPIO_Open(E_GPB, 15, E_IO_INPUT);
	DrvGPIO_EnableEINT1(E_IO_BOTH_EDGE, E_MODE_EDGE, EINT1Callaback);
	while(1) {
	}
	
}
