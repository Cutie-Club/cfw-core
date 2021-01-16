/*
  cutefirmware (cfw) - custom computer keyboard firmware
  Copyright (C) 2021 Cutie Club

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "gpio.h"
#include <avr/io.h>

#define BUILD_REG(reg, port) reg##port

#define SET_TRANS_PORT(reg)                \
  switch (port) {                          \
    case 1:                                \
      translatedPort = &BUILD_REG(reg, B); \
      break;                               \
    case 2:                                \
      translatedPort = &BUILD_REG(reg, C); \
      break;                               \
    case 3:                                \
      translatedPort = &BUILD_REG(reg, D); \
      break;                               \
  }

void GPIOSetDirection(char port, char pin, direction dir) {
  volatile uint8_t *translatedPort;

  SET_TRANS_PORT(DDR)

  switch (dir) {
    case input:
      *translatedPort &= ~(1 << pin);
      break;
    case input_pullup:
      // set pin state to input
      *translatedPort &= ~(1 << pin);
      // then set the PORTx to high to enable
      GPIOSetPinState(port, pin, high);
      break;
    case input_pulldown:
      // no pulldowns available on AVR
      break;
    case output:
      *translatedPort |= (1 << pin);
      break;
  }
};

void GPIOSetPinState(char port, char pin, pinState outState) {
  volatile uint8_t *translatedPort;

  SET_TRANS_PORT(PORT)

  if (outState == high) {
    *translatedPort |= (1 << pin);
  } else {
    *translatedPort &= ~(1 << pin);
  }
};

pinState GPIOReadPinState(char port, char pin) {
  volatile uint8_t *translatedPort;

  SET_TRANS_PORT(PIN)

  return (*translatedPort >> pin) & 1;
};
