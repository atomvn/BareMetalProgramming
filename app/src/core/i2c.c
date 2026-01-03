#include <core/i2c.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>

void i2c1_setup(void) {
    // Enable clock
    rcc_periph_clock_enable(RCC_GPIOB);

    // Configure I2C pin PB6 = SCL, PB7 = SDA
    gpio_set_mode(GPIOB, 
                GPIO_MODE_OUTPUT_50_MHZ,
                GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN,
                GPIO6 | GPIO7);

    rcc_periph_clock_enable(RCC_I2C1);

    // Reset I2C
    rcc_periph_reset_pulse(RST_I2C1);

    //Set clock 
    // i2c_set_clock_frequency(I2C1, 36); //APB1 = 36MHZ
    // i2c_set_standard_mode(I2C1);
    // i2c_set_ccr(I2C1, 180);
    i2c_set_speed(I2C1, i2c_speed_sm_100k, rcc_apb1_frequency / 1e6); // 100kHz   // i2c_set_trise(I2C1, 17);
    i2c_enable_ack(I2C1);

    //Enable I2C
    i2c_peripheral_enable(I2C1);
}

void i2c_write(uint8_t addr, uint8_t reg, uint8_t data) {
    i2c_transfer7(I2C1, addr, &reg, 1, &data, 1);
}

void i2c_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t len) {
    i2c_transfer7(I2C1, addr, &reg, 1, buf, len);
}