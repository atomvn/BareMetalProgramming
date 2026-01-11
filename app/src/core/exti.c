#include <core/exti.h>
#include <core/rcc.h>
#include <core/gpio.h>

// Configure PA0 as input floating 
void gpio_exti_pa0_init(void) {
    gpio_enable_clock(GPIOA);
    RCC_APB2ENR |= RCC_AFIO_EN;
    gpio_mode_setup(GPIOA, 0, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT);
    // GPIOA_ODR &= (0 << 0);
}

// Map PA0 -> EXTI0
void afio_exti0_map_pa0(void) {
    AFIO_EXTICR1 &= ~(0xF << 0); // 0000 = select PA0 for source input for EXTI0
}

// Setup EXTI0, unmask interrupt, rising edge, clear pending bit
void exti0_init(void) {
    // Enable interrupt on EXTI0
    EXTI_IMR |= (1 << 0);

    // Rising edge trigger
    EXTI_RTSR |= (1 << 0);
    EXTI_FTSR &= ~(1 << 0);

    // Clear pending
    EXTI_PR |= (1 << 0);
}

// Enable NVIC for EXTI0, EXTI0 IRQ = bit 6
void nvic_exti0_enable(void) {
    NVIC_ISER0 |= (1 << 6);
}

volatile uint8_t mpu_int_flag = 0;
// Interrupt handler for EXTI0
void exti0_isr(void) {
    if (EXTI_PR & (1 << 0)) {
        EXTI_PR |= (1 << 0); // clear PR pending
        mpu_int_flag = 1;
    }
}

