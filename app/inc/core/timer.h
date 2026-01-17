#ifndef CORE_TIMER_H
#define CORE_TIMER_H
#include <libopencm3/cm3/memorymap.h>
#include <libopencm3/cm3/vector.h>

// Timer registers define
#define TIM2				    TIM2_BASE
// Timer 2, CR1 register
#define TIM_CR1(tim_base)       MMIO32((tim_base) + 0x00)
#define TIM2_CR1			    TIM_CR1(TIM2)
// Timer 2, CNT/counter register
#define TIM_CNT(tim_base)		MMIO32((tim_base) + 0x24)
#define TIM2_CNT			    TIM_CNT(TIM2)
// Timer 2, prescaler register
#define TIM_PSC(tim_base)		MMIO32((tim_base) + 0x28)
#define TIM2_PSC			    TIM_PSC(TIM2)
// Timer2, auto reload register
#define TIM_ARR(tim_base)		MMIO32((tim_base) + 0x2C)
#define TIM2_ARR			    TIM_ARR(TIM2)
// Timer 2, Capture/Compare Mode Register/
#define TIM_CCMR1(tim_base)		MMIO32((tim_base) + 0x18)
#define TIM2_CCMR1			    TIM_CCMR1(TIM2)
// Timer2, Capture/Compare register
#define TIM_CCER(tim_base)		MMIO32((tim_base) + 0x20)
#define TIM2_CCER			    TIM_CCER(TIM2)
// Timer 2, Capture/Compare register 1
#define TIM_CCR1(tim_base)		MMIO32((tim_base) + 0x34)
#define TIM2_CCR1			    TIM_CCR1(TIM2)


// Timer 2, setup function
void timer2_ch1_pwm_setup(void);
void run_servo(void);

#endif