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

/* Size for usartBuffer used in main() */
#define BUFF_SIZE   30
#define DEBOUNCE_DELAY 2U
#define STEP_DELAY 1000U

/*********************************************************************************************************************************
 *          << Area for includes >>
 ********************************************************************************************************************************/
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <util/delay.h>

#include "usart.h"

// Declare flag for interrupt
volatile bool toggle = 0;

volatile uint8_t counter = 0;

struct tm g_tm = {0, 22, 13, 31, 0, 2, 124, 91, 0};
struct tm *gp_tm = &g_tm;
time_t g_time = 0;
time_t *gp_time = &g_time;

/*********************************************************************************************************************************
 *          << Area for function declaration >>
 ********************************************************************************************************************************/
void refreshDisplays(int8_t minutes, int8_t seconds);
void updateValue(int8_t value);
void selectDigit(uint8_t digit);

/*********************************************************************************************************************************
 *          << Main function >>
 ********************************************************************************************************************************/
int main()
{	
    g_time = mktime(gp_tm);

    /* Set prescaler for Timer1 to 8
    TCCR1B |= (1 << CS11);
    Set prescaler for Timer1 to 64 */
    TCCR1B |= (1 << CS11) | (1 << CS10); 
    /* Enable Timer1 Overflow Interrupt via TIMSK1 */
    TIMSK1 |= (1 << TOIE1);

    // Set PORTB0 as output
    DDRB |= 0x0F;
    // Set PORTC0 to PORTC3 as output
	DDRC |= 0x0F;
    DDRD ^= (1 << 7);
    
    // Set PORTC5 as intput
	// DDRC |= (1 << PORTC5);
    // Enable pull-up
    // PORTC |= (1 << PORTC5);

    /* ---------- USART initialization ---------- */
	uart_init( BAUD_CALC( 115200 ) ); // 8n1 transmission is set as default
	
	stdout = &uart0_io; /* attach uart stream to stdout & stdin */
	stdin = &uart0_io; /* uart0_in and uart0_out are only available if NO_USART_RX or NO_USART_TX is defined */
	
	char usartBuffer[BUFF_SIZE];

    /* SEt Interrupt flag in SREG */
    sei();
    
    uart_puts_P( "\e[2J\e[H" );
	uart_puts_P( "\e[1;32m>USART Ready\r\n" );

    uart_puts_P( "\e[0m" );

    /* Enter an infinite loop */
	while (1)
	{        
        
        if (toggle)
        {  
            toggle = 0;

            g_tm = *gmtime(gp_time);	

            printf("%02d:%02d:%02d\n", g_tm.tm_hour, g_tm.tm_min, g_tm.tm_sec);
        }
        refreshDisplays(g_tm.tm_min, g_tm.tm_sec);
    }
}

void refreshDisplays(int8_t minutes, int8_t seconds)
{
    selectDigit(0);
    updateValue(seconds % 10);
    selectDigit(1);
    _delay_ms(1);

    selectDigit(0);
    updateValue(seconds / 10);
    selectDigit(2);
    _delay_ms(1);

    selectDigit(0);
    updateValue(minutes % 10);
    selectDigit(3);
    _delay_ms(1);
    
    selectDigit(0);
    updateValue((minutes / 10));
    selectDigit(4);
    _delay_ms(1);
}

void updateValue(int8_t value)
{
    if (value >= 0 && value <= 9U)
    {
        PORTC = value;
    }
    else
    {
        PORTC = 15U;
    }
}

void selectDigit(uint8_t digit)
{   
    // Limitar el valor entre 1 a 4 y evitar que se enciendan los bits 4 y mayores
    if (digit > 0 && digit < 5)
    {
        PORTB = ~(1 << (digit - 1));
    }
    else
    {
        PORTB &= 0xF0;
    }
}

ISR(TIMER1_OVF_vect)
{
    toggle = 1;
    g_time++;
}