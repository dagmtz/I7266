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
#define F_CPU 16000000UL
#define ADC_POT_CHANNEL 5
#define LED_PIN PD6

/************************************************
 *       << Area for includes >>                *
 ************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void initialize(void);
uint16_t adc_read(uint8_t channel);

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
        /* Read analog value from potentiometer on ADC channel 0 */
        uint16_t pot_value = adc_read(ADC_POT_CHANNEL);

        /* Map the 10-bit ADC value (0-1023) to an 8-bit value (0-255) for PWM duty cycle */
        uint8_t pwm_value = pot_value / 4;

        /* Set the PWM duty cycle */
        OCR0A = pwm_value;
    }
}

/************************************************
 *       << Initialization routine >>           *
 ************************************************/
void initialize(void)
{
    /* Set the reference voltage to AVcc */
    ADMUX |= (1 << REFS0);

    /* Set the ADC prescaler to 128 for accurate ADC resuts (16 MHz / 128 = 125 KHz) */
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    /* Enable the ADC */
    ADCSRA |= (1 << ADEN);


    /* Clear OC0B on Compare Match */
    TCCR0A |= (1 << COM0A1);

    /* Set Timer0 to Fast PWM mode */
    TCCR0A |= (1 << WGM01) | (1 << WGM00);

    /* Set the prescaler off */
    TCCR0B |= (1 << CS00);


    /* Set PD6 (OC0A) as output for PWM */
    DDRD |= (1 << LED_PIN);

    /* Enable global interrupts */
    /* sei(); */
}

uint16_t adc_read(uint8_t channel) {
    /* Select the ADC channel (0 to 7) */
    ADMUX &= 0xF0;
    ADMUX |= channel;

    /* Start the conversion */
    ADCSRA |= (1 << ADSC);

    /* Wait for the conversion to complete */
    while (ADCSRA & (1 << ADSC));

    /* Return the ADC result */
    return ADC;
}
