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

#include "i2c.h"
#include <util/twi.h>

void i2cInit(char i2cPeripheral) {
  TWSR = 0;
  TWBR = ((F_CPU / (8 * F_SCL)) - 2);
}

void i2cStart(char i2cPeripheral) {
  TWCR = 0xA4;

  i2cAwaitCompletion(i2cPeripheral);
  i2cCheckStatus(0, TW_START);
}

void i2cSendAddress(char i2cPeripheral, char address, i2cState state) {
  if (state == read) {
    TWDR = ((address << 1) | 0x01);
  } else {
    TWDR = (address << 1);
  }

  TWCR = 0x84;
  i2cAwaitCompletion(i2cPeripheral);
  i2cCheckStatus(0, TW_MT_SLA_ACK);
}

void i2cAwaitCompletion(char i2cPeripheral) {
  while (!(TWCR & 0x80)) {}
}

int i2cCheckStatus(char i2cPeripheral, char expectedStatus) {
  return (TW_STATUS == expectedStatus);
}

void i2cSendByte(char i2cPeripheral, char byte) {
  TWDR = byte;
  TWCR = 0x84;
  i2cAwaitCompletion(i2cPeripheral);
  i2cCheckStatus(0, TW_MT_DATA_ACK);
}

void i2cSendBytes(char i2cPeripheral, char *byteArray, int byteArraySize) {
  for (int index = 0; index < byteArraySize; index++) {
    i2cSendByte(i2cPeripheral, byteArray[index]);
  }
}

char i2cReadByteAck(char i2cPeripheral) {
  TWCR = 0xC4;
  i2cAwaitCompletion(i2cPeripheral);
  i2cCheckStatus(0, TW_SR_DATA_ACK);
  return TWDR;
}

char i2cReadByteNack(char i2cPeripheral) {
  TWCR = 0x84;
  i2cAwaitCompletion(i2cPeripheral);
  i2cCheckStatus(0, TW_SR_DATA_ACK);
  return TWDR;
}

void i2cStop(char i2cPeripheral) { TWCR = 0x94; }
