/*
 * File:            i2c.c
 * Author:          Daniel Martinez
 *                  dagmtzs@gmail.com
 * Date:            Fri Nov 15 03:23:17 AM CST 2024
 * Target:          ATmega328P
 * Description:     TWI/I2C library
 */

#include "twi.h"

#ifndef F_TWI
#warning "The frequency for TWI/I2C interface (F_TWI) is not defined! Setting it to 100kHz"
#define F_TWI 100000UL
#elif F_TWI != 100000UL && F_TWI != 250000UL && F_TWI != 400000UL
#error "Invalid frequency for TWI/I2C interface (F_TWI)!"
#endif

#ifndef TWIPS
#warning "The value for TWI/I2C prescaler (TWIPS) is not defined! Setting it to 1"
#define TWIPS 1
#elif (TWIPS != 1) && (TWIPS != 4) && (TWIPS != 16) && (TWIPS != 64)
#error "Invalid prescaler (TWIPS) value for TWI/I2C!"
#endif

#define SET_TWBR ((F_CPU / F_TWI) - 16UL) / (TWIPS * 2U)

#if SET_TWBR < 0 || SET_TWBR > 255
#error "Invalid TWBR value! Please change TWIPS or F_TWI!"
#endif

uint8_t TW_ErrorCode;

/**
 * @brief   Set internal pull-up for TWI pins
 * @param[] none
 * @return  none
 */
void twi_set_internal_pullup(void)
{
    DDRC |= (1 << PIN_SDA) | (1 << PIN_SCL);
    PORTC |= (1 << PIN_SDA) | (1 << PIN_SCL);
}

/**
 * @brief   Initialize TWI interface
 * @param[] none
 * @return  none
 */
void twi_init(void)
{
    /* set clock */
    switch (TWIPS)
    {
    case 4:
        TWSR = 0x1;
        break;
    case 16:
        TWSR = 0x2;
        break;
    case 64:
        TWSR = 0x3;
        break;
    default:
        TWSR = 0x00;
        break;
    }
    TWBR = (uint8_t)SET_TWBR;
    
    /* enable */
    TWCR = (1 << TWEN);
}

/**
 * @brief   Start TWI transmisison
 * @param[] none
 * @return  none
 */
void twi_start()
{
    uint16_t timeout = F_CPU / F_TWI * 2.0;
    
    /* twi start */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while ((TWCR & (1 << TWINT)) == 0 && timeout != 0)
    {
        timeout--;
        if (timeout == 0)
        {
            TW_ErrorCode |= (1 << TW_START);
            return;
        }
    };
}

/**********************************************
 Public Function: twi_write_sla

 Purpose: Start TWI/I2C interface

 Input Parameter:
 - uint8_t twi_addr: Adress of reciever (use
    TW_SLA_W or TW_SLA_R to modify the address)

 Return Value: none
 **********************************************/
void twi_write_sla(uint8_t twi_addr)
{
    uint16_t timeout = F_CPU / F_TWI * 2.0;
    /* send adress */
    TWDR = twi_addr;
    TWCR = (1 << TWINT) | (1 << TWEN);
    timeout = F_CPU / F_TWI * 2.0;
    while ((TWCR & (1 << TWINT)) == 0 &&
           timeout != 0)
    {
        timeout--;
        if (timeout == 0)
        {
            TW_ErrorCode |= (1 << TW_ERR_SENDADRESS);
            return;
        }
    };
}

/**********************************************
 Public Function: twi_start_sla

 Purpose: Request TWI/I2C write to or read from
    the device with the provided address

 Input Parameter:
 - uint8_t twi_addr: Adress of reciever (use
    TW_SLA_W or TW_SLA_R to modify the address)

 Return Value: none
 **********************************************/
void twi_start_sla(uint8_t twi_addr)
{
    /* i2c start */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    uint16_t timeout = F_CPU / F_TWI * 2.0;
    while ((TWCR & (1 << TWINT)) == 0 && timeout != 0)
    {
        timeout--;
        if (timeout == 0)
        {
            TW_ErrorCode |= (1 << TW_START);
            return;
        }
    };
    /* send adress */
    TWDR = twi_addr;
    TWCR = (1 << TWINT) | (1 << TWEN);
    timeout = F_CPU / F_TWI * 2.0;
    while ((TWCR & (1 << TWINT)) == 0 &&
           timeout != 0)
    {
        timeout--;
        if (timeout == 0)
        {
            TW_ErrorCode |= (1 << TW_ERR_SENDADRESS);
            return;
        }
    };
}

/**********************************************
 Public Function: twi_stop

 Purpose: Signal stop TWI/I2C transmission

 Input Parameter: none

 Return Value: none
 **********************************************/
void twi_stop(void)
{
    /* i2c stop */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

/**********************************************
 Public Function: twi_write

 Purpose: Send byte at TWI/I2C interface

 Input Parameter:
 - uint8_t byte: Byte to send to reciever

 Return Value: none
 **********************************************/
void twi_write(uint8_t byte)
{
    TWDR = byte;
    TWCR = (1 << TWINT) | (1 << TWEN);
    uint16_t timeout = F_CPU / F_TWI * 2.0;
    while ((TWCR & (1 << TWINT)) == 0 &&
           timeout != 0)
    {
        timeout--;
        if (timeout == 0)
        {
            TW_ErrorCode |= (1 << TW_ERR_BYTE);
            return;
        }
    };
}

/**********************************************
 Public Function: twi_readAck

 Purpose: read acknowledge from TWI/I2C Interface

 Input Parameter: none

 Return Value: uint8_t
  - TWDR: recieved value at TWI/I2C-Interface, 0 at timeout
  - 0:    Error at read
 **********************************************/
uint8_t twi_readAck(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    uint16_t timeout = F_CPU / F_TWI * 2.0;
    while ((TWCR & (1 << TWINT)) == 0 &&
           timeout != 0)
    {
        timeout--;
        if (timeout == 0)
        {
            TW_ErrorCode |= (1 << TW_ERR_READACK);
            return 0;
        }
    };
    return TWDR;
}

/**********************************************
Public Function: twi_readNAck

Purpose: read non-acknowledge from TWI/I2C Interface

Input Parameter: none

Return Value: uint8_t
 - TWDR: recieved value at TWI/I2C-Interface
 - 0:    Error at read
**********************************************/
uint8_t twi_readNAck(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN);
    uint16_t timeout = F_CPU / F_TWI * 2.0;
    while ((TWCR & (1 << TWINT)) == 0 &&
           timeout != 0)
    {
        timeout--;
        if (timeout == 0)
        {
            TW_ErrorCode |= (1 << TW_ERR_READNACK);
            return 0;
        }
    };
    return TWDR;
}
