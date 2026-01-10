#include <core/rcc.h>
#include <core/gpio.h>
#include <core/systick.h>
#include <core/uart.h>
#include <core/i2c.h>
#include <mpu_6050.h>
#include <libopencm3/stm32/f1/i2c.h>

int main() {
	// Set up sys clock using pll 
    clock_setup_pll_72mhz();
	// Init systick
	systick_init(SYSCLK_HZ);
	// Init uart1
	uart1_init();
	// Init i2c1
	i2c1_init();
	// Init mpu6050
	mpu6050_init();
	// Enable GPIO and configure GPIO pin
	gpio_enable_clock(GPIOC);
	gpio_enable_clock(GPIOA);
	gpio_mode_setup(GPIOC, 13, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL);
	gpio_mode_setup(GPIOA, 0, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL);
    gpio_mode_setup(GPIOA, 3, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN);
	// Mpu6050 data struct val
	mpu6050_raw_t mpu;

	// Assign start time
	volatile uint32_t start = millis();
	while(1) {
		if (millis() - start < 2000) {
		// uart1_send_char('\n');
			// delay_ms(1000);
		// 	if (gpio_read(GPIOA, 3) == 1){
		// 		gpio_clear(GPIOA, 0);
		// 	}
		// 	else {
		// 		gpio_set(GPIOA, 0);
		// 	}
		// }
		}
		else {
			// Toggle led
			gpio_toggle(GPIOC, 13);
			// Read mpu6050 data
			mpu6050_read_raw(&mpu);
			// Print mpu6050 data
			uart1_send_string("==============MPU6050 data=================\n");
			uart1_send_string("ax: ");
			uart1_send_float(mpu.ax, 5);
			uart1_send_char('\n');
			uart1_send_string("ay: ");
			uart1_send_float(mpu.ay, 5);
			uart1_send_char('\n');
			uart1_send_string("az: ");
			uart1_send_float(mpu.az, 5);
			uart1_send_char('\n');

			uart1_send_string("gx: ");
			uart1_send_float(mpu.gx, 5);
			uart1_send_char('\n');
			uart1_send_string("gy: ");
			uart1_send_float(mpu.gy, 5);
			uart1_send_char('\n');
			uart1_send_string("gz: ");
			uart1_send_float(mpu.gz, 5);
			uart1_send_char('\n');
			// Reassign start time
			start = millis();
		} 
	}
}
