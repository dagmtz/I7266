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
#define LED_DELAY 200U
#define REPETITIONS 4

/*********************************************************************************************************************************
 *          << Area for includes >>
 ********************************************************************************************************************************/
#include <stdint.h>

#include <avr/io.h>
#include <util/delay.h>


/*********************************************************************************************************************************
 *          << Main function >>
 ********************************************************************************************************************************/
int main()
{	
    // Set all PORTA bits as outputs
	DDRA |= 0xFF;
    PORTA = 1;
    char count = 0;
    
    // Enter an infinite loop
	while (1)
	{	
		while(count < REPETITIONS)
        {
            _delay_ms(LED_DELAY);
            PORTA = (PINA << 1);
            if( PORTA >= 0x10 )
            {
                PORTA = 1;
                count++;
            }
        }
        
        count = 0;
        PORTA = 8;

        while(count < REPETITIONS)
        {
            _delay_ms(LED_DELAY);
            PORTA = (PINA >> 1);
            if( PORTA <= 0 )
            {
                PORTA = 8;
                count++;
            }
        }
        
        count = 0;
        PORTA = 1;

	}
	
}
