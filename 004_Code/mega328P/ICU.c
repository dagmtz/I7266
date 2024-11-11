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
#define F_CPU 16000000U

/************************************************
 *       << Area for includes >>                *
 ************************************************/
#include <avr/interrupt.h>

volatile uint16_t startTime = 0;
volatile uint16_t pulseWidth = 0;
volatile uint8_t pulseCaptured = 0;

void initialize(void);

/************************************************
 *       << Main function >>                    *
 ************************************************/
int main(void) {
   
    initialize();

    while (1) {
        if (pulseCaptured == 0 && pulseWidth > 0) {
            // Do something with pulseWidth
            pulseWidth = 0; // Reset pulse width after processing
        }
    }
}

/************************************************
 *       << Initialization routine >>           *
 ************************************************/
void initialize(){
    TCCR1B |= (1 << ICES1) | (1 << CS11); // Rising edge, prescaler 8
    TIMSK1 |= (1 << ICIE1); // Enable input capture interrupt

    DDRB &= ~(1 << DDB0); // Set PB0 (ICP1) as input

    sei(); // Enable global interrupts
}

ISR(TIMER1_CAPT_vect) {
    if (pulseCaptured == 0) {
        startTime = ICR1; // Capture the start time
        TCCR1B &= ~(1 << ICES1); // Switch to falling edge
        pulseCaptured = 1;
    } else {
        pulseWidth = ICR1 - startTime; // Calculate pulse width
        TCCR1B |= (1 << ICES1); // Switch back to rising edge
        pulseCaptured = 0;
    }
}
