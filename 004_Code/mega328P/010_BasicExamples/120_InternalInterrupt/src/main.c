/*
 * File:                    main.c
 * Author:                  Daniel Martinez
 *                          dagmtzs@gmail.com
 * Date:                    Sun Jan 01 00:00:00 AM CST 2024
 * Target:                  ATmega328P
 * Description:             This is a template for ATmega328P programs written in C
 */

/************************************************
 *       << Area for macro definitions >>       *
 ************************************************/
#define F_CPU 16000000U

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
    /* Set Timer1 to CTC mode */
    TCCR1B |= (1U << WGM12);

    // Set the prescaler to 64
    TCCR1B |= (1U << CS12) | (1U << CS10);

    /* Compare match value for 1-second delay */
    OCR1A = 15624U;

    /* Enable Timer1 compare match interrupt */
    TIMSK1 |= (1U << OCIE1A);

    /* Set outputs and inputs */
    DDRC |= (1U << PORTC5);

    /* Enable global interrupts */
    sei();
}

/* TIMER1 Compare A interrupt service routine */
ISR(TIMER1_COMPA_vect) 
{
    PORTC ^= (1U << PORTC5);
}
