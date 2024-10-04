/*
 * File:                    main.c
 * Author:                  Daniel Martinez
 *                          dagmtzs@gmail.com
 * Date:                    Thu Feb 15 10:10:08 PM CST 2024
 * Target:                  ATmega328P
 * Description:             This program is a "Hello World!" implementation for the 
 *                          ATmega328P. It turns an LED connected to PORTD7.
 */

#define F_CPU 16000000U

#include <avr/io.h>

void main(void)
{	
    // Set PORTD bit 7 direction as output via Data Direction Register
	DDRD |= (1 << PORTD7);

    // Enter an infinite loop
	while (1)
	{	
        // Turn on PORTD bit 7
		PORTD = (1 << PORTD7);
	}
	
}
