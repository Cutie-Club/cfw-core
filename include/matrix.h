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

#include "pins.h"
#include "scancodes.h"

#define NUMBER_OF_COLS 1
#define NUMBER_OF_ROWS 5
#define COLS \
  { D6 }
#define ROWS \
  { D0, C3, D1, C1, C2 }

#define KEY_MAP \
  { KEY_LSFT, KEY_T, KEY_1, KEY_LBRC, KEY_RALT }
// col 6 pd6
// row 4 pc2

void matrixInit();
void matrixScanner(void *pvParameters);

#endif /* MATRIX_H */