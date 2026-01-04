#pragma once
#include <libopencm3/stm32/f1/memorymap.h>
#include <libopencm3/cm3/common.h>

#define RCC_CR					MMIO32(RCC_BASE + 0x00)
#define RCC_CFGR				MMIO32(RCC_BASE + 0x04)
#define RCC_AHBENR				MMIO32(RCC_BASE + 0x14)
#define RCC_APB2ENR				MMIO32(RCC_BASE + 0x18)
#define RCC_APB1ENR				MMIO32(RCC_BASE + 0x1c)
#define RCC_CSR					MMIO32(RCC_BASE + 0x24)

#define FLASH_ACR			MMIO32(FLASH_MEM_INTERFACE_BASE + 0x00)

#define RCC_GPIOA               (1 << 2)
#define RCC_UART1               (1 << 14)

void clock_setup_hsi(void);
void clock_setup_hse(void);
void clock_setup_pll_72mhz(void);
