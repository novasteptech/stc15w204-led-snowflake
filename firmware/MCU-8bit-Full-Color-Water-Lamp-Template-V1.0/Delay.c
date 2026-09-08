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
 * Configuration:
     MCU:             STC15F104E
     Crystal:         internal crystal: 33MHz
     Extension module: -
     Software:        Keil.C51.V9.01
 *
 * Remarks:
 *
--------------------------------------------------------------------------------*/

#include "Delay.h"

//-------------------------------------------------------------------------------
// Subroutine: void DelayMs(unsigned char m)
// Function: millisecond delay subroutine.
//-------------------------------------------------------------------------------
void DelayMs(unsigned char m)
{
	unsigned char i,j,k;
	for(k=0;k<m;k++)
	{
		for(i=0;i<60;i++)
		{
			for(j=0;j<78;j++)
			{
				;
			}
		}
	}
}
//-------------------------------------------------------------------------------
// Subroutine: void Delay100Ms(unsigned char m)
// Function: 100ms delay subroutine (at a crystal frequency of 33MHz)
//-------------------------------------------------------------------------------
void Delay100Ms(unsigned char m)
{
	unsigned char i,j,k,l;
	for(l=0;l<m;l++)
	{
		for(k=0;k<98;k++)
		{
			for(i=0;i<60;i++)
			{
				for(j=0;j<78;j++)
				{
					;
				}
			}
		}
	}
}
