/*
 * File:                    main.c
 * Author:                  Daniel Martinez
 *                          dagmtzs@gmail.com
 * Date:                    yyyy-mm-dd 
 * Target:                  ATmega32A
 * Description:             This is a template for ATmega32A programs written in C
 */

/*********************************************************************************************************************************
 *          << Area for macro definitions >>
 ********************************************************************************************************************************/
#define F_CPU 1000000U
#define LED_DELAY 500U

/*********************************************************************************************************************************
 *          << Area for includes >>
 ********************************************************************************************************************************/
#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


/*********************************************************************************************************************************
 *          << Main function >>
 ********************************************************************************************************************************/
int main()
{	
    // Set Interrupt Sense Control 2 to zero so it triggers an interrupt on a rising edge on INT2
    MCUCSR |= _BV(ISC2);
    // Set General Interrupt Control Register 6, External Interrupt Request 2 Enable
    GICR |= _BV(INT2);
    // Set Global Interrupt Enable Flag in SREG
    sei();
    
    // Enable PORTA0 as output
    DDRA |= (1 << PORTA0); 
    // Enable PORTB2 as input, this is not neccesary
    DDRB &= ~(_BV(PORTB2));

	while (1)
	{	
        
	}
	
}

ISR(INT2_vect)
{ 
    PORTA ^=  _BV(PORTA0);
}
