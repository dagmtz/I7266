/*
 * File:                    main.c
 * Author:                  Daniel Martinez
 *                          dagmtzs@gmail.com
 * Date:                    Fri Feb 16 01:12:47 AM CST 2024
 * Target:                  ATmega328P
 * Description:             This is a template for ATmega328P programs written in C
 */

/*********************************************************************************************************************************
 *          << Area for macro definitions >>
 ********************************************************************************************************************************/
// Included in compilation command
// #define F_CPU 16000000U

#define FOSC 16000000U
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#define DEFAULT_DELAY_MS    100

/*********************************************************************************************************************************
 *          << Area for includes >>
 ********************************************************************************************************************************/
#include <avr/io.h>
#include <util/delay.h>
    
#include <stdlib.h>

/*********************************************************************************************************************************
 *          << Area for function definitions >>
 ********************************************************************************************************************************/
void USART_Init( unsigned int );
void USART_Transmit( unsigned char );

/*********************************************************************************************************************************
 *          << Main function >>
 ********************************************************************************************************************************/
void main( void )
{	
    USART_Init(MYUBRR);
    while (1)
    {
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
    }
    
}

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