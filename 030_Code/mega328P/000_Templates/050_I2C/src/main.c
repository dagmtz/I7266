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
#define F_CPU 16000000UL

/*********************************************************************************************************************************
 *          << Area for includes >>
 ********************************************************************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>

void main(void)
{
    /* Configure Timer0 in Normal Mode with prescaler 1024 */
    TCCR0B |= (1U << CS02) | (1U << CS00); /* Set prescaler to 1024 */
    TIMSK0 |= (1U << TOIE0);              /* Enable overflow interrupt */

    /* Set Timer1 to CTC mode */
    TCCR1B |= (1U << WGM12);

    // Set the prescaler to 64
    TCCR1B |= (1U << CS12) | (1U << CS10);

    /* Compare match value for 1-second delay */
    OCR1A = 15624U;

    /* Enable Timer1 compare match interrupt */
    TIMSK1 |= (1U << OCIE1A);

    /* Enable global interrupts */
    sei();

    /* Set outputs and inputs */
    DDRC |= (1U << PORTC4) | (1U << PORTC5);

    /* Main loop */
    while (1U) 
    {

    }

}

/* TIMER0 Overflow interrupt service routine */
ISR(TIMER0_OVF_vect) 
{
    PORTC ^= (1U << PORTC5);
}

/* TIMER1 Compare A interrupt service routine */
ISR(TIMER1_COMPA_vect) 
{
    PORTC ^= (1U << PORTC4);
}
