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

#ifndef GPIO_H
#define GPIO_H

#define PORT(num) num >> 8   // get first byte
#define PIN(num)  num & 0xFF // get last byte

typedef enum direction
{
  input,
  input_pullup,
  input_pulldown,
  output
} direction;

typedef enum state
{
  low,
  high
} pinState;

void     GPIOSetDirection(char port, char pin, direction dir);
void     GPIOSetPinState(char port, char pin, pinState outState);
pinState GPIOReadPinState(char port, char pin);

#endif /* GPIO_H */