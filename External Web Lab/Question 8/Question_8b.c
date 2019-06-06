#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "Driver\DrvGPIO.h"
#include "Driver\DrvADC.h"

void EINT1Callback() {
    DrvGPIO_ClrBit(E_GPB,11); // GPB11 = 0 to turn on Buzzer
    DrvSYS_Delay(100000); // Delay
    DrvGPIO_SetBit(E_GPB,11); // GPB11 = 1 to turn off Buzzer
    DrvSYS_Delay(100000);
}

int main (void)
{
    UNLOCKREG(); 
    DrvSYS_Open(48000000);
    LOCKREG();
    DrvGPIO_Open(E_GPB, 11, E_IO_OUTPUT); // initial GPIO pin GPB11 for controlling Buzzer
    DrvGPIO_Open(E_GPB,15,E_IO_INPUT);
    DrvGPIO_EnableEINT1(E_IO_BOTH_EDGE,E_MODE_EDGE,EINT1Callback);
    while(1) {
    }
}