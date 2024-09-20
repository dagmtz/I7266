/*
 * File:                    main.c
 * Author:                  Daniel Martinez
 *                          dagmtzs@gmail.com
 * Date:                    Thu Feb 15 11:29:12 PM CST 2024
 * Target:                  ATmega328P
 * Description:             This is a template for ATmega328P programs written in C
 */

/*********************************************************************************************************************************
 *          << Area for macro definitions >>
 ********************************************************************************************************************************/
#define F_CPU 16000000U
#define LED_DELAY 125U
#define BOTTOM 0x01
#define TOP 0xFF
#define BIT_STEP 1U

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
    // Set all PORTD bits as outputs
	DDRD |= 0xFF;
    PORTD = BOTTOM;

    // Enter an infinite loop
	while (1)
	{
        while(PORTD != TOP)
        {
            _delay_ms(LED_DELAY);
            PORTD <<= BIT_STEP;
            PORTD++;
        }
        while(PORTD != 0)
        {
            _delay_ms(LED_DELAY);  
            PORTD <<= BIT_STEP;
        }
	}
}
