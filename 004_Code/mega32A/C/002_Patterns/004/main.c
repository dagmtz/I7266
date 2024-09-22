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
#define LED_DELAY 100U
#define TOP 0x80
#define BOTTOM 1U
#define BIT_STEP 1U

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
    DDRA = 0xFF;
    PORTA = BOTTOM;

	while (1)
	{
        while(PORTA < TOP)
        {
            _delay_ms(LED_DELAY);
            PORTA <<= BIT_STEP;
        }        
        while(PORTA > BOTTOM)
        {
            _delay_ms(LED_DELAY);
            PORTA >>= BIT_STEP;
        }        
	}
	
}
