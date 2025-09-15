/*
 * File:            i2c.h
 * Author:          Daniel Martinez
 *                  dagmtzs@gmail.com
 * Date:            Fri Nov 15 03:23:17 AM CST 2024
 * Target:          ATmega328P
 * Description:     TWI/I2C library
 */

#ifndef TWI_H_
#define TWI_H_

#include <stdio.h>
#include <avr/io.h>
#include <util/twi.h>

#define F_TWI 100000UL
#define TWIPS 1

#define TW_READ_NACK 0
#define TW_READ_ACK 1
#define PIN_SDA PORTC4
#define PIN_SCL PORTC5

#define TW_SLA_W(ADDR) ((ADDR << 1) | TW_WRITE)
#define TW_SLA_R(ADDR) ((ADDR << 1) | TW_READ)

extern uint8_t TWI_ErrorCode; /* variable for communication error at twi */
                              /* ckeck it in your code */
                              /* 0 means no error */
                              /* define bits in TWI-ErrorCode: */
#define TW_ERR_START 0      // bit 0: timeout start-condition
#define TW_ERR_SENDADRESS 1 // bit 0: timeout device-adress
#define TW_ERR_BYTE 2       // bit 0: timeout byte-transmission
#define TW_ERR_READACK 3    // bit 0: timeout read acknowledge
#define TW_ERR_READNACK 4   // bit 0: timeout read nacknowledge

void twi_set_internal_pullup(void);
void twi_init(void); 
void twi_start(void);
void twi_write_sla(uint8_t twi_addr);
void twi_start_sla(uint8_t twi_addr);
void twi_stop(void);          // send twi_stop_condition
void twi_write(uint8_t byte); // send data_byte

uint8_t twi_readAck(void);  // read byte with ACK
uint8_t twi_readNAck(void); // read byte with NACK

#endif /* TWI_H_ */
