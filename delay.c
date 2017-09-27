/*
 * delay.c
 *
 *  Created on: 20/09/2017
 *      Author: Daniel Barragán and Alejandro Ávila
 */

#include "DataTypeDefinitions.h"
#include "delay.h"

void delay_cycles(uint32 cycles){
	register int a1 __asm ("r0");//a1 is linked with the r0 direction
	a1 = cycles; // assign the cycles in the refister r0
		__asm(  "LOOP:");
		__asm("SUB %0,%1,#1":"=r"(a1):"r"(a1));//
		__asm("CMP r0, #0");
		__asm("BNE LOOP");
}

void delay_msOrus(uint16 time, uint32 systemClock, uint8 msOrus){
	time = time/1000; //divide time by 1000, to make it mili seconds
	if(FALSE != msOrus) time = time/1000; //if needed microseconds we divide by 1000 again
	systemClock = systemClock/4;//adjusting the systemClock value
	delay_cycles(time*systemClock);//make the delay in mili/micro seconds

}

/*register float a1 __asm ("r0");
register float a2 __asm ("r1");
register float a3 __asm ("r2");
register float a4 __asm ("r3");
a1 = time;
a2 = msOrus;
a3 = systemClock;
a4 = 1000;
__asm("UDIV r0,r0,r3");
__asm("CMP r1,#1");
__asm("BNE CONTINUE");
__asm("UDIV r0,r0,r3");
__asm("CONTINUE:");
__asm("MOV r3,#2");
__asm("MUL r0,r0,r2");
__asm("UDIV r0,r0,r3");
delay_cycles(a1);
*/
