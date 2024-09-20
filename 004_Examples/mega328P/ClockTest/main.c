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

struct tm time_struct;
//struct tm * p_time = &time_struct;

time_struct.tm_sec = 0;
time_struct.tm_min = 0;
time_struct.tm_hour = 0;

time_t timestamp = mktime(p_time);

/*********************************************************************************************************************************
 *          << Area for function declaration >>
 ********************************************************************************************************************************/
void updateValue(uint8_t value);
void selectDigit(uint8_t digit);

/*********************************************************************************************************************************
 *          << Main function >>
 ********************************************************************************************************************************/
int main()
{	
    set_system_time(timestamp);

    // Set Pin Change Interrupt Control to Enable PCIE1 
    // PCICR = (1 << PCIE1);
    // Set Pin Change Mask Register to enable PCINT13
    // PCMSK1 = (1 << PCINT13);
    
    // Set prescaler for Timer1 to 8
    // TCCR1B |= (1 << CS11);
    // Set prescaler for Timer1 to 64
    TCCR1B |= (1 << CS11) | (1 << CS10);
    // Enable Timer1 Overflow Interrupt via TIMSK1
    TIMSK1 |= (1 << TOIE1);


    // Set PORTB1 as output
	DDRD |= (1 << PORTD7);
    
    // Set PORTC5 as intput
	// DDRC |= (1 << PORTC5);
    // Enable pull-up
    // PORTC |= (1 << PORTC5);

    /* ---------- USART initialization ---------- */
	uart_init( BAUD_CALC( 115200 ) ); // 8n1 transmission is set as default
	
	stdout = &uart0_io; // attach uart stream to stdout & stdin
	stdin = &uart0_io; // uart0_in and uart0_out are only available if NO_USART_RX or NO_USART_TX is defined
	
	char usartBuffer[BUFF_SIZE];

    // SEt Interrupt flag in SREG
    sei();
    
    uart_puts_P( "\e[2J\e[H" );
	uart_puts_P( "\e[1;32m>USART Ready\r\n" );

    // Enter an infinite loop
	while (1)
	{        
        
        if (toggle == 1)
        {  
            //PORTD ^= (1 << PORTD7);
            
            printf("%02d:%02d:%02d\n", time_struct.tm_hour, time_struct.tm_min, time_struct.tm_sec);
            printf("%i\n", timestamp);
            updateDigitValue((uint8_t) time_struct.tm_sec);
            toggle = 0;
        }
    }
}

void updateValue(uint8_t value)
{
    if (value <= 9)
    {
        PORTC = value;
    }
    else
    {
        PORTC = 10;
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
        PORTB = 0;
    }
}

ISR(TIMER1_OVF_vect)
{ 
    toggle = 1;
    
    time_struct.tm_sec++;
    if(time_struct.tm_sec >= 60)
    {
        time_struct.tm_sec = 0;
        time_struct.tm_min++;
    }
    if(time_struct.tm_min >= 60)
    {
        time_struct.tm_min = 0;
        time_struct.tm_hour++;
    }    
    if(time_struct.tm_hour >= 24)
    {
        time_struct.tm_hour = 0;
    }
    system_tick();
    reti();
}
