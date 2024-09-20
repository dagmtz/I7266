/*
 * File:                    main.c
 * Author:                  Daniel Martinez
 *                          dagmtzs@gmail.com
 * Date:                    Fri Feb 16 12:44:31 AM CST 2024
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
#include <avr/io.h>
#include <util/delay.h>


/*********************************************************************************************************************************
 *          << Main function >>
 ********************************************************************************************************************************/
int main()
{	
    // Set PORTD7 as output
	DDRD |= (1 << PORTD7);
    // Set PORTC5 as input and activate Pull-Up Resistor
    DDRC &= ~(1 << PORTC5);
    PORTC |= (1 << PORTC5);

    // Enter an infinite loop
	while (1)
	{
        if (~PINC & (1 << PINC5))
        {  
            _delay_ms(DEBOUNCE_DELAY);
            if (~PINC & (1 << PINC5))
            {
                PORTD ^= (1 << PORTD7);
                while (~PINC & (1 << PINC5))
                {
                    ;;
                }
                
            }

        }
	}
}
