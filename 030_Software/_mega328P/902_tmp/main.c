/*
 * File:                    main.c
 * Author:                  Daniel Martinez
 *                          dagmtzs@gmail.com
 * Date:                    Thu Feb 15 10:10:08 PM CST 2024
 * Target:                  ATmega328P
 * Description:             This program is a "Hello World!" implementation for the 
 *                          ATmega328P. It turns an LED connected to PORTD7.
 */

#define F_CPU 16000000UL
#define DELAY 1000UL

#include <avr/io.h>
#include <util/delay.h>

void mostrarNumero(uint8_t numero);

int main(void)
{
    DDRC |= (1<<PORTC0) | (1<<PORTC1) | (1<<PORTC2) | (1<<PORTC3); 

    while (1)
    {
        // Contar de 0 a 9
        for (uint8_t i = 0; i < 10; i++)
        {
            // Mostrar en el display de 7 segmentos, el número "i"
            mostrarNumero(i);            
            _delay_ms(DELAY);
        }    
    }
}

void mostrarNumero(uint8_t numero)
{
    PORTC = ((PORTC & 0xF0) | (numero & 0x0F));
}