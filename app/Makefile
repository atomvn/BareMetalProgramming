########################################################################
#SILENT RULE FOR MAKEFILE
# ifneq ($(V),1)
# Q	:= @
# NULL	:= 2>/dev/null
# endif

########################################################################
#FOLDERS
INC_DIR		   = inc
OPENCM3_DIR    = ../libopencm3

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
SRC        := $(wildcard **/*.c)
SRC        += $(wildcard src/**/*.c)
OBJS := $(patsubst %.c, build/%.o, $(SRC))
ELF_FILE   = build/firmware.elf
BIN_FILE   = build/firmware.bin
HEX_FILE   = build/firmware.hex

########################################################################
#COMPILER AND LINKER FLAGS
CFLAGS = -Os -ggdb3 $(ARCH_FLAGS) -ffunction-sections -fdata-sections
LDFLAGS = -T$(LDSCRIPT) $(ARCH_FLAGS) -nostartfiles -Wl,--gc-sections -L$(OPENCM3_DIR)/lib
LDLIBS = -l$(LIBNAME)

all: $(ELF_FILE) $(BIN_FILE) $(HEX_FILE)

########################################################################
#STARTUP FILE
$(OPENCM3_DIR)/lib/lib$(LIBNAME).a:
	$(MAKE) -C $(OPENCM3_DIR)

########################################################################
#BUILD
#Compile every .c file to .o file, $<(First dependent file) = .c file, $@ = target
# %.o: %.c
# 	$(CC) $(CFLAGS) $(DEFS) -c $< -o $@
build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEFS) -c $< -o $@

#.o -> firmware.elf, link object files and libopencm3_stm321 lib to generate elf file
$(ELF_FILE): $(OBJS) $(OPENCM3_DIR)/lib/lib$(LIBNAME).a
	$(LD) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

$(BIN_FILE): $(ELF_FILE)
	$(OBJCOPY) -O binary $< $@

$(HEX_FILE): $(ELF_FILE)
	$(OBJCOPY) -O ihex $< $@

########################################################################
#CLEAN
clean:
	@rm -f *.elf *.bin *.hex 
	@rm -rf build/