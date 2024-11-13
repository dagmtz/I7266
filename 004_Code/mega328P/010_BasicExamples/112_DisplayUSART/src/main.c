/*
 * File:                    main.c
 * Author:                  Daniel Martinez
 *                          dagmtzs@gmail.com
 * Date:                    Thu, Nov  7, 2024  5:45:48 PM
 * Target:                  ATmega328P
 * Description:             ...
 */

#define F_CPU 16000000U
#define FOSC F_CPU // Clock Speed
#define BAUD 9600
#define MYUBRR 103

#define DELAY_PER_DIGIT 1U

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

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
void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );

void main(void)
{	
    my_time_t time = {.ss_u = 0, .ss_d = 0, .mm_u = 4, .mm_d = 3, .hh_u = 5, .hh_d = 1};
    my_time_t *p_time = &time;

    char buffer = 0;

    USART_Init(MYUBRR);
        
    DDRB |= (1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3) | (1 << PORTB4) | (1 << PORTB5);
    DDRC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3);

    /* Este es el ciclo principal */
    while (1U)
    {
        for (uint8_t i = 0; i < 200; i++)
        {
            show_time(p_time);
        }
        /* itoa(time.hh_d, &buffer, 10);
        USART_Transmit(buffer);
        itoa(time.hh_u, &buffer, 10);
        USART_Transmit(buffer);
        USART_Transmit(':');
        itoa(time.mm_d, &buffer, 10);
        USART_Transmit(buffer);
        itoa(time.mm_u, &buffer, 10);
        USART_Transmit(buffer);
        USART_Transmit(':');
        itoa(time.ss_d, &buffer, 10);
        USART_Transmit(buffer);
        itoa(time.ss_u, &buffer, 10);
        USART_Transmit(buffer);
        USART_Transmit('\n');
        USART_Transmit('\r'); */
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

void USART_Init( unsigned int ubrr)
{
    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);

    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) )
        ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}