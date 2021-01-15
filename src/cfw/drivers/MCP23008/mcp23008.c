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

#include "mcp23008.h"
#include "i2c.h"

void mcpInit(char address) {
  i2cInit(0);
  // disable sequential operation
  mcpConfigure(address, SEQOP, 1);
}

void mcpConfigure(char address, configBit bit, char value) {
  char configRegister = mcpReadByte(address, IOCON);
  configRegister |= (1 << bit);
  mcpWriteByte(address, IOCON, configRegister);
}

void mcpWriteByte(char address, registerName reg, char byte) {
  i2cStart(0);
  i2cSendAddress(0, address, write);
  i2cSendByte(0, reg);
  i2cSendByte(0, byte);
  i2cStop(0);
}

char mcpReadByte(char address, registerName reg) {
  char byte;
  i2cStart(0);
  i2cSendAddress(0, address, write);
  i2cSendByte(0, reg);
  i2cStart(0);
  i2cSendAddress(0, address, read);
  byte = i2cReadByte(0);
  i2cStop(0);
  return byte;
}

void mcpGPIOSetDirection(char address, char pin, direction dir) {
  char dirRegister    = mcpReadByte(address, IODIR);
  char pullupRegister = mcpReadByte(address, GPPU);
  char pullupChanged  = 0;

  switch (dir) {
    case input:
      dirRegister |= (1 << pin);
      break;
    case input_pullup:
      dirRegister |= (1 << pin);
      pullupRegister |= (1 << pin);
      pullupChanged = 1;
      break;
    case output:
      dirRegister &= ~(1 << pin);
      break;
  }

  mcpWriteByte(address, IODIR, dirRegister);
  if (pullupChanged) { mcpWriteByte(address, GPPU, pullupRegister); }
}

void mcpGPIOSetPinState(char address, char pin, pinState outState) {
  char GPIOregister = mcpReadByte(address, GPIO);

  switch (outState) {
    case high:
      GPIOregister |= (1 << pin);
      break;

    case low:
      GPIOregister &= ~(1 << pin);
      break;
  }

  mcpWriteByte(address, GPIO, GPIOregister);
}

int mcpGPIOReadPinState(char address, char pin) {
  char GPIOregister = mcpReadByte(address, GPIO);
  return (GPIOregister >> pin);
}
