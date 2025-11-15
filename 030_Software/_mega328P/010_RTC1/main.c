#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include <util/delay.h>
#include <avr/io.h>

#include "includes/usart.h"
#include "includes/i2c.h"
#include "includes/ds3231.h"

#define DELAY_TIME_MS       100U
#define USART_BUFFER_SIZE   255U

#ifndef BAUD_RATE
#   define BAUD_RATE           9600U
#endif

#define I2C_SCL             100000U
#define I2C_PRESCALER       4U

#define DS3231_ADDRESS		0x68

typedef struct 
{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint8_t year;
}timeStruct_t;


char USART_buffer[USART_BUFFER_SIZE];

int main( void )
{
    USART_init(UBRR_CALC(BAUD_RATE));
    USART_puts( "\e[2J\e[H" );
    USART_puts( "\e[1;36m> USART Ready\r\n" );
    USART_puts( "\e[0m\n" );

    timeStruct_t time = {0,0,0x09,0x25,0x04,0x24};

    _delay_ms(1000);

    DDRC = (1<<PORTC5) | (PORTC4);
    PORTC = (1<<PORTC5) | (PORTC4);
    
    I2C_init();
    USART_puts( "I2C initialized\r\n" );    

    USART_puts("Hora: ");
    utoa(time.hours, USART_buffer, 16);
    USART_puts(USART_buffer);
    USART_puts(":");
    utoa(time.minutes, USART_buffer, 16);
    USART_puts(USART_buffer);
    USART_puts(":");
    utoa(time.seconds, USART_buffer, 16);
    USART_puts(USART_buffer);

    /* Enviar segundos */
    setByte(0x00, time.seconds);
    setByte(0x01, time.minutes);
    setByte(0x02, time.hours);
    setByte(0x04, time.day);
    setByte(0x05, time.month);
    setByte(0x06, time.year);

    while(1U)
    {
        _delay_ms(1000);
        
        readByte(0x04, &time.day);
        readByte(0x05, &time.month);
        readByte(0x06, &time.year);
        readByte(0x02, &time.hours);
        readByte(0x01, &time.minutes);
        readByte(0x00, &time.seconds);

        utoa(time.day, USART_buffer, 16);
        USART_puts(USART_buffer);
        USART_puts("/");
        utoa(time.month, USART_buffer, 16);
        USART_puts(USART_buffer);
        USART_puts("/");
        utoa(time.year, USART_buffer, 16);
        USART_puts(USART_buffer);
        USART_puts("\t");
        utoa(time.hours, USART_buffer, 16);
        USART_puts(USART_buffer);
        USART_puts(":");
        utoa(time.minutes, USART_buffer, 16);
        USART_puts(USART_buffer);
        USART_puts(":");
        utoa(time.seconds, USART_buffer, 16);
        USART_puts(USART_buffer);

        USART_puts("\r\n");
    }
}



