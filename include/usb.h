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

#ifndef USB_H
#define USB_H
#include "usbdrv.h"
#include <avr/interrupt.h>
#include <util/delay.h>
typedef struct {
  uint8_t modifier;
  uint8_t reserved;
  uint8_t keycode[6];
} keyboard_report_t;

void          usbSetup();
void          usbTask(void *pvParameters);
void          buildReport(unsigned char modifierByte, unsigned char scanCodeArray[],
                          int scanCodeArraySize);
void          usbLoop(void);
unsigned char usbReady(void);

#endif /* USB_H */