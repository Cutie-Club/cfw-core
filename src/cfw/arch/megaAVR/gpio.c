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

// avr

void GPIOSetDirection(char port, char pin, direction dir) {
  volatile uint8_t *translatedPort;

  switch (port) {
    case 2:
      translatedPort = &DDRC;
      break;
    case 3:
      translatedPort = &DDRD;
      break;
  }

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

  switch (port) {
    case 2:
      translatedPort = &PORTC;
      break;
    case 3:
      translatedPort = &PORTD;
      break;
  }

  if (outState == high) {
    *translatedPort |= (1 << pin);
  } else {
    *translatedPort &= ~(1 << pin);
  }
};

pinState GPIOReadPinState(char port, char pin) {
  volatile uint8_t *translatedPort;

  switch (port) {
    case 2:
      translatedPort = &PINC;
      break;
    case 3:
      translatedPort = &PIND;
      break;
  }

  return (*translatedPort >> pin) & 1;
};
