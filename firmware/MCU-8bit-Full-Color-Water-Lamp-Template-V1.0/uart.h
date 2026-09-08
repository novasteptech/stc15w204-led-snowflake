#ifndef __UART_H__
#define __UART_H__


void UartInit(void)		//9600bps@33MHz
{
	SCON = 0x50;
	AUXR |= 0x01;
	AUXR |= 0x04;
	T2L = 0xA5;
	T2H = 0xFC;
	AUXR |= 0x10;
	ES=1;
	EA=1;
}

void UART1_SendData(unsigned char dat)
{
	SBUF=dat;
	while(!TI);
	TI=0;
}

void UART1_SendString(unsigned char *s)
{
	while(*s != 0)
	{
		UART1_SendData(*s++);
	}
}

#endif
