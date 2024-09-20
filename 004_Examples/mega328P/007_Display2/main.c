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

#define DISPLAY_DDR         DDRD
#define DISPLAY_PORT        PORTD
#define TRANSISTOR_DDR      DDRD
#define TRANSISTOR_PORT     PORTD

#define DEFAULT_DELAY_MS    100

/*********************************************************************************************************************************
 *          << Area for includes >>
 ********************************************************************************************************************************/
#include <avr/io.h>
#include <util/delay.h>

#include <stdlib.h>

/*********************************************************************************************************************************
 *          << Area for function definitions >>
 ********************************************************************************************************************************/
// Este es el PROTOTIPO de una función

void showTime(int8_t minutes, int8_t seconds);
void showDigit(uint8_t digit);
void updateDigitValue(uint8_t);
void clearDigit();
void selectDigit(uint8_t);

/*********************************************************************************************************************************
 *          << Main function >>
 ********************************************************************************************************************************/
int main()
{	
    TRANSISTOR_DDR = 0x0F;
    DISPLAY_DDR = 0xF0;

    // Enter an infinite loop
    while (1)
    {        
        //showTime(12,45);
        updateDigitValue(5);
        selectDigit(1);
        _delay_us(DEFAULT_DELAY_MS);
        clearDigit();
        updateDigitValue(4);
        selectDigit(2);
        _delay_us(DEFAULT_DELAY_MS);
        clearDigit();
        updateDigitValue(2);
        selectDigit(3);
        _delay_us(DEFAULT_DELAY_MS);
        clearDigit();
        updateDigitValue(1);
        selectDigit(4);
        _delay_us(DEFAULT_DELAY_MS);
        clearDigit();
    }
}

void showTime(int8_t minutes, int8_t seconds)
{
    updateDigitValue(seconds%10);
    showDigit(1);
    updateDigitValue((uint8_t)(seconds/10));
    showDigit(2);
    updateDigitValue(minutes%10);
    showDigit(3);
    updateDigitValue((uint8_t)(minutes/10));
    showDigit(4);
}

void showDigit(uint8_t digit)
{
    clearDigit();
    selectDigit(digit);
    _delay_us(DEFAULT_DELAY_MS);
}

void updateDigitValue(uint8_t value)
{
    // Limpiar los últimos 4 bits del puerto
    DISPLAY_PORT &= 0b00001111;

    // Limitar el valor a 9 como máximo y evitar que se enciendan los bits 4 y mayores
    if (value <= 9)
    {
        DISPLAY_PORT |= (value << 4);
    }
    else
    {
        // Si el valor está fuera de rango, mostrar un caracter especial
        DISPLAY_PORT |= (10 << 4);
    }
    
}

void clearDigit()
{
    // Limpiar los primeros 4 bits del puerto C
    TRANSISTOR_PORT &= 0b11110000;
}

void selectDigit(uint8_t digit)
{   
    // Limitar el valor entre 1 a 4 y evitar que se enciendan los bits 4 y mayores
    if (digit > 0 && digit < 5)
    {
        TRANSISTOR_PORT |= (1 << (digit - 1));
    }
    else
    {
        // No hacer nada
    }
}