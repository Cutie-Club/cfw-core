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

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>

#include "usb.h"

#include "FreeRTOS.h"
#include "task.h"

#include "matrix.h"
#include "serial.h"

int main() {
  matrixInit();

  usbSetup();

  xTaskCreate(usbTask, "USB", configMINIMAL_STACK_SIZE, NULL, (configMAX_PRIORITIES - 1),
              NULL);

  xTaskCreate(matrixScanner, "matrix", configMINIMAL_STACK_SIZE, NULL,
              (configMAX_PRIORITIES - 2), NULL);

  vTaskStartScheduler();

  for (;;) {}

  return 0;
}
