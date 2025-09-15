#include <avr/io.h>
#include "usart.h"

void USART_init( unsigned int ubrr )
{
    /* Set baud rate */
    UBRR0H = (unsigned char) (ubrr >> 8);
    UBRR0L = (unsigned char) ubrr;

    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);

    /* Set frame format: 8 data, 2 stop bit, */
    UCSR0C = (1<<USBS0) | (3<<UCSZ00);
}

void USART_putc( char character )
{
    while ( !( UCSR0A & (1<<UDRE0)) )
    {
        /* Wait for empty transmit buffer */
        ;
    }
    
    /* Put data into buffer, sends the data */
    UDR0 = character;   
}

void USART_puts( char *p_string )
{
    /* Check if there is still more chars to send from the null char */
    while(*p_string != 0x00)
    {  
        /* Send one char at a time */
        USART_putc(*p_string); 

        /* Go to next character */
        p_string++;
    }    
}

char USART_getc( void )
{
    /* Wait to receive a character */
    while(!(UCSR0A & (1 << RXC0)))
    {
        ;
    }

    /* Return the received character */
    return UDR0;
}

void USART_getl(char* buf, uint8_t length)
{
    uint8_t bufferIndex = 0;
    char character;

    /*  while received character is not carriage return 
        and end of buffer has not been reached */ 
    do
    {
        /* receive character */
        character = USART_getc();

        /* store character in buffer */
        buf[bufferIndex++] = character;
    }
    while((bufferIndex < length) && (character != '\r'));

    // ensure buffer is null terminated
    buf[bufferIndex] = 0;
}


