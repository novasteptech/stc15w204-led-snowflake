/*----------------------------------------------------------------------------
 * Project name:
 *
     RGB LED driver
 *
 * Function description:
 *
     1. Send the data of the whole array so the LEDs display it
     2. Send the data of the whole array to the LED display starting from a
        specified pixel
     3. Send the reset signal
 *
 * Configuration:
     MCU:             STC15W204S
     Crystal:         internal crystal: 33MHz
     Extension module: -
     Software:        Keil.C51.V9.01
 *
 * Remarks:
 *
------------------------------------------------------------------------------*/

#ifndef _WS2812_H_
#define _WS2812_H_

#define Blue 0
#define Red 1
#define Green 2
/******************************* Communication interface configuration **********/

sbit DI = P5^5;						    // Data port

/*---------------------------- Number of LEDs connected in series --------------*/
#define SNUM 32
/*-------------------------------- Function declarations ------------------------*/
void SendOnePix(unsigned char *ptr);	// Send the 24-bit data of one LED
void ResetDataFlow(void);				// Chip reset pulse, prepare for sending the next frame
// void SendOneFrame(unsigned char *ptr);	// Send one frame of data
// void SendSameColor(unsigned char *ptr,unsigned char cnt);  // Send the same color several times
// void SendOneFrameFrom(unsigned char i,unsigned char *ptr);// Send one frame of data
// 														  // starting from the i-th pixel
// void SendOneFrameSince(unsigned char i,unsigned char *ptr);// Send the data of the i-th pixel
// 														   // onwards
#endif

//-------------------------THE END------------------------*/
