#ifndef DS3231_H_
#define DS3231_H_

#define DS3231_ADDRESS		0x68

void setByte(uint8_t registerAddress, uint8_t value);
void readByte(uint8_t registerAddress, uint8_t *p_value);

#endif /* DS3231_H_ */