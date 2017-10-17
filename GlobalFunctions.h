/*
 * GloalFunctions.h
 *
 *  Created on: 09/10/2017
 *      Author: Ryzen X by EGM
 */

#ifndef GLOBALFUNCTIONS_H_
#define GLOBALFUNCTIONS_H_

void delay(uint16 delay)
{
	volatile uint16 counter;

	for(counter=delay; counter > 0; counter--)
	{
	}
}


#endif /* GLOBALFUNCTIONS_H_ */
