#ifndef CORE_EXTI_H
#define CORE_EXTI_H

#include <libopencm3/cm3/memorymap.h>
#include <libopencm3/cm3/vector.h>

/** EXTI Interrupt Mask Registers */
#define EXTI_IMR			MMIO32(EXTI_BASE + 0x00)
/** EXTI Event Mask Register */
#define EXTI_EMR			MMIO32(EXTI_BASE + 0x04)
/** EXTI Rising Trigger Selection Register */
#define EXTI_RTSR			MMIO32(EXTI_BASE + 0x08)
/** EXTI Falling Triger Selection Register */
#define EXTI_FTSR			MMIO32(EXTI_BASE + 0x0c)
/** EXTI Software Interrupt Event Register */
#define EXTI_SWIER			MMIO32(EXTI_BASE + 0x10)
/** EXTI Pending Register */
#define EXTI_PR				MMIO32(EXTI_BASE + 0x14)

// AFIO
#define AFIO_EXTICR1        MMIO32(AFIO_BASE + 0x08)

// NVIC enable register
#define NVIC_ISER0          (*(volatile uint32_t *)0xE000E100)

// Flag to decide when to read MPU6050
extern volatile uint8_t mpu_int_flag;

// Configure PA0 as input floating
void gpio_exti_pa0_init(void);

// Map PA0 -> EXTI0
void afio_exti0_map_pa0(void);

// Setup EXTI0, unmask interrupt, rising edge, clear pending bit
void exti0_init(void);

// Enable NVIC for EXTI0
void nvic_exti0_enable(void);

#endif
