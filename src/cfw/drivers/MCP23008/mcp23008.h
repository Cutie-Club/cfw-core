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

#ifndef MCP23008_H
#define MCP23008_H

#include "gpio.h"

#define MCP0 0xFF00
#define MCP1 0xFF01
#define MCP2 0xFF02
#define MCP3 0xFF03
#define MCP4 0xFF04
#define MCP5 0xFF05
#define MCP6 0xFF06
#define MCP7 0xFF07

typedef enum registerName
{
  IODIR   = 0x00, // IO Direction Register
  IPOL    = 0x01, // Input Polarity Register
  GPINTEN = 0x02, // Interrupt-on-Change Control Register
  DEFVAL  = 0x03, // Default Compare Register for Interrupt-on-Change
  INTCON  = 0x04, // Interrupt Control Register
  IOCON   = 0x05, // Configuration Register
  GPPU    = 0x06, // Pull-up Resistor Configuration Register
  INTF    = 0x07, // Interrupt Flag Register
  INTCAP  = 0x08, // Interrupt Capture Register
  GPIO    = 0x09, // Port (GPIO) Register
  OLAT    = 0x0A  // Output Latch Register
} registerName;

typedef enum configBit
{
  INTPOL = 1, // INT output pin polarity
  ODR    = 2, // Int pin open-drain output
  DISSLW = 4, // Slew Rate control bit for SDA output
  SEQOP  = 5  // Sequential Operation Mode
} configBit;

void mcpInit(char address);
void mcpConfigure(char address, configBit bit, char value);
void mcpWriteRegister(char address, registerName reg, char contents);
char mcpReadRegister(char address, registerName reg);

void mcpGPIOSetDirection(char address, char pin, direction dir);
void mcpGPIOSetPinState(char address, char pin, pinState outState);
int  mcpGPIOReadPinState(char address, char pin);

#endif /* MCP23008_H */
