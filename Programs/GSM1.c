

#include <stdio.h>
#include "Driver\DrvUART.h"
#include "Driver\DrvGPIO.h"
#include "Driver\DrvSYS.h"
#include "NUC1xx.h"
#include "NUC1xx-LB_002\LCD_Driver.h"


char TEXT[16] = " ";

/*---------------------------------------------------------------------------------------------------------*/
/* UART Callback function                                                                           	   */
/*---------------------------------------------------------------------------------------------------------*/
void UART_INT_HANDLE(void)
{
 
	uint8_t bInChar[2] ;

	while(UART0->ISR.RDA_IF==1) 
	{
		DrvUART_Read(UART_PORT0,bInChar,2);	
		DrvGPIO_ClrBit(E_GPC, 13);
 
	}			
	
}

int32_t main()
{
	uint8_t  i =0;
	uint8_t  dataout[4],dataout1[16], number[10]; 
	STR_UART_T sParam;

	UNLOCKREG();
  DrvSYS_Open(48000000);
	LOCKREG();
	Initial_panel();
	clr_all_panel();
	print_lcd(0,"Alaa GSM Demo");
  print_lcd(1,"GSM SIM300"); 
  print_lcd(2,"Calling..."); 	
	/* Set UART Pin */
	DrvGPIO_InitFunction(E_FUNC_UART0);		

	/* UART Setting */
    sParam.u32BaudRate 		= 9600;
    sParam.u8cDataBits 		= DRVUART_DATABITS_8;
    sParam.u8cStopBits 		= DRVUART_STOPBITS_1;
    sParam.u8cParity 		= DRVUART_PARITY_NONE;
    sParam.u8cRxTriggerLevel= DRVUART_FIFO_1BYTES;

	/* Set UART Configuration */
 	if(DrvUART_Open(UART_PORT0,&sParam) != E_SUCCESS);  

	DrvUART_EnableInt(UART_PORT0, DRVUART_RDAINT, UART_INT_HANDLE);  

	 
 	  dataout[0] = 'A';	
		dataout[1] = 'T';
 		dataout[2] = 0x0d;	
	 	dataout[3] = 0x0a;	  
    dataout1[0] = 'A';	
		dataout1[1] = 'T';	
		dataout1[2] = 'D';	
		dataout1[3] = 'x';
		dataout1[4] = 'x';
		dataout1[5] = 'x';
		dataout1[6] = 'x';	
		dataout1[7] = 'x';
		dataout1[8] = 'x';	
		dataout1[9] = 'x';
		dataout1[10] ='x';	
		dataout1[11] ='x';
		dataout1[12] ='x';
    dataout1[13] =';';		
	 	dataout1[14] = 0x0d;	
	 	dataout1[15] = 0x0a;  
		
		DrvGPIO_ClrBit(E_GPC, 12); 
		
		for (i=3;i<13;i++)
		{
			number[i-3] =dataout1[i];
		}
		sprintf(TEXT ,"%s",number);
	  print_lcd(3,TEXT);
		//Transmitting AT Commands
 		DrvUART_Write(UART_PORT0, dataout1 ,16);
		DrvGPIO_ClrBit(E_GPC, 14);
 while(1)
 {
 }
	//DrvUART_Close(UART_PORT0);
} 