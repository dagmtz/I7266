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

/************************************************
 *       << Area for includes >>                *
 ************************************************/
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

void setup_watchdog();
void reset_watchdog();

int main(void) {
    // Initialize the watchdog timer
    setup_watchdog();

    while (1) {
        // Your main code here

        // Reset the watchdog timer periodically
        reset_watchdog();
    }
}

void setup_watchdog() {
    // Disable interrupts
    cli();
    // Reset watchdog timer
    wdt_reset();
    // Set up the watchdog timer for a 2-second timeout
    WDTCSR = (1 << WDCE) | (1 << WDE);
    WDTCSR = (1 << WDE) | (1 << WDP2) | (1 << WDP1);
    // Enable global interrupts
    sei();
}

void reset_watchdog() {
    // Reset the watchdog timer
    wdt_reset();
}
