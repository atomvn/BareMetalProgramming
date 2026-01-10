#include <core/i2c.h>
#include <core/gpio.h>

// Init I2C
void i2c1_init(void) {
    // Enable clock for I2C1, GPIOB and AFIO
    RCC_APB1ENR |= RCC_I2C1_EN;
    RCC_APB2ENR |= RCC_GPIOB_EN;
    RCC_APB2ENR |= RCC_AFIO_EN;

    // Configure PB6, PB7 OUTPUT mode
    gpio_mode_setup(GPIOB, 6, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN);
    gpio_mode_setup(GPIOB, 7, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN);

    // Configuring I2C1 with APB1 = 36MHz and I2C = 100 kHz
    // Reset I2C
    I2C1_CR1 |= (1 << 15);   // SWRST = 1
    I2C1_CR1 &= ~(1 << 15);  // SWRST = 0

    // CR2: APB1 clock (MHz)
    I2C1_CR2 = 36;

    // Standard mode 100kHz
    // CCR = APB1 / (2 * I2C_speed)
    // = 36MHz / (2 * 100k) = 180
    I2C1_CCR = 180;

    // TRISE = APB1(MHz) + 1
    I2C1_TRISE = 37;

    // Enable I2C
    I2C1_CR1 |= (1 << 0);  // PE = 1
}

// Start I2C
void i2c_start(void)
{
    I2C1_CR1 |= (1 << 8);          // START = 1
    while (!(I2C1_SR1 & (1 << 0))); // SB bit
}

// Send address to slave
void i2c_send_address(uint8_t addr, uint8_t rw)
{
    I2C1_DR = (addr << 1) | rw;

    while (!(I2C1_SR1 & (1 << 1))); // ADDR bit

    (void)I2C1_SR2; // Clear ADDR by reading SR2
}

// Write a byte to DR register
void i2c_write_byte(uint8_t data)
{
    while (!(I2C1_SR1 & (1 << 7))); // TXE
    I2C1_DR = data;
    while (!(I2C1_SR1 & (1 << 2))); // BTF
}

// Read a byte from DR register
uint8_t i2c_read_byte(void)
{
    while (!(I2C1_SR1 & (1 << 6))); // RXNE
    return I2C1_DR;
}

// Stop I2C
void i2c_stop(void)
{
    I2C1_CR1 |= (1 << 9);  // STOP
}

// Write data to reg 
void i2c_write_reg(uint8_t addr, uint8_t reg, uint8_t data)
{
    i2c_start();
    i2c_send_address(addr, 0); // write
    i2c_write_byte(reg);
    i2c_write_byte(data);
    i2c_stop();
}

// Read data from reg
uint8_t i2c_read_reg(uint8_t addr, uint8_t reg)
{
    uint8_t data;

    i2c_start();
    i2c_send_address(addr, 0);   // write
    i2c_write_byte(reg);

    i2c_start();
    i2c_send_address(addr, 1);   // read

    I2C1_CR1 &= ~(1 << 10);  // ACK = 0

    data = i2c_read_byte();

    i2c_stop();

    I2C1_CR1 |= (1 << 10);   // ACK = 1

    return data;
}
