/*--------------------------------------------------------------------------------
 * Project name:
 *
     RGB water-lamp board delay subroutines
 *
 * Function description:
 *
     1. Millisecond-level delay
     2. 100-millisecond-level delay
 *
 *
 * Configuration:
     MCU:             STC15F104E
     Crystal:         internal crystal: 33MHz
     Extension module: -
     Software:        Keil.C51.V9.01
 *
 * Remarks:
 *
--------------------------------------------------------------------------------*/

#ifndef _DELAY_H_
#define _DELAY_H_

/*------------------------------- Function declarations ------------------------*/
void DelayMs(unsigned char m);
void Delay100Ms(unsigned char m);

#endif

//-----------------------------------THE END------------------------------------*/
