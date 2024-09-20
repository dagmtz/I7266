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
#define DEBOUNCE_DELAY 2U
#define LED_DELAY 125U
#define BOTTOM 0
#define TOP 0x80
#define BIT_STEP 1U

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

    // Set PORTC5 as input
    DDRC &= ~(1 << PORTC5);
    // Enable PORTC5 internal pull-up resistor
    PORTC |= (1 << PORTC5);
    // Set all PORTD pins as outputs
	DDRD |= 0xFF;

    bool run_pattern = 0;
    bool direction = 0;

    // Enter an infinite loop
	while (1)
	{
        if (toggle == 1)
        {
            toggle = 0;
            run_pattern = 1;
            direction  = 0;
            PORTD = 1;
        }
        
        while (run_pattern == 1 && toggle == 0 && PORTD != BOTTOM)
        {  
            _delay_ms(LED_DELAY);
            if (PORTD == TOP)
            {
                direction = 1;
            }
            if (direction == 1)
            {
                PORTD = (PORTD >> 1);
            }
            else
            {
                PORTD = (PORTD << 1);
            }
            
        }
	}
}

ISR(PCINT1_vect)
{ 
    _delay_ms(DEBOUNCE_DELAY);
    if (~PINC & (1 << PORTC5))
    {
        toggle = 1;
    }
}