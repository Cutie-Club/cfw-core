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

#ifndef I2C_H
#define I2C_H

// i2c speed
#define F_SCL 400000UL

typedef enum state
{
  write, // write is active LOW
  read
} state;

void i2cInit(char i2cPeripheral);
void i2cStart(char i2cPeripheral);
void i2cSendAddress(char i2cPeripheral, char address, state state);
void i2cAwaitCompletion(char i2cPeripheral);
int  i2cCheckStatus(char i2cPeripheral, char expectedStatus);
void i2cSendByte(char i2cPeripheral, char byte);
void i2cSendData(char i2cPeripheral, char *byteArray, int byteArraySize);
char i2cReadByte(char i2cPeripheral);
void i2cStop(char i2cPeripheral);

#endif /* I2C_H */
