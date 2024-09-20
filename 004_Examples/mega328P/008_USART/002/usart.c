 /*
  * Name:		    usart.c
  * Author:		    dagmtzs@gmail.com
  * Target:		    ATmega328P
  * Date:		    dom 14 abr 2024 12:52:59 CST
  *
  * Description:	Module to provide basic USART functions
  */

#include <avr/io.h>
#include "usart.h"

 void USART_Init( unsigned int ubrr )
{
    /* Set baud rate */
    UBRR0H = (unsigned char) (ubrr >> 8);
    UBRR0L = (unsigned char) ubrr;

    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);
    /* Set frame format: 8 data, 2 stop bit, */
    UCSR0C = (1<<USBS0) | (3<<UCSZ00);
}

void USART_Transmit( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) )
    ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}