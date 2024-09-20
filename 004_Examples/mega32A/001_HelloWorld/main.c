/*
 * File:                    main.c
 * Author:                  Daniel Martinez
 *                          dagmtzs@gmail.com
 * Date:                    2024-02-05
 * Target:                  ATmega32A
 * Description:             This program is a "Hello World!" implementation for the 
 *                          ATmega32A. It turns on an LED connected to PORTD7.
 */

/* #define F_CPU 1000000U */

#include <avr/io.h>
#include <util/delay.h>

int main()
{	
    // Set PORTD bit 7 direction as output via Data Direction Register
	DDRD |= (1 << PORTD7);

    // Enter an infinite loop
	while (1)
	{	
        // Toggle PORTD bit 7
		PORTD ^= (1 << PORTD7); 
        _delay_ms(500);
	}
	
}
