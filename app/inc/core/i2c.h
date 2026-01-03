#pragma once

#include <stdint.h>

void i2c1_setup(void);
void i2c_write(uint8_t addr, uint8_t reg, uint8_t data);
void i2c_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t len);