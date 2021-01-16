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

#ifndef MATRIX_H
#define MATRIX_H

#include "mcp23008.h"
#include "pins.h"
#include "scancodes.h"

#define MCP_ADDR 0b00100000

#define NUMBER_OF_COLS 14
#define NUMBER_OF_ROWS 5
#define COLS \
  { MCP0, D4, C0, B5, D5, B4, D6, B1, B0, B2, D7, B3, MCP2, MCP1 }
#define ROWS \
  { D0, C3, D1, C1, C2 }

#define KEY_MAP                                                                        \
  {                                                                                    \
    KEY_ESC, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,     \
        KEY_MIN, KEY_EQL, KEY_BS, KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y,   \
        KEY_U, KEY_I, KEY_O, KEY_P, KEY_LBRC, KEY_RBRC, KEY_NONE, KEY_CAPS, KEY_A,     \
        KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_COLN, KEY_APOS,    \
        KEY_NUHT, KEY_RTRN, KEY_LSFT, KEY_NUBS, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B,     \
        KEY_N, KEY_M, KEY_COMM, KEY_DOT, KEY_FSLS, KEY_RSFT, KEY_PRT, KEY_LCTL,        \
        KEY_LGUI, KEY_LALT, KEY_NONE, KEY_NONE, KEY_NONE, KEY_SPC, KEY_NONE, KEY_NONE, \
        KEY_NONE, KEY_RALT, KEY_APP, KEY_RGUI, KEY_RCTL                                \
  }

void matrixInit();
void matrixScanner(void *pvParameters);

#endif /* MATRIX_H */
