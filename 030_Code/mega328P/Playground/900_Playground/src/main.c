/*
 * File:                    main.c
 * Author:                  Daniel Martinez
 *                          dagmtzs@gmail.com
 * Date:                    Fri Feb 16 01:12:47 AM CST 2024
 * Target:                  ATmega328P
 * Description:             This is a template for ATmega328P programs written in C
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usart.h"
#include "i2c.h"
#include "ds3231.h"

#define DELAY_TIME_MS 100U

#ifdef BAUD
#define BAUD_RATE BAUD
#else
#define BAUD_RATE 9600UL
#endif

#define I2C_SCL 100000UL
#define I2C_PRESCALER 4U

#define DS3231_ADDRESS 0x68

#define _INIT_TIME

#ifdef _INIT_TIME
#define _INIT_SECONDS	0x00
#define _INIT_MINUTES	0x45
#define _INIT_HOURS		0x15
#define _INIT_DATE		0x13
#define _INIT_MONTH		0x11
#define _INIT_YEAR		0x24
#endif // _INIT_TIME

/* Size for usartBuffer used in main() */
#define USART_BUFFER_SIZE   30

/* 1Hz heartbeat coming from RTC */
volatile bool g_heartbeat_1s = false;

time_t g_time;
time_t *gp_time = &g_time;
struct tm rtc_time;
struct tm  *gp_rtcTime = &rtc_time;

char USART_buffer[USART_BUFFER_SIZE];
DS3231_buffer_t rtcBuffer;

void initialize(void);

void main(void)
{
    initialize();

    while (1U)
    {
        if ( g_heartbeat_1s )
		{
			g_heartbeat_1s = false;
			
			uart_puts_P( "\r\0[2K" );
			printf("%s\t%.2fC", ctime(gp_time) , rtc_getTemp());
		}
    }
}

void initialize(void)
{
    
    DDRC = (1 << PORTC5) | (PORTC4);
    PORTC = (1 << PORTC5) | (PORTC4);

    /* Set up external interrupt ( 1Hz from RTC ) */
	EICRA = ( _BV( ISC01 ) | _BV( ISC00 ) );
	
	/* Enable INT0 external interrupt */
	EIMSK = _BV( INT0 );

    uart_init(BAUD_CALC(BAUD_RATE));

    _delay_ms(200U);
    
    uart_puts("\0[2J\0[H");
    uart_puts("\0[1;36m> USART Ready\r\n");
    uart_puts("\0[0m\n");
    
    I2C_init();

    uart_puts("I2C initialized\r\n");

    sei();

    rtc_setByte( DS3231_CONTROL, 0x00 );
    rtcBuffer.control = rtc_getByte( DS3231_CONTROL );
	rtcBuffer.status = rtc_getByte( DS3231_STATUS );

    uart_puts_P( "\0[0;m>Control register value: 0x" );
	utoa( rtcBuffer.control, USART_buffer, 16);
	uart_puts( USART_buffer );
	uart_puts_P( "\r\n" );
	
	uart_puts_P( "\0[0;m>Status register value: 0x" );
	utoa( rtcBuffer.status, USART_buffer, 16);
	uart_puts( USART_buffer );
	uart_puts_P( "\r\n" );

#ifdef _INIT_TIME
	/*	In case this is defined, set initial values to RTC */
	rtc_setByte( DS3231_SECOND, _INIT_SECONDS );
	rtc_setByte( DS3231_MINUTE, _INIT_MINUTES );
	rtc_setByte( DS3231_HOUR, _INIT_HOURS );
	rtc_setByte( DS3231_DATE, _INIT_DATE );
	rtc_setByte( DS3231_MONTH, _INIT_MONTH );
	rtc_setByte( DS3231_YEAR, _INIT_YEAR );
#endif /* _INIT_TIME */

    /* ---------- Core time initialization ---------- */
	rtc_getTime( gp_rtcTime );
	rtc_time.tm_isdst = 0;
	
	g_time = mktime( gp_rtcTime );
	set_system_time( g_time );

	/*	Wait for a heartbeat from RTC to initialize values	*/
	g_heartbeat_1s = false;
	// while ( g_heartbeat_1s == false);

    uart_puts_P( "\0[0m" );
}

ISR( INT0_vect )
{
	g_heartbeat_1s = true;
	g_time++;
}