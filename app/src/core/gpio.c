#include <core/rcc.h>
#include <core/gpio.h>

static volatile uint32_t *gpio_cr_reg(uint32_t port, uint8_t pin) {
    return (pin < 8) ? &GPIO_CRL(port) : &GPIO_CRH(port);
}

void gpio_enable_clock(uint32_t port) {
    if (port == GPIOA) RCC_APB2ENR |= (1<<2);
    if (port == GPIOB) RCC_APB2ENR |= (1<<3);
    if (port == GPIOC) RCC_APB2ENR |= (1<<4);
}

void gpio_mode_setup(uint32_t port, uint8_t pin, uint8_t mode, uint8_t cnf) {
    volatile uint32_t *cr = gpio_cr_reg(port, pin);
    uint8_t shift = (pin % 8) * 4;

    /* Clear 4 bits */
    *cr &= ~(0xF << shift);

    /* Set MODE + CNF */
    *cr |= ((mode & 0x3) | ((cnf & 0x3) << 2)) << shift;

    /* Pull-up needs ODR = 1 */
    if (mode == GPIO_MODE_INPUT && cnf == GPIO_CNF_INPUT_PULL_UPDOWN) {
        GPIO_ODR(port) |= (1 << pin);
    }
}

void gpio_set(uint32_t port, uint8_t pin) {
    GPIO_BSRR(port) = (1 << pin);
}

void gpio_clear(uint32_t port, uint8_t pin) {
    GPIO_BSRR(port) = (1 << (pin + 16));
}

void gpio_toggle(uint32_t port, uint8_t pin) {
    uint8_t status = gpio_read(port, pin);
    if (status) {
        gpio_clear(port, pin);
    }
    else {
        gpio_set(port, pin);
    }
}

uint8_t gpio_read(uint32_t port, uint8_t pin) {
    return (GPIO_IDR(port) & (1 << pin)) ? 1 : 0;
}