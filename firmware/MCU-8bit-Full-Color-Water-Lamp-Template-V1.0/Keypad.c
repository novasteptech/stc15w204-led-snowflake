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
     MCU:             STC15W204E
     Crystal:         internal crystal: 33MHz
     Extension module: -
     Software:        Keil.C51.V9.01
 *
 * Remarks:
 *
--------------------------------------------------------------------------------*/

#include "STC15W.h"
#include "Keypad.h"
#include "Delay.h"

//-------------------------------------------------------------------------------
// Subroutine: Keypad_IO_Init(void)
// Function: port initialization, enable interrupts
//-------------------------------------------------------------------------------
void Keypad_IO_Init(void)
{
	Button_1=1;
	Button_2=1;

	// Enable INT0 interrupt
	INT0 = 1;
    IT0 = 1;                    // Set INT0 interrupt type (1: falling edge only, 0: rising and falling edge)
    EX0 = 1;                    // Enable INT0 interrupt

	// Enable INT1 interrupt
	INT1 = 1;
    IT1 = 1;                    // Set INT1 interrupt type (1: falling edge only, 0: rising and falling edge)
    EX1 = 1;                    // Enable INT1 interrupt
}

//-------------------------------------------------------------------------------
// Subroutine: unsigned char GetKey(void)
// Function: get the key value of the pressed key
// Notes: returns 1 when key 1 is pressed, returns 2 when key 2 is pressed,
//        returns 0 when no key is pressed
//-------------------------------------------------------------------------------
unsigned char GetKey(void)
{
	unsigned char i;
	Button_1=1;
	Button_2=1;

	if(Button_1==0)				// If key 1 is pressed
	{
		DelayMs(10);			// Delay 10 milliseconds before checking
		if(Button_1==0)
		{
			for(i=0;i<100;i++)
			{
				if(Button_1==1)	// If the key is released within the timeout, key 1 is considered triggered
				{
					return 1;	// Return 1, meaning key 1 was pressed
				}
				DelayMs(10);	// Timeout is 1 second; if the key is not released within 1 second, the press is ignored
			}
		}
	}
	if(Button_2==0)				// If key 1 is not pressed, start checking key 2
	{
		DelayMs(10);
		if(Button_2==0)
		{
			for(i=0;i<100;i++)
			{
				if(Button_2==1)	// If the key is released within the timeout, key 2 is considered triggered
				{
					return 2;	// Return 2, meaning key 2 was pressed
				}
				DelayMs(10);	// Timeout is 1 second
			}
		}
	}
	return 0;
}
