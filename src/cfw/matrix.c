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

#define MATRIX_SIZE    (NUMBER_OF_ROWS * NUMBER_OF_COLS)
#define smallest(a, b) (a > b) ? b : a

// TODO:

// create debouncing function so that we send the correct number of keypresses
// instead of checking just the keyPressed flag here, account for debouncing
// 5ms should be fine, as that accounts for all the Cherry MX / Alps SCKx switches

// generate matrix report based on layout then send this data over USB

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
  unsigned char       scanCodeBuffer[MATRIX_SIZE];
  int                 positionCounter = 0;

  memset(keysPressed, 0, MATRIX_SIZE);
  memset(scanCodeBuffer, 0, MATRIX_SIZE);

  for (;;) {
    int           keyIndex      = 0;
    unsigned char matrixChanged = 0;
    unsigned char modifierByte  = 0;
    unsigned char ledState      = low;

    for (int rowIndex = 0; rowIndex < NUMBER_OF_ROWS; rowIndex++) {
      int matrixRowPin = rows[rowIndex];
      matrixSetPinState(PORT(matrixRowPin), PIN(matrixRowPin), low);

      for (int colIndex = 0; colIndex < NUMBER_OF_COLS; colIndex++) {
        int      matrixColPin = cols[colIndex];
        pinState flag         = matrixReadPinState(PORT(matrixColPin), PIN(matrixColPin));

        if (flag == low) {
          ledState = high;
          // if key down
          if (scanCodeLookup[keyIndex] >= KEY_LCTL) {
            unsigned char keyBit = scanCodeLookup[keyIndex] - KEY_LCTL;
            modifierByte |= (1 << keyBit);
          }
          if (!keysPressed[keyIndex]) {
            // if was up previously
            // if not mod
            if (!(scanCodeLookup[keyIndex] >= KEY_LCTL)) {
              scanCodeBuffer[positionCounter] = scanCodeLookup[keyIndex];
              positionCounter++;
            }
            matrixChanged = 1;
          }
          keysPressed[keyIndex] = 1;
        } else {
          if (keysPressed[keyIndex]) {
            // key was down, now up
            if (!(scanCodeLookup[keyIndex] >= KEY_LCTL)) {
              // delete from buffer
              int deletableIndex = -1;
              for (int i = 0; i < positionCounter; i++) {
                if ((deletableIndex != -1) && (i > deletableIndex)) {
                  scanCodeBuffer[i - 1] = scanCodeBuffer[i];
                } else if (scanCodeBuffer[i] == scanCodeLookup[keyIndex]) {
                  deletableIndex = i;
                }
              }
              positionCounter--;
            }
            matrixChanged = 1;
          }
          keysPressed[keyIndex] = 0;
        }
        keyIndex++;
      }

      matrixSetPinState(PORT(matrixRowPin), PIN(matrixRowPin), high);
    }

    if (matrixChanged) {
      buildReport(modifierByte, scanCodeBuffer, smallest(positionCounter, 6));
    }
  }

  // (we shouldn't get here, but for safety, let's
  // kill the task)
  vTaskDelete(NULL);
}
