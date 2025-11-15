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
// Included in compilation command (?)
#define F_CPU 16000000UL

#define DISPLAY_DDR     DDRB
#define DISPLAY_PORT    PORTB

#define REPETITIONS 20U
#define DELAY_TIME_MS 3U

/*********************************************************************************************************************************
 *          << Area for includes >>
 ********************************************************************************************************************************/
#include <stdint-gcc.h>
#include <avr/io.h>
#include <util/delay.h>

/*********************************************************************************************************************************
 *          << Area for function definitions >>
 ********************************************************************************************************************************/
// Este es el PROTOTIPO de una función
void updateDigitValue(uint8_t value);

/*********************************************************************************************************************************
 *          << Main function >>
 ********************************************************************************************************************************/
int main()
{	
    DDRB = 0x0F;
    DDRC = 0x0F;

    // Enter an infinite loop
    while (1)
    {   
        for (uint8_t i = 0; i < 10; i++)
        {
            PORTC = ((DISPLAY_PORT & 0xF0) | (i & 0x0F));                
            for (uint8_t i = 0; i < REPETITIONS; i++)
            {
                for (uint8_t j = 0U; j < 4U; j++)
                {
                    PORTB = (1U << j);
                    _delay_ms(DELAY_TIME_MS);
                }
            }
        }
    }
}


