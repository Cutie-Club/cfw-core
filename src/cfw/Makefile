SHELL = /bin/sh
CC = avr-gcc
BUILD_DIR = ./build
FREERTOS_SOURCE_DIR = ../modules/FreeRTOS-Kernel
VUSB_SOURCE_DIR = ../modules/v-usb/usbdrv
F_CPU = 16000000UL
MCU_TARGET = atmega328p
PROGRAMMER = USBasp
CSTANDARD = c11
FREERTOS_ATMEGA_DIR = $(FREERTOS_SOURCE_DIR)/portable/ThirdParty/GCC/ATmega
TARGET = main
# end

SOURCES 					= $(TARGET).c \
										gpio.c \
										serial.c \
										rtosCallbacks.c \
										matrix.c \
										usb.c

FREERTOS_SOURCES 	=	$(FREERTOS_SOURCE_DIR)/tasks.c \
										$(FREERTOS_SOURCE_DIR)/queue.c \
										$(FREERTOS_SOURCE_DIR)/list.c \
										$(FREERTOS_SOURCE_DIR)/timers.c \
										$(FREERTOS_SOURCE_DIR)/event_groups.c \
										$(FREERTOS_SOURCE_DIR)/portable/MemMang/heap_4.c \
										$(FREERTOS_ATMEGA_DIR)/port.c

VUSB_SOURCES 			=	$(VUSB_SOURCE_DIR)/usbdrv.c \
										$(VUSB_SOURCE_DIR)/usbdrvasm.S \
										$(VUSB_SOURCE_DIR)/oddebug.c 

.PHONY: clean flash

all: $(BUILD_DIR)/$(TARGET).hex

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	@avr-objcopy -j .text -j .data -O ihex $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex

$(BUILD_DIR)/$(TARGET).elf: $(SOURCES)
	# remove -p its very naughty
	@mkdir -p $(BUILD_DIR)
	@$(CC) -std=$(CSTANDARD) -DF_CPU=$(F_CPU) -mmcu=$(MCU_TARGET) -I$(FREERTOS_SOURCE_DIR)/include -I$(FREERTOS_ATMEGA_DIR) -I$(VUSB_SOURCE_DIR) -I../../include -Wall -Os -o $(BUILD_DIR)/$(TARGET).elf $(FREERTOS_SOURCES) $(VUSB_SOURCES) $(SOURCES)

flash: all
	@avrdude -p $(MCU_TARGET) -c $(PROGRAMMER) -P /dev/cu.usbmodem14311 -e -U flash:w:$(BUILD_DIR)/$(TARGET).hex 

clean: 
	@rm -rf $(BUILD_DIR)
