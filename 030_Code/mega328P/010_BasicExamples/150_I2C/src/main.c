/*
 * File:                    main.c
 * Author:                  Daniel Martinez
 *                          dagmtzs@gmail.com
 * Date:                    Fri Feb 16 01:12:47 AM CST 2024
 * Target:                  ATmega328P
 * Description:             This is a template for ATmega328P programs written in C
 */

#include <util/delay.h>
#include <avr/io.h>

#include "usart.h"
#include "i2c.h"

#define DELAY_TIME_MS       100U
#define USART_BUFFER_SIZE   255U

#ifndef BAUD_RATE
#   define BAUD_RATE           9600U
#endif

#define I2C_SCL             100000U
#define I2C_PRESCALER       4U

char USART_buffer[USART_BUFFER_SIZE];

int main( void )
{
    USART_init(UBRR_CALC(BAUD_RATE));
    USART_puts( "\e[2J\e[H" );
    USART_puts( "\e[1;36m> USART Ready\r\n" );
    USART_puts( "\e[0m\n" );

    _delay_ms(1000);

    DDRC = (1<<PORTC5) | (PORTC4);
    PORTC = (1<<PORTC5) | (PORTC4);
    
    I2C_init();
    USART_puts( "I2C initialized\r\n" );    

    uint8_t year = 0;

    I2C_start();
    I2C_write_sla(TW_SLA_W(DS3231_ADDRESS));
    I2C_write(0x06);
    I2C_write(0x24);
    I2C_stop();

    while(1U)
    {
        _delay_ms(1000);
        I2C_start();
        I2C_write_sla(TW_SLA_W(DS3231_ADDRESS));
        I2C_write(0x06);
        I2C_start();
        I2C_write_sla(TW_SLA_R(DS3231_ADDRESS));
        year = I2C_readNAck();
        I2C_stop();

        utoa(year, USART_buffer, 16);
        USART_puts(USART_buffer);
        USART_puts("\r\n");
    }
}



