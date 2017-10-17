/**
	\file 
	\brief 
		This is a starter file to use the Nokia 5510 LCD. 
		The LCD is connected as follows:
		reset-PDT0
		CE-GND
		DC-PTD3
		DIN-PTD2
		CLK-PTD1
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	1/08/2015
	\todo
	    The SPI device driver needs to be completed.
 */

 
#include "SPI.h"
#include "GPIO.h"
#include "DatatypeDefinitions.h"
#include "LCDNokia5110.h"
#include "LCDNokia5110Images.h"
#include "GlobalFunctions.h"
#include "SPI.h"

/** \brief This is the configuration structure to configure the LCD.
 * Note that is constants and it is because is only a variable used for configuration*/
const SPI_ConfigType SPI_Config={SPI_DISABLE_FIFO,
							SPI_LOW_POLARITY,
							SPI_LOW_PHASE,
							SPI_MSB,
							SPI_0,
							SPI_MASTER,
							GPIO_MUX2,
							SPI_BAUD_RATE_2,
							SPI_FSIZE_8,
							{GPIO_D,BIT1,BIT2}};
/*! This array hold the initial picture that is shown in the LCD*/
extern const uint8 ITESO[504];


int main(void)
{
	uint8 string1[]="ITESO"; /*! String to be printed in the LCD*/
	uint8 string2[]="uMs y DSPs"; /*! String to be printed in the LCD*/
	SPI_init(&SPI_Config); /*! Configuration function for the LCD port*/
	LCDNokia_init(); /*! Configuration function for the LCD */
		for(;;) {	  
			LCDNokia_clear();/*! It clears the information printed in the LCD*/
			LCDNokia_bitmap(&ITESO[0]); /*! It prints an array that hold an image, in this case is the initial picture*/
			delay(65000);
			LCDNokia_clear();
			delay(65000);
     		LCDNokia_clear();
     		LCDNokia_gotoXY(25,0); /*! It establishes the position to print the messages in the LCD*/
			LCDNokia_sendString(string1); /*! It print a string stored in an array*/
			delay(65000);
     		LCDNokia_gotoXY(10,1);
			LCDNokia_sendString(string2); /*! It print a string stored in an array*/
			delay(65000);
			LCDNokia_gotoXY(25,2);
			LCDNokia_sendChar('2'); /*! It prints a character*/
			LCDNokia_sendChar('0'); /*! It prints a character*/
			LCDNokia_sendChar('1'); /*! It prints a character*/
			LCDNokia_sendChar('5'); /*! It prints a character*/
			delay(65000);
			delay(130000);

		}
	
	return 0;
}

