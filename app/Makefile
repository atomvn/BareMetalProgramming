########################################################################
#SILENT RULE FOR MAKEFILE
# ifneq ($(V),1)
# Q	:= @
# NULL	:= 2>/dev/null
# endif

########################################################################
#FOLDERS
SRC_DIR        = src
INC_DIR        = inc
OPENCM3_DIR    = ../libopencm3
SHARED_SRC_DIR = ../shared/src
SHARED_INC_DIR = ../shared/inc

########################################################################
#BINARY FILES
BINARY = firmware

########################################################################
#STM32F103C8T6 CHIP CONFIGURE
#Chose libopencm3 lib for stm32f1
LIBNAME = opencm3_stm32f1
#MACRO FOR STM32F1
DEFS 	+= -DSTM32F1 -DSTM32F103C8
#MACRO FOR C8T6
ARCH_FLAGS     = -mthumb -mcpu=cortex-m3

########################################################################
#LINKER SCRIPT
LDSCRIPT = linkerscript.ld

########################################################################
#INCLUDE PATH AND DEFINES
DEFS += -I$(OPENCM3_DIR)/include
DEFS += -I$(INC_DIR)
DEFS += -I$(SHARED_INC_DIR)

########################################################################
#CONFIGURE TOOL CHAIN
PREFIX ?= arm-none-eabi-

CC  := $(PREFIX)gcc
LD  := $(PREFIX)gcc
OBJCOPY := $(PREFIX)objcopy
OBJDUMP := $(PREFIX)objdump
GDB := $(PREFIX)gdb

########################################################################
#OBJECT FILES
OBJS += src/firmware.o
OBJS += src/core/rcc.o
OBJS += src/core/gpio.o
OBJS += src/core/systick.o
OBJS += src/core/uart.o
# OBJS += src/mpu_6050.o
# OBJS += src/core/i2c.o

########################################################################
#COMPILER AND LINKER FLAGS
CFLAGS = -Os -ggdb3 $(ARCH_FLAGS) -ffunction-sections -fdata-sections
LDFLAGS = -T$(LDSCRIPT) $(ARCH_FLAGS) -nostartfiles -Wl,--gc-sections -L$(OPENCM3_DIR)/lib
LDLIBS = -l$(LIBNAME)

all: firmware.elf firmware.bin firmware.hex

########################################################################
#STARTUP FILE
$(OPENCM3_DIR)/lib/lib$(LIBNAME).a:
	$(MAKE) -C $(OPENCM3_DIR)

########################################################################
#BUILD
#Compile every .c file to .o file, $<(First dependent file) = .c file, $@ = target
%.o: %.c
	$(CC) $(CFLAGS) $(DEFS) -c $< -o $@

#.o -> firmware.elf, link object files and libopencm3_stm321 lib to generate elf file
firmware.elf: $(OBJS) $(OPENCM3_DIR)/lib/lib$(LIBNAME).a
	$(LD) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

firmware.bin: firmware.elf
	$(OBJCOPY) -O binary $< $@

firmware.hex: firmware.elf
	$(OBJCOPY) -O ihex $< $@

########################################################################
#CLEAN
clean:
	rm -f $(OBJS) *.elf *.bin *.hex 