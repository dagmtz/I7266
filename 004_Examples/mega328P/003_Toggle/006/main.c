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
    // PCICR = (1 << PCIE1);
    // Set Pin Change Mask Register to enable PCINT13
    // PCMSK1 = (1 << PCINT13);

    volatile bool latch = 0;

    // Set INT0 and INT1 to 0b00
    EICRA = 0;
    // Set INT0 mask enable
    EIMSK |= 0x01;

    // SEt Interrupt flag in SREG
    sei();

    // Set PORTD2 as input 
    DDRD &= ~(1 << PORTD2);

    // Set PORTD7 as output
	DDRD |= (1 << PORTD7);

    // Enter an infinite loop
	while (1)
	{

        if (toggle == 1)
        {
            PORTD ^= _BV(PORTD7);
            _delay_ms(DEBOUNCE_DELAY);
            while ((PIND & _BV(PORTD2)) == 0)
            {
                ;;
            }
            _delay_ms(DEBOUNCE_DELAY);
            toggle = 0;
        }
	}
}

ISR(INT0_vect)
{ 
    toggle = 1;
}