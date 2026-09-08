/*--------------------------------------------------------------------------------
 * Project name:
 *
     RGB water-lamp board keyboard driver
 *
 * Function description:
 *
     1. Get the key value of the pressed key
 *
 * Copyright:
 *
     (c) Flywing Electronics, 2014.
 *
 * History:
     2014-03-15:
       - Initial version V1.0.0;
 *
 * Configuration:
     MCU:             STC15W204S
     Crystal:         internal crystal: 33MHz
     Extension module: -
     Software:        Keil.C51.V9.01
 *
 * Remarks:
 *
--------------------------------------------------------------------------------*/

#ifndef _KEYPAD_H_
#define _KEYPAD_H_


/******************************* Communication interface configuration **********/

sbit Button_1 = P3^2;	 // Button 1 connected to P3.2
sbit Button_2 = P3^3;	 // Button 2 connected to P3.3

/*------------------------------- Function declarations ------------------------*/

void Keypad_IO_Init(void);		 // Key port initialization
unsigned char GetKey(void);		 // Get key value

#endif

//-------------------------THE END------------------------*/
