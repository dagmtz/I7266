/*
 * File:                    main.c
 * Author:                  Daniel Martinez
 *                          dagmtzs@gmail.com
 * Date:                    Thu Feb 15 11:48:34 PM CST 2024
 * Target:                  ATmega328P
 * Description:             This is a template for ATmega328P programs written in C
 */

/*********************************************************************************************************************************
 *          << Area for macro definitions >>
 ********************************************************************************************************************************/
#define F_CPU 16000000U
#define LED_DELAY 500U

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
    
    // Enter an infinite loop
	while (1)
	{
        PORTD ^= (1 << PORTD7);
        _delay_ms(LED_DELAY); 
	}
}
