#pragma once
#include <core/rcc.h>

//I2C base memory
#define I2C1				I2C1_BASE

/* Control register 1 (I2Cx_CR1) */
#define I2C_CR1(i2c_base)		MMIO32((i2c_base) + 0x00)
#define I2C1_CR1			I2C_CR1(I2C1)

/* Control register 2 (I2Cx_CR2) */
#define I2C_CR2(i2c_base)		MMIO32((i2c_base) + 0x04)
#define I2C1_CR2			I2C_CR2(I2C1)

/* Data register (I2Cx_DR) */
#define I2C_DR(i2c_base)		MMIO32((i2c_base) + 0x10)
#define I2C1_DR				I2C_DR(I2C1)

/* Status register 1 (I2Cx_SR1) */
#define I2C_SR1(i2c_base)		MMIO32((i2c_base) + 0x14)
#define I2C1_SR1			I2C_SR1(I2C1)

/* Status register 2 (I2Cx_SR2) */
#define I2C_SR2(i2c_base)		MMIO32((i2c_base) + 0x18)
#define I2C1_SR2			I2C_SR2(I2C1)

/* Clock control register (I2Cx_CCR) */
#define I2C_CCR(i2c_base)		MMIO32((i2c_base) + 0x1c)
#define I2C1_CCR			I2C_CCR(I2C1)

/* TRISE register (I2Cx_CCR) */
#define I2C_TRISE(i2c_base)		MMIO32((i2c_base) + 0x20)
#define I2C1_TRISE			I2C_TRISE(I2C1)

void i2c1_init(void);
void i2c_start(void);
void i2c_send_address(uint8_t addr, uint8_t rw);
uint8_t i2c_read_byte(void);
void i2c_write_byte(uint8_t data);
void i2c_stop(void);
void i2c_write_reg(uint8_t addr, uint8_t reg, uint8_t data);
uint8_t i2c_read_reg(uint8_t addr, uint8_t reg);