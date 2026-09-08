/*------------------------------------------------------------------------------------
 * Project name:
 *
     MCU 8-bit Full-Color Water Lamp Template V1.0
 *
 * Function description:
 *
 *
 * Configuration:
 *     - MCU       : STC15W204S
 *     - CPU clock : 30MHz
-------------------------------------------------------------------------------------*/

/*********************************** Includes **************************************/
#include "STC15W.h"
#include "ws2812.h"		 // LED driver routines
#include "delay.h"		 // delay routines
#include "uart.h"
/******************************* Function prototypes *******************************/

void Flash_WS2812(unsigned char *p);         // Whole-board flash; pass a color
void LED_Water(unsigned char *p);            // Water-light from the inside out
void LED_Water_Color(unsigned char *p);      // Water-light from the inside out with color change
void LED_Single_Flower(void);                // Single ring blooms one LED at a time
void Water_lamp(unsigned char *p);           // Light in order from 1 to 37
void DIY_SNOW(unsigned char *p);             // From the outside in, display in array color order, up to five colors
void Flower(void);
void Flower_In(void);                        // Light up ring by ring
void Gradual_change(unsigned char *p);       // Gradual brightening
void Breathing_WS2812(unsigned char level,unsigned char Color); // Breathing effect; two parameters: first is the base color, second is the color

void WS2812_Close(void);
void WS2812_1_5Line(unsigned char *p,unsigned char line);        // Light a whole ring at once; two parameters: first is the color, second is the ring number (1-5)
void WS2812_1_5Line_In(unsigned char *p,unsigned char line);     // Light a whole ring at once, inner ring color kept; two parameters: first is the color, second is the ring number (1-5)
void WS2812_1_5Line_Single(unsigned char *p,unsigned char line); // Water-light on the given ring; two parameters: first is the color, second is the ring number (1-5)
void WS2812_LineIn_Single(unsigned char *p,unsigned char line);  // Outermost ring flows while the inside stays fully lit; two parameters: first is the color, second is the ring number (2-5)

void Change_Color(unsigned char *p);
void sovle(unsigned char m);

/********************************* Global variables *********************************/

unsigned char green[3]={50,0,0};   // Green, Red, Blue
unsigned char red[3]={0,50,0};     // Red
unsigned char blue[3]={0,0,50};    // Blue
unsigned char white[3]={25,25,25}; // White
unsigned char org[3]={5,80,0};     // Orange
unsigned char close[3]={0,0,0};
unsigned char color[7][3]={{0,50,0},{25,255,0},{100,255,0},{50,0,0},{0,0,50},{0,230,230},{50,50,50}}; // Red, Orange, Yellow, Green, Blue, Purple, White
xdata unsigned char buffer[64];
unsigned char buf_data=0x00;
// unsigned char dis_count=0;
/********************************** Main program ************************************/

void  main()
{
	DelayMs(1000);			  // Power-on delay
	UartInit();
	UART1_SendString("STC15W204S\r\nUart is ok !\r\n");// Send a string to verify initialization succeeded
	DelayMs(1000);
 	ResetDataFlow();
 	WS2812_Close();
	// Main loop
	while(1)
	{
// 		UART1_SendData(buf_data);
		sovle(buf_data);
// 		Flash_WS2812(white);
	}
}

//-------------------------------------------------------------------------------
// Subroutine: sovle(unsigned char m)
// Function: Select the effect based on the data received from the UART
// Parameter: effect selector
// Notes:
//-------------------------------------------------------------------------------
void sovle(unsigned char m)
{
	switch(m)
	{
		case 0x00:
			DIY_SNOW(color);
			Delay100Ms(50);
			WS2812_Close();
			Water_lamp(white);
			ResetDataFlow();
			Flash_WS2812(white);
			ResetDataFlow();

			WS2812_Close();
			Delay100Ms(5);

			LED_Water_Color(color);
			WS2812_Close();
			Delay100Ms(5);

			LED_Single_Flower();
			WS2812_Close();
			Flower_In();
			WS2812_Close();
			Change_Color(color);
			WS2812_Close();
			Gradual_change(blue);
			Delay100Ms(50);
			WS2812_Close();
			Breathing_WS2812(0,Red);
			Breathing_WS2812(1,Red);
			Breathing_WS2812(1,Green);
			Breathing_WS2812(1,Blue);
			WS2812_Close();
		break;
		case 0x01:
			WS2812_Close();
			DIY_SNOW(color);
		break;
		case 0x02:
			WS2812_Close();
			Flower_In();
		break;
		case 0x03:
			WS2812_Close();
			Breathing_WS2812(0,Red);
			Breathing_WS2812(1,Red);
			Breathing_WS2812(1,Green);
			Breathing_WS2812(1,Blue);
		break;
		case 0x04:
			WS2812_Close();
			Gradual_change(org);

		break;
		case 0x05:
			WS2812_Close();
			LED_Single_Flower();

		break;
		case 0x06:
			WS2812_Close();
			Change_Color(red);

		break;
		case 0x07:
			WS2812_Close();
			LED_Water_Color(color);
		break;
		case 0x08:
			WS2812_Close();
			Flash_WS2812(white);
		break;
		case 0x09:
			WS2812_Close();
		break;
	}
}

//-------------------------------------------------------------------------------
// Subroutine: WS2812_Close(void)
// Function: Turn off all 37 LEDs
// Parameter: none
// Notes:
//-------------------------------------------------------------------------------
void WS2812_Close(void)
{
	unsigned char count_sum;
	for(count_sum=0;count_sum<37;count_sum++)
	{
		SendOnePix(close);
	}
	ResetDataFlow();
}
//-------------------------------------------------------------------------------
// Subroutine: WS2812_1_5Line(unsigned char *p,unsigned char line)
// Function: Light a whole ring at once; two parameters: first is the color,
//           second is the ring number (1-5)
// Parameter: the pointer is the color array, line is the ring number (1-5)
// Notes:
//-------------------------------------------------------------------------------
void WS2812_1_5Line(unsigned char *p,unsigned char line)
{

	unsigned char count_sum;
	unsigned char m=1;
	switch(line)
	{
		case 1:
			for(count_sum=0;count_sum<=36;count_sum++)// 36-LED loop
			{
				if(count_sum==36)
				{
					SendOnePix(p);
				}
				else
					SendOnePix(close);
			}
			ResetDataFlow();
			break;
		case 2:
			for(count_sum=0;count_sum<36;count_sum++)// 36-LED loop
			{
				if(count_sum%6==0)
				{
					SendOnePix(p);
				}
				else
					SendOnePix(close);
			}
			ResetDataFlow();
			break;
		case 3:
			for(count_sum=0;count_sum<36;count_sum++)// 36-LED loop
			{
				if(count_sum%6==1)
				{
					SendOnePix(p);
				}
				else
					SendOnePix(close);
			}
			ResetDataFlow();
			break;
		case 4:
			for(count_sum=0;count_sum<36;count_sum++)// 36-LED loop
			{
				if(count_sum%6==2)
				{
					SendOnePix(p);
				}
				else
					SendOnePix(close);
			}
			ResetDataFlow();
			break;
		case 5:
			for(count_sum=0;count_sum<36;count_sum++)// 36-LED loop
			{
				if(count_sum==3*m)
				{
					SendOnePix(p);
				}
				else if(count_sum==(3*m)+1)
				{
					SendOnePix(p);
				}
				else if(count_sum==(3*m)+2)
				{
					SendOnePix(p);
					m+=2;
				}
				else
					SendOnePix(close);
			}
			m=1;
			ResetDataFlow();
			break;
	}
}






//-------------------------------------------------------------------------------
// Subroutine: WS2812_1_5Line_In(unsigned char *p,unsigned char line)
// Function: Light a whole ring at once, inner ring color kept
// Parameter: the pointer is the 2D color array, line is the ring number (1-5)
// Notes:
//-------------------------------------------------------------------------------
void WS2812_1_5Line_In(unsigned char *p,unsigned char line)
{
	unsigned char count_sum;
	unsigned char m=1;
	unsigned char k=0;
	switch(line)
	{
		case 1:
			for(count_sum=0;count_sum<=36;count_sum++)// 36-LED loop
			{
				if(count_sum==36)
				{
					SendOnePix(&p[(3*k)]);
				}
				else
					SendOnePix(close);
			}
			ResetDataFlow();
			break;
		case 2:
			for(count_sum=0;count_sum<36;count_sum++)// 36-LED loop
			{
				k=1;
				if(count_sum%6==0)
				{
					SendOnePix(&p[(3*k)]);
				}
				else
					SendOnePix(close);
			}
			ResetDataFlow();
			break;
		case 3:
			for(count_sum=0;count_sum<36;count_sum++)// 36-LED loop
			{
				if(count_sum%6==1)
				{
					k=2;
					SendOnePix(&p[(3*k)]);
				}
				else if(count_sum%6==0)
				{
					k=1;
					SendOnePix(&p[(3*k)]);
				}
				else
					SendOnePix(close);
			}
			ResetDataFlow();
			break;
		case 4:
			for(count_sum=0;count_sum<36;count_sum++)// 36-LED loop
			{
				if(count_sum%6==2)
				{
					k=3;
					SendOnePix(&p[(3*k)]);
				}
				else if(count_sum%6==1)
				{
					k=2;
					SendOnePix(&p[(3*k)]);
				}
				else if(count_sum%6==0)
				{
					k=1;
					SendOnePix(&p[(3*k)]);
				}
				else
					SendOnePix(close);
			}
			ResetDataFlow();
			break;
		case 5:
			for(count_sum=0;count_sum<36;count_sum++)// 36-LED loop
			{
				if(count_sum==3*m)
				{
					k=4;
					SendOnePix(&p[(3*k)]);
				}
				else if(count_sum==(3*m)+1)
				{
					k=5;
					SendOnePix(&p[(3*k)]);
				}
				else if(count_sum==(3*m)+2)
				{
					k=6;
					SendOnePix(&p[(3*k)]);
					m+=2;
				}
				else if(count_sum%6==2)
				{
					k=3;
					SendOnePix(&p[(3*k)]);
				}
				else if(count_sum%6==1)
				{
					k=2;
					SendOnePix(&p[(3*k)]);
				}
				else if(count_sum%6==0)
				{
					k=1;
					SendOnePix(&p[(3*k)]);
				}
				else
					SendOnePix(close);
			}
			m=1;
			ResetDataFlow();
			break;
	}
}
//-------------------------------------------------------------------------------
// Subroutine: WS2812_1_5Line_Single(unsigned char *p,unsigned char line)
// Function: Water-light on the given ring; two parameters
// Parameter: the pointer is the 2D color array, line is the ring number (1-5)
// Notes:
//-------------------------------------------------------------------------------
void WS2812_1_5Line_Single(unsigned char *p,unsigned char line)// Water-light on the given ring; two parameters: first is the color, second is the ring number (1-5)
{
	unsigned char count_sum;
	unsigned char count=0;
	unsigned char m=1;
	switch(line)
	{
		case 1:
			for(count_sum=0;count_sum<37;count_sum++)
			{
				if(count_sum==36)
				{
					SendOnePix(p);
				}
				else
					SendOnePix(close);
			}
			Delay100Ms(2);
			ResetDataFlow();
			break;
		case 2:
			for(count_sum=0;count_sum<36;count_sum++)// 36-LED loop
			{
				for(count=0;count<=count_sum;count++)// Within the first count_sum LEDs, guarantee how many are lit
				{
					if(count%6==0)
					{
						SendOnePix(p);
					}
					else
						SendOnePix(close);
				}
				DelayMs(10);
			}
			ResetDataFlow();
			break;
		case 3:
			for(count_sum=0;count_sum<36;count_sum++)// 36-LED loop
			{
				for(count=0;count<=count_sum;count++)// Within the first count_sum LEDs, guarantee how many are lit
				{
					if(count%6==1)
					{
						SendOnePix(p);
					}
					else
						SendOnePix(close);
				}
				DelayMs(10);
			}
			ResetDataFlow();
			break;
		case 4:
			for(count_sum=0;count_sum<36;count_sum++)// 36-LED loop
			{
				for(count=0;count<=count_sum;count++)// Within the first count_sum LEDs, guarantee how many are lit
				{
					if(count%6==2)
					{
						SendOnePix(p);
					}
					else
						SendOnePix(close);
				}
				DelayMs(10);
			}
			ResetDataFlow();
			break;
		case 5:
			for(count_sum=0;count_sum<36;count_sum++)
			{
				for(count=0;count<=count_sum;count++)
				{
					if(count==3*m)
					{
						SendOnePix(p);
					}
					else if(count==(3*m)+1)
					{
						SendOnePix(p);
					}
					else if(count==(3*m)+2)
					{
						SendOnePix(p);
						m+=2;
					}
					else
						SendOnePix(close);
				}
				ResetDataFlow();
				Delay100Ms(1);
				m=1;
			}
			ResetDataFlow();
	}
}

//-------------------------------------------------------------------------------
// Subroutine: WS2812_LineIn_Single(unsigned char *p,unsigned char line)
// Function: Water-light on the given ring, inner ring stays lit; two parameters
// Parameter: the pointer is the color array, line is the ring number (2-5)
// Notes:
//-------------------------------------------------------------------------------
void WS2812_LineIn_Single(unsigned char *p,unsigned char line)
{
	unsigned char count;
	unsigned char count_sum;
	unsigned char m=1;
	switch(line)
	{
		case 2:
			for(count_sum=0;count_sum<37;count_sum++)
			{
				for(count=0;count<=count_sum;count++)
				{
					if(count%6==0)
					{
						SendOnePix(p);
					}
					else
						SendOnePix(close);
				}
				DelayMs(20);
			}
			ResetDataFlow();
			break;
		case 3:
			for(count_sum=0;count_sum<36;count_sum++)
			{
				for(count=0;count<=count_sum;count++)
				{
					if(count%6==1)
					{
						SendOnePix(p);
					}
					else if(count%6==0)
					{
						SendOnePix(p);
					}
					else
						SendOnePix(close);
				}
// 				ResetDataFlow();
				DelayMs(20);
			}
			ResetDataFlow();
			break;
		case 4:
			for(count_sum=0;count_sum<36;count_sum++)
			{
				for(count=0;count<=count_sum;count++)
				{
					if(count%6==2)
					{
						SendOnePix(p);
					}
					else if(count%6==1)
					{
						SendOnePix(p);
					}
					else if(count%6==0)
					{
						SendOnePix(p);
					}
					else
						SendOnePix(close);
				}
// 				ResetDataFlow();
				DelayMs(20);
			}
			ResetDataFlow();
			break;
		case 5:
			for(count_sum=0;count_sum<36;count_sum++)
			{
				for(count=0;count<=count_sum;count++)
				{
					if(count==3*m)
					{
						SendOnePix(p);
// 				m+=2;
					}
					else if(count==(3*m)+1)
					{
						SendOnePix(p);
					}
					else if(count==(3*m)+2)
					{
						SendOnePix(p);
						m+=2;
					}

					else if(count%6==2)
					{
						SendOnePix(p);
					}
					else if(count%6==1)
					{
						SendOnePix(p);
					}
					else if(count%6==0)
					{
						SendOnePix(p);
					}
					else
						SendOnePix(close);
				}
				DelayMs(70);
				m=1;
			}
			ResetDataFlow();
			break;
	}
}
















//-------------------------------------------------------------------------------
// Subroutine: LED_Water(unsigned char *p)
// Function: Water-light from the inside out
// Parameter: the pointer is the color array
// Notes:
//-------------------------------------------------------------------------------
void LED_Water(unsigned char *p)// Water-light from the inside out
{
	WS2812_1_5Line_Single(p,1);// The 37th LED gets no new data, so it keeps its previous state
	WS2812_1_5Line_Single(p,2);
// 	LED_3count(p);
// 	LED_4count(p);
// 	LED_5count(p);
	WS2812_LineIn_Single(p,3);
	WS2812_LineIn_Single(p,4);
	WS2812_LineIn_Single(p,5);
}

//-------------------------------------------------------------------------------
// Subroutine: LED_Water_Color(unsigned char *p)
// Function: Water-light from the inside out
// Parameter: the pointer is the 2D array of multiple colors
// Notes:
//-------------------------------------------------------------------------------
void LED_Water_Color(unsigned char *p)// Water-light from the inside out, color change
{
	unsigned char k=0;
	for(k=0;k<7;k++)
	{
		LED_Water(&p[(3*k)]);
	}
}
//-------------------------------------------------------------------------------
// Subroutine: LED_Single_Flower(void)
// Function: Single ring blooms one LED at a time
// Parameter: none
// Notes:
//-------------------------------------------------------------------------------
void LED_Single_Flower(void)// Single ring blooms one LED at a time
{
		WS2812_1_5Line_Single(green,1);
		DelayMs(50);
		WS2812_Close();
// 		LED_2_Single(c);
	WS2812_1_5Line_Single(red,2);
		DelayMs(50);
// 		LED_3_Single(b);
	WS2812_1_5Line_Single(blue,3);
		DelayMs(50);
// 		LED_4_Single(a);
	WS2812_1_5Line_Single(org,4);
		DelayMs(50);
// 		LED_5_Single(d);
	WS2812_1_5Line_Single(white,5);
		DelayMs(20);
		WS2812_Close();
}

//-------------------------------------------------------------------------------
// Subroutine: Flash_WS2812(unsigned char *p)
// Function: Whole-board flash
// Parameter: the pointer is the color array
// Notes:
//-------------------------------------------------------------------------------
void Flash_WS2812(unsigned char *p)
{
	unsigned char count;
	WS2812_Close();
	ResetDataFlow();
	Delay100Ms(5);
	for(count=0;count<37;count++)
	{
		SendOnePix(p);
	}
	Delay100Ms(5);
}

//-------------------------------------------------------------------------------
// Subroutine: DIY_SNOW(unsigned char *p)
// Function: From the outside in, display in array color order, up to five colors
// Parameter: the pointer is the 2D array of multiple colors
// Notes:
//-------------------------------------------------------------------------------
void DIY_SNOW(unsigned char *p)// From the outside in, display in array color order, up to five colors
{
	unsigned char count;
	unsigned char m=1;
	unsigned char k=0;
	for(count=0;count<36;count++)
	{
		if(count==3*m)
			{
				SendOnePix(&p[(3*k)]);
			}
			else if(count==(3*m)+1)
			{
				SendOnePix(&p[(3*k)]);
			}
			else if(count==(3*m)+2)
			{
				SendOnePix(&p[(3*k)]);
				m+=2;
			}
			else if(count%6==2)
			{
				k=1;
				SendOnePix(&p[(3*k)]);
			}
			else if(count%6==1)
			{
				k=2;
				SendOnePix(&p[(3*k)]);
			}
			else if(count%6==0)
			{
				k=3;
				SendOnePix(&p[(3*k)]);
			}
	}
	if(count==36)
	{
		k=4;
		SendOnePix(&p[(3*k)]);
	}
	m=1;
	ResetDataFlow();
}

//-------------------------------------------------------------------------------
// Subroutine: Water_lamp(unsigned char *p)
// Function: Light in order from 1 to 37
// Parameter: the pointer is the color array
// Notes:
//-------------------------------------------------------------------------------
void Water_lamp(unsigned char *p)// Light in order from 1 to 37
{
	unsigned char count;
	unsigned char count_sum;
	for(count_sum=0;count_sum<37;count_sum++)
	{
		for(count=0;count<=count_sum;count++)
		{
			SendOnePix(p);
		}
		ResetDataFlow();
		DelayMs(50);
	}
	ResetDataFlow();
}

void Flower(void)
{
	WS2812_1_5Line(green,1);
	Delay100Ms(5);
	WS2812_1_5Line(green,1);
	WS2812_1_5Line(red,2);
	Delay100Ms(5);
	WS2812_1_5Line(green,1);
	WS2812_1_5Line(red,2);
	WS2812_1_5Line(blue,3);
	Delay100Ms(5);
	WS2812_1_5Line(green,1);
	WS2812_1_5Line(red,2);
	WS2812_1_5Line(blue,3);
	WS2812_1_5Line(white,4);
	Delay100Ms(5);
	WS2812_1_5Line(green,1);
	WS2812_1_5Line(red,2);
	WS2812_1_5Line(blue,3);
	WS2812_1_5Line(white,4);
	WS2812_1_5Line(org,5);
	Delay100Ms(5);
}
//-------------------------------------------------------------------------------
// Subroutine: Flower_In(void)
// Function: Light up ring by ring, inner color kept
// Parameter: none
// Notes:
//-------------------------------------------------------------------------------
void Flower_In(void)
{
		WS2812_1_5Line_In(color,1);
		Delay100Ms(5);
		WS2812_1_5Line_In(color,2);
		Delay100Ms(5);
		WS2812_1_5Line_In(color,3);
		Delay100Ms(5);
		WS2812_1_5Line_In(color,4);
		Delay100Ms(5);
		WS2812_1_5Line_In(color,5);
		Delay100Ms(5);
}

//-------------------------------------------------------------------------------
// Subroutine: Gradual_change(unsigned char *p)
// Function: Gradual brightening
// Parameter: the pointer is the color array
// Notes:
//-------------------------------------------------------------------------------
void Gradual_change(unsigned char *p)
{
	unsigned char i,j,count;
	unsigned char x[3];

 		for(j=0;j<3;j++)
		{
			x[j]=p[j];
		}
// 	for(i=0;i<50;i++)
// 	{
// 		for(j=0;j<3;j++)
// 		{
// 			x[j]++;
// 		}
		for(count=0;count<37;count++)
		{
	 		for(j=0;j<3;j++)
			{
				x[j]++;
			}
			SendOnePix(x);
		}
		ResetDataFlow();
}

//-------------------------------------------------------------------------------
// Subroutine: Breathing_WS2812(unsigned char level,unsigned char Color)
// Function: Gradual brightening (breathing)
// Parameter: level 0 means white; level 1 lets Color decide which of R, G, B
//            fades
// Notes:
//-------------------------------------------------------------------------------
void Breathing_WS2812(unsigned char level,unsigned char Color)// Breathing effect; two parameters: first is the base color, second is the color
{
	unsigned char i,j,count;
	unsigned char x[3]={0,0,0};
	switch(level)
	{
			case 0:
				for(i=0;i<50;i++)
				{
					for(j=0;j<3;j++)
					{
						x[j]++;
					}
					for(count=0;count<37;count++)
					{
						SendOnePix(x);
					}
					Delay100Ms(1);
				}
				break;
			case 1:
				for(i=0;i<50;i++)
				{
					for(j=0;j<3;j++)
					{
						switch(Color)
						{
							case Green:
								x[0]++;
								break;
							case Red:
								x[1]++;
								break;
							case Blue:
								x[2]++;
								break;
						}
					}
					for(count=0;count<37;count++)
					{
						SendOnePix(x);
					}
					Delay100Ms(1);
				}
				break;
	}
}

//-------------------------------------------------------------------------------
// Subroutine: Change_Color(unsigned char *p)
// Function: All 37 LEDs change color together
// Parameter: the pointer is the 2D array of multiple colors
// Notes:
//-------------------------------------------------------------------------------
void Change_Color(unsigned char *p)
{
	unsigned char count,k;
	for(k=0;k<8;k++)
	{
		for(count=0;count<37;count++)
		{
			SendOnePix(&p[(3*k)]);
		}
		ResetDataFlow();
		Delay100Ms(5);
		WS2812_Close();
	}
}


//-------------------------------------------------------------------------------
// Subroutine: uart_sever()
// Function: UART interrupt service routine, receives data
// Parameter:
// Notes:
//-------------------------------------------------------------------------------
void uart_sever() interrupt 4
{
	static unsigned int data_temp=0;
	if(RI==1)// Data reception complete
	{
		RI=0;
		buf_data=SBUF;
		buffer[data_temp]=buf_data;
		data_temp++;
		UART1_SendData(buf_data);
		if(buf_data==0x0D)
		{
			data_temp=0;
		}
	}
}

/********************************** END *****************************************/
