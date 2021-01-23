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

#include "matrix.h"
#include "FreeRTOS.h"
#include "gpio.h"
#include "mcp23008.h"
#include "scancodes.h"
#include "task.h"
#include "usb.h"
#include <avr/io.h>
#include <string.h>

#define MATRIX_SIZE (NUMBER_OF_ROWS * NUMBER_OF_COLS)
#define REPORT_SIZE 6

int cols[NUMBER_OF_COLS] = COLS;
int rows[NUMBER_OF_ROWS] = ROWS;

void matrixSetDirection(unsigned char port, char pin, direction dir) {
  switch (port) {
    case 0xFF:
      mcpGPIOSetDirection(MCP_ADDR, pin, dir);
      break;
    default:
      GPIOSetDirection(port, pin, dir);
      break;
  }
}

void matrixSetPinState(unsigned char port, char pin, pinState state) {
  switch (port) {
    case 0xFF:
      mcpGPIOSetPinState(MCP_ADDR, pin, state);
      break;
    default:
      GPIOSetPinState(port, pin, state);
      break;
  }
}

char matrixReadPinState(unsigned char port, char pin) {
  switch (port) {
    case 0xFF:
      return mcpGPIOReadPinState(MCP_ADDR, pin);
      break;
    default:
      return GPIOReadPinState(port, pin);
      break;
  }
}

void matrixInit() {
  mcpInit(MCP_ADDR);
  // set column pins as input pins
  for (unsigned char colIndex = 0; colIndex < NUMBER_OF_COLS; colIndex++) {
    int matrixColPin = cols[colIndex];
    matrixSetDirection(PORT(matrixColPin), PIN(matrixColPin), input_pullup);
  }

  // set row pins as output pins
  for (unsigned char rowIndex = 0; rowIndex < NUMBER_OF_ROWS; rowIndex++) {
    int matrixRowPin = rows[rowIndex];
    matrixSetDirection(PORT(matrixRowPin), PIN(matrixRowPin), output);
  }
  mcpGPIOSetDirection(MCP_ADDR, 3, output);
  mcpGPIOSetDirection(MCP_ADDR, 4, output);
}

void matrixScanner(void *pvParameters) {
  const unsigned char scanCodeLookup[MATRIX_SIZE] = KEY_MAP;
  unsigned char       keysPressed[MATRIX_SIZE];
  memset(keysPressed, 0, MATRIX_SIZE);

  for (;;) {
    int           keyIndex      = 0;
    unsigned char matrixChanged = 0;

    for (int rowIndex = 0; rowIndex < NUMBER_OF_ROWS; rowIndex++) {
      int matrixRowPin = rows[rowIndex];
      matrixSetPinState(PORT(matrixRowPin), PIN(matrixRowPin), low);

      for (int colIndex = 0; colIndex < NUMBER_OF_COLS; colIndex++) {
        int      matrixColPin = cols[colIndex];
        pinState flag         = matrixReadPinState(PORT(matrixColPin), PIN(matrixColPin));

        if (flag == low) {
          if (!keysPressed[keyIndex]) {
            // key was up, now down
            matrixChanged = 1;
          }
          keysPressed[keyIndex] = 1;
        } else {
          if (keysPressed[keyIndex]) {
            // key was down, now up
            matrixChanged = 1;
          }
          keysPressed[keyIndex] = 0;
        }
        keyIndex++;
      }

      matrixSetPinState(PORT(matrixRowPin), PIN(matrixRowPin), high);
    }

    if (matrixChanged) {
      // generate scanCodeBuffer
      // generate modifierByte
      unsigned char scanCodeBuffer[REPORT_SIZE];
      memset(scanCodeBuffer, 0, REPORT_SIZE);

      unsigned char modifierByte    = 0;
      int           positionCounter = 0;

      for (int i = 0; i < MATRIX_SIZE; i++) {
        if (keysPressed[i]) {
          // is it a modifier?
          if (scanCodeLookup[i] >= (unsigned)KEY_LCTL) {
            char modBit = scanCodeLookup[i] - (unsigned)KEY_LCTL;
            modifierByte |= (1 << modBit);
          } else {
            // make scanCodeBuffer
            if (positionCounter < REPORT_SIZE) {
              scanCodeBuffer[positionCounter] = scanCodeLookup[i];
              positionCounter++;
            } else {
              memset(scanCodeBuffer, KEY_ERRO, REPORT_SIZE);
              break;
              // 6KRO overflow event, break!
            }
          }
        }
      }

      buildReport(modifierByte, scanCodeBuffer, REPORT_SIZE);
    }
  }

  // (we shouldn't get here, but for safety, let's
  // kill the task)
  vTaskDelete(NULL);
}
