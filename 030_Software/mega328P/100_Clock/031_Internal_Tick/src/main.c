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
#define MYUBRR 103
#define DELAY_PER_DIGIT 1U

/************************************************
 *       << Area for includes >>                *
 ************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct _tag_my_time_t
{
    uint8_t ss_u;
    uint8_t ss_d;
    uint8_t mm_u;
    uint8_t mm_d;
    uint8_t hh_u;
    uint8_t hh_d;
}my_time_t;

volatile bool heartbeat = false;

void tick(my_time_t *);
void turn_off_digits(void);
void turn_on_digit(uint8_t);
void show_digit(uint8_t);
void show_time(my_time_t *);
void initialize(void);


/************************************************
 *       << Main function >>                    *
 ************************************************/

void main(void)
{	
    my_time_t time = {.ss_u = 0, .ss_d = 0, .mm_u = 0, .mm_d = 0, .hh_u = 0, .hh_d = 0};
    my_time_t *p_time = &time;

    /* Initialization */
    initialize();

    /* Main loop */
    while (1U) 
    {
        show_time(p_time);
        if(heartbeat == true)
        {
            heartbeat = false;
            tick(p_time);
        }
    }
    
    return;
}

void initialize()
{
    DDRB |= (1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3) | (1 << PORTB4) | (1 << PORTB5);
    DDRC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3);

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

void tick(my_time_t *time)
{
    time->ss_u++;
    if (time->ss_u > 9)
    {
        time->ss_u = 0;
        time->ss_d++;
    }
    if (time->ss_d > 5)
    {
        time->ss_d = 0;
        time->mm_u++;
    }
    if (time->mm_u > 9)
    {
        time->mm_u = 0;
        time->mm_d++;
    }
    if (time->mm_d > 5)
    {
        time->mm_d = 0;
        time->hh_u++;
    }
    if (time->hh_u > 9)
    {
        time->hh_u = 0;
        time->hh_d++;
    }
    if (time->hh_d == 2 && time->hh_u == 4)
    {
        time->hh_u = 0;
        time->hh_d = 0;
    }
}

void turn_off_digits()
{
    PORTB = 0U;
}

void turn_on_digit(uint8_t digit)
{
    PORTB = (1U << (5U - digit));
    _delay_ms(DELAY_PER_DIGIT);
    turn_off_digits();
}

void show_digit(uint8_t number)
{
    PORTC = ((PORTC & 0xF0) | (number & 0x0F));
}

void show_time(my_time_t *time)
{
    show_digit(time->ss_u);
    turn_on_digit(0);
    show_digit(time->ss_d);
    turn_on_digit(1);
    show_digit(time->mm_u);
    turn_on_digit(2);
    show_digit(time->mm_d);
    turn_on_digit(3);
    show_digit(time->hh_u);
    turn_on_digit(4);
    show_digit(time->hh_d);
    turn_on_digit(5);
}

/* TIMER1 Compare A interrupt service routine */
ISR(TIMER1_COMPA_vect) 
{
    heartbeat = true;
}