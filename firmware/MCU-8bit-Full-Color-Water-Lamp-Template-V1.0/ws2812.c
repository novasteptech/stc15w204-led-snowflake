/*----------------------------------------------------------------------------
 * Project name:
 *
     RGB LED driver
 *
 * Function description:
 *
     1. Send the data of the whole array so the LEDs display it
     2. Send the reset signal
 *
 * Configuration:
     MCU:             STC15W204S
     Crystal:         internal crystal: 33MHz
------------------------------------------------------------------------------*/

#include "STC15W.h"
#include <intrins.h>
#include "ws2812.h"


//-------------------------------------------------------------------------------
// Subroutine: ResetDataFlow(void)
// Function: reset, prepare for the next transmission.
// Notes: after setting DI to 0, delay about 65us
//-------------------------------------------------------------------------------
void ResetDataFlow(void)
{
	unsigned char i,j;
	DI=0;					// After DI is set to 0, delay 50us or more to achieve frame reset
	for(i=0;i<50;i++)		// At 33MHz this delays 65us
	{
		for(j=0;j<20;j++)
		{
			;
		}
	}
}
//-------------------------------------------------------------------------------
// Subroutine: SendOnePix(unsigned char *ptr)
// Function: send the 24-bit data of one pixel
// Parameter: the received parameter is a pointer; this function sends the three
//            consecutive bytes of data at the address the pointer points to
// Notes:
//-------------------------------------------------------------------------------
void SendOnePix(unsigned char *ptr) //unsigned char a[3]={0,0,50};0=0x00=0000 0000   0x80=1000 0000
{
	unsigned char i,j;
	unsigned char temp;

	for(j=0;j<3;j++)
	{
		temp=ptr[j];
		for(i=0;i<8;i++)
		{
			if(temp&0x80)		 // Send from the high bit
			{
				DI=1;			 // Send a "1" code
				_nop_();		 // This nop() must not be omitted; it delays for a specified time; crystal frequency 33MHz
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();// One instruction cycle; for 1T, one cycle is one clock cycle (33ns)
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();

				DI=0;
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
			}
			else				// Send a "0" code
			{
				DI=1;
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();

				DI=0;
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
				_nop_();
			}
			temp=(temp<<1);		 // Shift left
		}
	}
}

/**********************************THE END**********************************/
