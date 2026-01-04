#include <core/rcc.h>
#include <core/gpio.h>
#include <core/systick.h>
#include <core/uart.h>

int main() {
    clock_setup_pll_72mhz();
	systick_init(SYSCLK_HZ);
	uart1_init();
	gpio_enable_clock(GPIOC);
	gpio_enable_clock(GPIOA);
	gpio_mode_setup(GPIOC, 13, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL);
	gpio_mode_setup(GPIOA, 0, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL);
    gpio_mode_setup(GPIOA, 3, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN);

	volatile uint32_t start = millis();
	while(1) {
		if (millis() - start < 2000) {
			if (gpio_read(GPIOA, 3) == 1){
				gpio_clear(GPIOA, 0);
			}
			else {
				gpio_set(GPIOA, 0);
			}
		}
		else {
			gpio_toggle(GPIOC, 13);
			start = millis();

			uart1_send_char('c');
			delay_ms(500);
		} 
	}
}
