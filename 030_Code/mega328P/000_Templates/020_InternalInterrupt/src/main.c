/*
 * File:            main.c
 * Author:          Daniel Martinez
 *                  dagmtzs@gmail.com
 * Date:            Sun Nov 10 01:51:39 PM CST 2024
 * Target:          ATmega328P
 * Description:     This is a template for ATmega328P programs written in C
 */

/************************************************
 *       << Area for macro definitions >>       *
 ************************************************/
#define F_CPU 16000000UL

/************************************************
 *       << Area for includes >>                *
 ************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>

void initialize(void);


/************************************************
 *       << Main function >>                    *
 ************************************************/
void main(void)
{
    /* Initialization */
    initialize();

    /* Main loop */
    while (1U) 
    {

    }

}

/************************************************
 *       << Initialization routine >>           *
 ************************************************/
void initialize(void)
{
    /* Enable global interrupts */
    sei();

    /* Set outputs and inputs */
    DDRC |= (1U << PORTC5);
}

/* Overflow interrupt service routine */
ISR(TIMER1_COMPA_vect) 
{
    PORTC ^= (1 << PORTC5);
}