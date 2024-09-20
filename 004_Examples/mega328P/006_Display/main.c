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
// Included in compilation command
// #define F_CPU 16000000U

#define DISPLAY_DDR     DDRC
#define DISPLAY_PORT    PORTC

#define ONE_SECOND_MS   1000

/*********************************************************************************************************************************
 *          << Area for includes >>
 ********************************************************************************************************************************/
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
    DDRC = 0x0F; // DDRC = 0b00001111

    uint8_t counter = 0;

    // Enter an infinite loop
    while (1)
    {        
        updateDigitValue(counter);
        // _delay_ms(ONE_SECOND_MS);
        // counter++;
        // if (counter == 10)
        // {
        //     counter = 0;
        // }
        
    }
}

void updateDigitValue(uint8_t value)
{
    if (value <= 9)
    {
        PORTC &= 0b11110000;
        PORTC |= value;
    }
    else
    {
        PORTC &= 0b11110000;
        PORTC |= 10;
    }
    
}
