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
#define F_CPU 16000000UL

/************************************************
 *       << Area for includes >>                *
 ************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t a;

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
    /* Set External Interrupt Control Register A to trigger an interrupt request with a falling edge of INT0*/
    EICRA &= ~(1 << ISC00);
    EICRA |= (1 << ISC01);

    /* Enable External Interrupt Request 0 */
    EIMSK |= (1 << INT0);

    /* Set PORTD2 as input and enable internal pull-up resistor */
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);

    /* Set PORTD4 as output */
    DDRD |= (1 << PD4);

    /* Enable global interrupts */
    sei();
}

ISR(INT0_vect)
{
    PORTD ^= (1 << PD4);
}