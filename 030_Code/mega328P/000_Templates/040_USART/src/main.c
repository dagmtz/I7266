/*
 * File:            main.c
 * Author:          Daniel Martinez
 *                  dagmtzs@gmail.com
 * Date:            Sun Nov 10 01:51:39 PM CST 2024
 * Target:          ATmega328P
 * Description:     This is a template for ATmega328P programs written in C
 */

/************************************************
 *       << Area for macro definitions >>       *
 ************************************************/
#define F_CPU 16000000UL
#define FOSC F_CPU // Clock Speed
#define BAUD 9600
#define MYUBRR 103

/************************************************
 *       << Area for includes >>                *
 ************************************************/
#include <avr/io.h>
#include <util/delay.h>

void initialize(void);
void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );

/************************************************
 *       << Main function >>                    *
 ************************************************/
int main(void)
{
    /* Initialization */
    initialize();

    /* Main loop */
    while (1U) 
    {
        USART_Transmit('a');
        _delay_ms(1000U);
    }

}

/************************************************
 *       << Initialization routine >>           *
 ************************************************/
void initialize(void)
{
    USART_Init(MYUBRR);
}

void USART_Init( unsigned int ubrr)
{
    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);

    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) )
        ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}