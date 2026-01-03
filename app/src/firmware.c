#include <core/rcc.h>
// #include <libopencm3/stm32/gpio.h>
// #include <core/i2c.h>
// #include <mpu_6050.h>
#include <core/gpio.h>

int main() {
    clock_setup_pll_72mhz();
	gpio_enable_clock(GPIOC);
	gpio_enable_clock(GPIOA);
	gpio_mode_setup(GPIOC, 13, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL);
	// gpio_clear(GPIOC, 13);
	gpio_mode_setup(GPIOA, 0, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL);
	// gpio_set(GPIOA, 0);
	/* PA0: input pull-up */
    gpio_mode_setup(GPIOA, 3, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN);

	while(1) {
		if (gpio_read(GPIOA, 3) == 1){
			gpio_clear(GPIOA, 0);
		}
		else {
			gpio_set(GPIOA, 0);
		}
		// mpu6050_read_accel(&ax, &ay, &az);
		// gpio_clear(GPIOC, GPIO13);
		// // printf("Ax: %d, Ay: %d, Az: %d", ax, ay, az);
		// for (volatile int i = 0; i < 72000000; i++);	
	}
}
