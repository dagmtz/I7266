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
#define F_CPU 16000000U
#define DEBOUNCE_DELAY 30U

/*********************************************************************************************************************************
 *          << Area for includes >>
 ********************************************************************************************************************************/
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

// Declare flag for interrupt
volatile bool toggle = 0;

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

    // Enter an infinite loop
	while (1)
	{
        if (toggle == 1)
        {  
            _delay_ms(DEBOUNCE_DELAY);
            PORTB ^= (1 << PORTB1);
            toggle = 0;
        }
	}
}

ISR(PCINT1_vect)
{ 
    toggle = 1;
}