/*
 * File:                    main.c
 * Author:                  Daniel Martinez
 *                          dagmtzs@gmail.com
 * Date:                    Thu Feb 15 10:10:08 PM CST 2024
 * Target:                  ATmega328P
 * Description:             This program is a "Hello World!" implementation for the 
 *                          ATmega328P. It turns an LED connected to PORTD7.
 */


/*
            0   1   2   3   4   5   6   7   8   9
--------------------------------------------------
a   PC5 |   1   0   1   1   0   1   1   1   1   1
b   PC4 |   1   1   1   1   1   0   0   1   1   1
c   PC3 |   1   1   0   1   1   1   1   1   1   1   
d   PC2 |   1   0   1   1   0   1   1   0   1   0
e   PC1 |   1   0   1   0   0   0   1   0   1   0
f   PC0 |   1   0   0   0   1   1   1   0   1   1
g   PD0 |   0   0   1   1   1   1   1   1   1   1

0 -> PORTC = 0b111111;          PORTD &= ~0b00000001;
1 -> PORTC = 0b011000;          PORTD &= ~0b00000001;
2 -> PORTC = 0b110110;          PORTD |= 0b00000001; 
3 -> PORTC = 0b111100;          PORTD |= 0b00000001;
4 -> PORTC = 0b011001;          PORTD |= 0b00000001;
5 -> PORTC = 0b101101;          PORTD |= 0b00000001;
6 -> PORTC = 0b101111;          PORTD |= 0b00000001;
7 -> PORTC = 0b111000;          PORTD |= 0b00000001;
8 -> PORTC = 0b111111;          PORTD |= 0b00000001;
9 -> PORTC = 0b111011;          PORTD |= 0b00000001;

*/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void main(void)
{

    DDRC = 0x3F;
    DDRD = 0x01;

    while (1)
    {
        // Contar de 0 a 9
        for (uint8_t i = 0; i < 10; i++)
        {
            // Mostrar en el display de 7 segmentos, el número "i"
            switch (i)
            {
            case 0:
                PORTC = 0b111111;          
                PORTD &= ~0b00000001;
                break;

            case 1:
                PORTC = 0b011000;          
                PORTD &= ~0b00000001;
                break;

            case 2:
                PORTC = 0b110110;          
                PORTD |= 0b00000001; 
                break;

            case 3:
                PORTC = 0b111100;          
                PORTD |= 0b00000001;
                break;

            case 4:
                PORTC = 0b011001;          
                PORTD |= 0b00000001;
                break;

            case 5:
                PORTC = 0b101101;          
                PORTD |= 0b00000001;
                break;

            case 6:
                PORTC = 0b101111;          
                PORTD |= 0b00000001;
                break;

            case 7:
                PORTC = 0b111000;          
                PORTD |= 0b00000001;
                break;
            
            case 8:
                PORTC = 0b111111;          
                PORTD |= 0b00000001;
                break;

            case 9:
                PORTC = 0b111001;          
                PORTD |= 0b00000001;
                break;

            default:
                break;
            }
            
            _delay_ms(200);
        }
        
    }
    

}