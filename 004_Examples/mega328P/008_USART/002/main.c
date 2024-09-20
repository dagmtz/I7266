 /*
  * Name:		    main.c
  * Author:		    dagmtzs@gmail.com
  * Target:		    ATmega328P
  * Date:		    dom 14 abr 2024 12:52:59 CST
  *
  * Description:	Main source file for a dummy project.
  * 			    The objective is a project to serve as reference 
  * 			    on how to create basic libraries for avr-gcc.
  */

#include <avr/io.h> 
#include <util/delay.h>

#include "usart.h"

int main( void )
{
    PORTD = 0x80;
    USART_Init(51);
    while(1)
    {
        PORTD ^= _BV(PORTD7);
        USART_Transmit('H');
        USART_Transmit('e');
        USART_Transmit('l');
        USART_Transmit('l');
        USART_Transmit('o');
        USART_Transmit(' ');
        USART_Transmit('W');
        USART_Transmit('o');
        USART_Transmit('r');
        USART_Transmit('l');
        USART_Transmit('d');
        USART_Transmit('!');
        USART_Transmit('\r');
        USART_Transmit('\n');
       	_delay_ms(1000); 
    }
}

