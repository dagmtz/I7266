#include <stdint.h>
#include "includes/ds3231.h"
#include "includes/i2c.h"

void setByte(uint8_t registerAddress, uint8_t value)
{
    I2C_start();
    I2C_write_sla(TW_SLA_W(DS3231_ADDRESS));
    I2C_write(registerAddress);
    I2C_write(value);
    I2C_stop();
}

void readByte(uint8_t registerAddress, uint8_t *p_value)
{
    I2C_start();
    I2C_write_sla(TW_SLA_W(DS3231_ADDRESS));
    I2C_write(registerAddress);
    I2C_start();
    I2C_write_sla(TW_SLA_R(DS3231_ADDRESS));
    *p_value = I2C_readNAck();
    I2C_stop();
}
    