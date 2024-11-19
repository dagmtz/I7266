#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>

/* #define F_CPU 16000000UL */
#define DS3231_ADDRESS 0x68  // I2C address of DS3231
#define BAUD 9600
#define MYUBRR 103

// Initialize I2C (TWI) interface
void i2c_init() {
    // Set I2C clock rate (TWBR = 12 for 400kHz with F_CPU=16MHz)
    TWSR = 0x00;             // Set prescaler bits to zero
    TWBR = 12;
    TWCR = (1 << TWEN);      // Enable TWI (I2C)
}

// Start I2C transmission
void i2c_start() {
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);  // Send START condition
    while (!(TWCR & (1 << TWINT)));                    // Wait for TWINT Flag set
}

// Send I2C stop condition
void i2c_stop() {
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);  // Transmit STOP condition
    while (TWCR & (1 << TWSTO));                       // Wait for STOP to finish
}

// Write a byte to the I2C bus
void i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWEN) | (1 << TWINT);                 // Start transmission
    while (!(TWCR & (1 << TWINT)));                    // Wait for TWINT Flag set
}

// Read a byte from the I2C bus with ACK or NACK
uint8_t i2c_read(uint8_t ack) {
    TWCR = (1 << TWEN) | (1 << TWINT) | (ack ? (1 << TWEA) : 0);
    while (!(TWCR & (1 << TWINT)));                    // Wait for TWINT Flag set
    return TWDR;
}

// Convert BCD to decimal
uint8_t bcd_to_decimal(uint8_t bcd) {
    return ((bcd / 16 * 10) + (bcd % 16));
}

// Read time from DS3231
void ds3231_get_time(uint8_t* hours, uint8_t* minutes, uint8_t* seconds) {
    i2c_start();
    i2c_write((DS3231_ADDRESS << 1) | 0);  // DS3231 address + write bit
    i2c_write(0x00);                       // Set DS3231 register pointer to 0x00 (Seconds register)
    
    i2c_start();
    i2c_write((DS3231_ADDRESS << 1) | 1);  // DS3231 address + read bit
    *seconds = bcd_to_decimal(i2c_read(1)); // Read seconds
    *minutes = bcd_to_decimal(i2c_read(1)); // Read minutes
    *hours = bcd_to_decimal(i2c_read(0));   // Read hours
    i2c_stop();
}

void USART_Init( unsigned int ubrr)
{
    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);

    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) )
        ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

int main(void) {
    uint8_t hours, minutes, seconds;
    char buffer = 0;

    i2c_init();  // Initialize I2C
    USART_Init(MYUBRR);

    while (1) {
        ds3231_get_time(&hours, &minutes, &seconds);
        itoa(seconds, &buffer, 10);
        USART_Transmit(buffer);
        USART_Transmit('\n');
        USART_Transmit('\r');

        // Here you would display the time (hours, minutes, seconds)
        // For example: Toggle an LED every second, or send the time to serial
        _delay_ms(1000U);
    }
}
