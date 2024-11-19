/*
 * File:            main.c
 * Author:          Daniel Martinez
 *                  dagmtzs@gmail.com
 * Date:            Sun Nov 10 01:51:39 PM CST 2024
 * Target:          ATmega328P
 * Description:     This is a template for ATmega328P programs written in C
 */

#define F_CPU 16000000UL

#define DELAY_PER_DIGIT 1U
#define DELAY_TIME_MS 100U

#define USART_BUFFER_SIZE   255U
#ifndef BAUD_RATE
    #define BAUD_RATE           19200U
#endif

char USART_buffer[USART_BUFFER_SIZE];

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "usart.h"


typedef struct _tag_my_time_t
{
    uint8_t ss_u;
    uint8_t ss_d;
    uint8_t mm_u;
    uint8_t mm_d;
    uint8_t hh_u;
    uint8_t hh_d;
}my_time_t;

void tick(my_time_t *);
void turn_off_digits(void);
void turn_on_digit(uint8_t);
void show_digit(uint8_t);
void show_time(my_time_t *);

void main(void)
{	
    my_time_t time = {.ss_u = 0, .ss_d = 0, .mm_u = 0, .mm_d = 0, .hh_u = 0, .hh_d = 0};
    my_time_t *p_time = &time;
        
    DDRB |= (1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3) | (1 << PORTB4) | (1 << PORTB5);
    DDRC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3);

    USART_init(UBRR_CALC(BAUD_RATE));
    USART_puts( "\0[2J\0[H" );
    USART_puts( "\0[1;36m> USART Ready\r\n\n" );
    USART_puts( "\0[0;32mHello World! :)\r\n" );


    /* Set seconds through USART */
    USART_puts( "\0[0mWrite the seconds\r\n" );
    USART_getl(USART_buffer, USART_BUFFER_SIZE);
    _delay_ms(DELAY_TIME_MS); 
    if( atoi(USART_buffer) > 59 || atoi(USART_buffer) < 0)
    {
        USART_puts( "\nThe number received was:\0[0;m " );
        USART_puts( USART_buffer );
        USART_puts( "\n" );
        USART_puts( "\0[1;31mBut that number is not valid!\n\r" );
        USART_puts( "\0[0;mPlease reset and enter a valid number." );
        while(1);
    }
    USART_puts( "\nSetting the seconds to:\0[0;m " );
    USART_puts( USART_buffer );
    USART_puts( "\n" );    

    time.ss_u = ((uint8_t) atoi(USART_buffer)) % 10U;
    time.ss_d = ((uint8_t) atoi(USART_buffer) - time.ss_u) / 10U;

    /* Set minutes through USART */
    USART_puts( "\0[0mWrite the minutes\r\n" );
    USART_getl(USART_buffer, USART_BUFFER_SIZE);
    _delay_ms(DELAY_TIME_MS); 
    if( atoi(USART_buffer) > 59 || atoi(USART_buffer) < 0)
    {
        USART_puts( "\nThe number received was:\0[0;m " );
        USART_puts( USART_buffer );
        USART_puts( "\n" );
        USART_puts( "\0[1;31mBut that number is not valid!\n\r" );
        USART_puts( "\0[0;mPlease reset and enter a valid number." );
        while(1);
    }
    USART_puts( "\nSetting the minutes to:\0[0;m " );
    USART_puts( USART_buffer );
    USART_puts( "\n" );    

    time.mm_u = ((uint8_t) atoi(USART_buffer)) % 10U;
    time.mm_d = ((uint8_t) atoi(USART_buffer) - time.ss_u) / 10U;

    /* Set hours through USART */
    USART_puts( "\0[0mWrite the hours\r\n" );
    USART_getl(USART_buffer, USART_BUFFER_SIZE);
    _delay_ms(DELAY_TIME_MS); 
    if( atoi(USART_buffer) > 23 || atoi(USART_buffer) < 0)
    {
        USART_puts( "\nThe number received was:\0[0;m " );
        USART_puts( USART_buffer );
        USART_puts( "\n" );
        USART_puts( "\0[1;31mBut that number is not valid!\n\r" );
        USART_puts( "\0[0;mPlease reset and enter a valid number." );
        while(1);
    }
    USART_puts( "\nSetting the hours to:\0[0;m " );
    USART_puts( USART_buffer );
    USART_puts( "\n" );    

    time.hh_u = ((uint8_t) atoi(USART_buffer)) % 10U;
    time.hh_d = ((uint8_t) atoi(USART_buffer) - time.ss_u) / 10U;


    /* Este es el ciclo principal */
    while (1U)
    {

        for (uint8_t i = 0; i < 200; i++)
        {
            show_time(p_time);
        }
        tick(p_time);
        
    }
    
    return;

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