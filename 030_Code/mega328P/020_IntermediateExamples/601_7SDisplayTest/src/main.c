/*
 * File:            main.c
 * Author:          Daniel Martinez
 *                  dagmtzs@gmail.com
 * Date:            Sun Jan 01 00:00:00 AM CST 2024
 * Target:          ATmega328P
 * Description:     This is a template for ATmega328P programs written in C
 */

/************************************************
 *       << Area for macro definitions >>       *
 ************************************************/
#define F_CPU 16000000UL
#define DELAY_TIME_MS 1000U
/* #define __NO_BCD_ONELINER */

/************************************************
 *       << Area for includes >>                *
 ************************************************/
#include <avr/io.h>
#include <util/delay.h>

void initialize(void);
void number_to_74LS47(uint8_t);

/************************************************
 *       << Main function >>                    *
 ************************************************/
void main(void)
{
    uint8_t counter = 0;

    /* Initialization */
    initialize();

    /* Main loop */
    while (1U) 
    {
        for (counter = 0; counter < 10; counter++)
        {
            number_to_74LS47(counter);
            _delay_ms(DELAY_TIME_MS);
        }
    }   
}

/************************************************
 *       << Initialization routine >>           *
 ************************************************/
void initialize(void)
{
    DDRB |= (1 << PORTB0);
    DDRC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3);
}

void number_to_74LS47(uint8_t number)
{
#ifdef __NO_BCD_ONELINER
    /* mask1 stores the last 4 bits of what is being stored in PORTC, so 
    that is not modified*/
    uint8_t mask1 = PORTC & 0xF0;
    
    /* mask2 stores the first 4 bits of what is being stored in "number", so 
    no number bigger than 4 bits is sent*/
    uint8_t mask2 = number & 0x0F;

    /* mask3 stores the addition of mask1 and mask2, that is, the last nibble 
    what we don't want to modify) and the first (what we want to update */
    PORTC = mask1 | mask2;
#else
    /* This is a one liner that does the same */
    PORTC = (PORTC & 0xF0) | (number & 0x0F);
#endif /* __NO_BCD_ONELINER */
}