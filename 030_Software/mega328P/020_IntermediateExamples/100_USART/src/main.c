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
/* #define F_CPU 16000000UL */

/* Size for usartBuffer used in main() */
#define BUFF_SIZE   32U

/************************************************
 *       << Area for includes >>                *
 ************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "usart.h"

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
        printf("Hello World! :)\n");
        _delay_ms(1000U);
    }
}

/************************************************
 *       << Initialization routine >>           *
 ************************************************/
void initialize(void)
{

	/* ---------- USART initialization ---------- */
	uart_init( BAUD_CALC( BAUD ) ); /* 8n1 transmission is set as default */
	
	stdout = &uart0_io; /* attach uart stream to stdout & stdin */
	stdin = &uart0_io; /* uart0_in and uart0_out are only available if NO_USART_RX or NO_USART_TX is defined */

	sei();
	
	uart_puts_P( "\e[2J\e[H" );
	uart_puts_P( "\e[1;32m>USART Ready\r\n" );
    uart_puts_P( "\e[0m" );

}