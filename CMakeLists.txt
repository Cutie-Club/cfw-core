# cutefirmware (cfw) - custom computer keyboard firmware
# Copyright (C) 2021 Cutie Club

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.10)

project(cfw VERSION 0.1.0 LANGUAGES C ASM)
set(PRODUCT_NAME cfw)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(MCU_TARGET atmega328p)
set(F_CPU 16000000UL)
set(PROG_TYPE usbasp)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)

# MMCU needs to be passed to the compiler and the linker.
set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU_TARGET})

add_compile_options(
  -DF_CPU=${F_CPU}
  -mmcu=${MCU_TARGET} # MCU
  -Os # optimize
  -Wall # enable warnings
)

# Get all source files
set(CFW_SOURCE_DIR "./src/cfw")
set(CFW_DRIVERS_DIR "./src/cfw/drivers")
set(CFW_PROTOCOLS_DIR "./src/cfw/protocols")
set(FREERTOS_SOURCE_DIR "./src/modules/FreeRTOS-Kernel")
set(VUSB_SOURCE_DIR "./src/modules/v-usb/usbdrv")

list(APPEND CFW_SOURCE_LIST "${CFW_SOURCE_DIR}/main.c"
                            "${CFW_SOURCE_DIR}/arch/megaAVR/gpio.c"
                            "${CFW_SOURCE_DIR}/matrix.c"
                            "${CFW_SOURCE_DIR}/serial.c"
                            "${CFW_SOURCE_DIR}/rtosCallbacks.c"
                            "${CFW_SOURCE_DIR}/arch/megaAVR/i2c.c"
)

list(APPEND CFW_DRIVERS_SOURCE_LIST "${CFW_DRIVERS_DIR}/MCP23008/mcp23008.c")

list(APPEND CFW_PROTOCOLS_SOURCE_LIST "${CFW_PROTOCOLS_DIR}/usb/vusb.c")

list(APPEND FREERTOS_SOURCE_LIST "${FREERTOS_SOURCE_DIR}/tasks.c"
                                 "${FREERTOS_SOURCE_DIR}/queue.c"
                                 "${FREERTOS_SOURCE_DIR}/list.c"
                                 "${FREERTOS_SOURCE_DIR}/timers.c"
                                 "${FREERTOS_SOURCE_DIR}/event_groups.c"
                                 "${FREERTOS_SOURCE_DIR}/portable/MemMang/heap_4.c"
                                 "${FREERTOS_SOURCE_DIR}/portable/ThirdParty/GCC/ATmega/port.c"
)

list(APPEND VUSB_SOURCE_LIST "${VUSB_SOURCE_DIR}/usbdrv.c"
                             "${VUSB_SOURCE_DIR}/usbdrvasm.S"
                             "${VUSB_SOURCE_DIR}/oddebug.c"
)

# Create target
add_executable(${PRODUCT_NAME} ${CFW_SOURCE_LIST} ${FREERTOS_SOURCE_LIST} ${CFW_DRIVERS_SOURCE_LIST} ${CFW_PROTOCOLS_SOURCE_LIST} ${VUSB_SOURCE_LIST})

target_include_directories(cfw PUBLIC "./include"
                                      "${CFW_DRIVERS_DIR}/MCP23008"
                                      "${FREERTOS_SOURCE_DIR}/include"
                                      "${FREERTOS_SOURCE_DIR}/portable/ThirdParty/GCC/ATmega"
                                      "${VUSB_SOURCE_DIR}"
)

# Rename the output to .elf as we will create multiple files
set_target_properties(${PRODUCT_NAME} PROPERTIES OUTPUT_NAME ${PRODUCT_NAME}.elf)

# Strip binary for upload
add_custom_target(strip ALL avr-strip ${PRODUCT_NAME}.elf DEPENDS ${PRODUCT_NAME})

# Transform binary into hex file, we ignore the eeprom segments in the step
add_custom_target(hex ALL avr-objcopy -R .eeprom -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.hex DEPENDS strip)

add_custom_target(upload avrdude  -c ${PROG_TYPE} -p ${MCU_TARGET} -U flash:w:${PRODUCT_NAME}.hex DEPENDS hex)
