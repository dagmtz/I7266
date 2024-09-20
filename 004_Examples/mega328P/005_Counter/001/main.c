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
#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>

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
    // Set Pin Change Interrupt Control to Enable PCIE1 
    PCICR = (1 << PCIE1);
    // Set Pin Change Mask Register to enable PCINT13
    PCMSK1 = (1 << PCINT13);
    // SEt Interrupt flag in SREG
    sei();

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
    
    // Enter an infinite loop
	while (1)
	{        
        
        if (toggle == 1)
        {  
            PORTB ^= (1 << PORTB1);
            
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
        if (myTime.seconds > 59)
        {
            myTime.seconds = 0;
            myTime.minutes++;
        }
        if (myTime.minutes > 59)
        {
            myTime.minutes = 0;
            myTime.hours++;
        }
        if (myTime.hours > 23)
        {
            myTime.hours = 0;
        }
    }
}
