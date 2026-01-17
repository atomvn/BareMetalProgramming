#include <core/timer.h>
#include <core/rcc.h>
#include <core/gpio.h>
#include <core/systick.h>

void timer2_ch1_pwm_setup(void) {
    // Enable clock for timer 2 and GPIOA
    RCC_APB1ENR |= (1 << 0);
    gpio_enable_clock(GPIOA);
    // Configure GPIOA mode
    gpio_mode_setup(GPIOA, 0, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL);

    // Timer 2 configure with perscaler = 72 => tick = 1us (Timerclock = 1MHz)
    TIM2_PSC = 72 -1;
    // Setup auto reload value, T = 20000 tick = 20ms
    TIM2_ARR = 19999;

    // Configure PWM mode 1 on channel 1
    TIM2_CCMR1 &= ~(0xFF << 0); // Clear CCMR1 bit 0-7 (Channel 1)
    TIM2_CCMR1 |= (0x6 << 4); // OCM1 = 110 = PWM mode 1
    TIM2_CCMR1 |= (1 << 3);  // OC1PE = 1 (preload enable)

    // Polarity configure and enable channel
    TIM2_CCER &= ~(1 << 1); // CC1P = 0, active high
    TIM2_CCER |= (1 << 0); // CC1E = 1, enable output

    // Turn on preload for ARR (to avoid glitch)
    TIM2_CR1 |= (1 << 7); //ARPE = 1
    // Turn on counter for timer
    TIM2_CR1 |= (1 << 0);
}

void run_servo(void) {
    // 2575 us, approx 10 degree
    TIM2_CCR1 = 2575;
    delay_ms(1500);

    // 2450us, 90 degree
    TIM2_CCR1 = 2450;
    delay_ms(1500);

    // 1800us, 0 degree
    TIM2_CCR1 = 1800;
    delay_ms(1500);
}