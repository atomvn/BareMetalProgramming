#include <core/uart.h>

void uart1_init(void) {
    /* Enable GPIOA + USART1 clock */
    RCC_APB2ENR |= RCC_GPIOA | RCC_UART1;

        /* PA9 = TX (AF push-pull, 50MHz)
       PA10 = RX (input floating) */
    gpio_mode_setup(GPIOA, 9, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL); // PA9: AF PP, 50MHz
    gpio_mode_setup(GPIOA, 10, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT); //PA10: input floating

    /* Baudrate 9600 @72MHz */
    USART1_BRR = (468 << 4) | 12;

    /* Enable USART, TX, RX */
    USART1_CR1 = USART_CR1_UE |
                 USART_CR1_TE |
                 USART_CR1_RE;
}

void uart1_send_char(char c) {
    while (!(USART1_SR & USART_SR_TXE));
    USART1_DR = c;
}

void uart1_send_string(const char *s)
{
    while (*s) {
        uart1_send_char(*s++);
    }
}

char uart1_receive_char(void)
{
    while (!(USART1_SR & USART_SR_RXNE));
    return USART1_DR;
}

