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

/* Size for usartBuffer used in main() */
#define BUFF_SIZE   30
#define DEBOUNCE_DELAY 30U

/*********************************************************************************************************************************
 *          << Area for includes >>
 ********************************************************************************************************************************/
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <util/delay.h>

#include "usart.h"

typedef struct
{
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
}myTime_t;

// Declare flag for interrupt
volatile bool toggle = 0;
volatile myTime_t myTime;

/*********************************************************************************************************************************
 *          << Main function >>
 ********************************************************************************************************************************/
int main()
{	
    // Set prescaler for Timer1 to 64
    TCCR1B |= (1 << CS11) | (1 << CS10);
    // Enable Timer1 Overflow Interrupt via TIMSK1
    TIMSK1 |= (1 << TOIE1);

    // Set PORTB1 as output
	DDRB |= (1 << PORTB1);
    
    // Set PORTC5 as output
	DDRC |= (1 << PORTC5);
    // Enable pull-up
    PORTC |= (1 << PORTC5);

    /* ---------- USART initialization ---------- */
	uart_init( BAUD_CALC( 115200 ) ); // 8n1 transmission is set as default
	
	stdout = &uart0_io; // attach uart stream to stdout & stdin
	stdin = &uart0_io; // uart0_in and uart0_out are only available if NO_USART_RX or NO_USART_TX is defined
	
	char usartBuffer[BUFF_SIZE];

    sei();
    
    myTime.hours = 0;
    myTime.minutes = 0;
    myTime.seconds = 0;
    
    uart_puts_P( "\e[2J\e[H" );
	uart_puts_P( "\e[1;32m>USART Ready\r\n" );

    // Enter an infinite loop
	while (1)
	{        
        
        if (toggle == 1)
        {              
            printf("%02d:%02d:%02d\n", myTime.hours, myTime.minutes, myTime.seconds);
            
            toggle = 0;
        }
    }
}

ISR(PCINT1_vect)
{ 
    _delay_ms(DEBOUNCE_DELAY);
    if (~PINC & (1 << PORTC5))
    {
        toggle = 1;
        myTime.seconds++;
        if(myTime.seconds >= 60)
        {
            myTime.seconds = 0;
            myTime.minutes++;
        }
        if(myTime.minutes >= 60)
        {
            myTime.minutes = 0;
            myTime.hours++;
        }    
        if(myTime.hours >= 24)
        {
            myTime.hours = 0;
        }
    }
}
