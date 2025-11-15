#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL  // Define CPU frequency (16 MHz)

volatile uint8_t overflow_count = 0;

int main() 
{
    // Configure Timer0 in Normal Mode with prescaler 1024
    TCCR0B |= (1 << CS02) | (1 << CS00); // Set prescaler to 1024
    TIMSK0 |= (1 << TOIE0);              // Enable overflow interrupt

    // Enable global interrupts
    sei();

    DDRD |= (1 << PORTD7);

    // Main loop
    while (1) 
    {

    }

}

// Overflow interrupt service routine
ISR(TIMER0_OVF_vect) 
{
    // Increment overflow count
    //overflow_count++;
    PORTD ^= (1 << PORTD7);
}