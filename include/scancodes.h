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

/*
  Scancodes - taken from Keyboard/Keypad Page (0x07)
  HID Usage Tables for Universal Serial Bus (USB)
  Version 1.21 - USB.org
*/

#ifndef SCANCODES_H
#define SCANCODES_H

#define KEY_NONE 0x00
#define KEY_ERRO 0x01
#define KEY_A    0x04
#define KEY_B    0x05
#define KEY_C    0x06
#define KEY_D    0x07
#define KEY_E    0x08
#define KEY_F    0x09
#define KEY_G    0x0A
#define KEY_H    0x0B
#define KEY_I    0x0C
#define KEY_J    0x0D
#define KEY_K    0x0E
#define KEY_L    0x0F
#define KEY_M    0x10
#define KEY_N    0x11
#define KEY_O    0x12
#define KEY_P    0x13
#define KEY_Q    0x14
#define KEY_R    0x15
#define KEY_S    0x16
#define KEY_T    0x17
#define KEY_U    0x18
#define KEY_V    0x19
#define KEY_W    0x1A
#define KEY_X    0x1B
#define KEY_Y    0x1C
#define KEY_Z    0x1D
#define KEY_1    0x1E
#define KEY_2    0x1F
#define KEY_3    0x20
#define KEY_4    0x21
#define KEY_5    0x22
#define KEY_6    0x23
#define KEY_7    0x24
#define KEY_8    0x25
#define KEY_9    0x26
#define KEY_0    0x27
#define KET_RTRN 0x28
#define KEY_ESC  0x29
#define KEY_BS   0x2A
#define KEY_TAB  0x2B
#define KEY_SPC  0x2C
#define KEY_MIN  0x2D
#define KEY_EQL  0x2E
#define KEY_LBRC 0x2F
#define KEY_RBRC 0x30
#define KEY_PIPE 0x31
#define KEY_NUHT 0x32
#define KEY_COLN 0x33
#define KEY_APOS 0x34
#define KEY_GRV  0x35
#define KEY_COMM 0x36
#define KEY_DOT  0x37
#define KEY_FSLS 0x38
#define KEY_CAPS 0x39
#define KEY_F1   0x3A
#define KEY_F2   0x3B
#define KEY_F3   0x3C
#define KEY_F4   0x3D
#define KEY_F5   0x3E
#define KEY_F6   0x3F
#define KEY_F7   0x40
#define KEY_F8   0x41
#define KEY_F9   0x42
#define KEY_F10  0x43
#define KEY_F11  0x44
#define KEY_F12  0x45
#define KEY_PRT  0x46
#define KEY_SCR  0x47
#define KEY_PAUS 0x48
#define KEY_INS  0x49
#define KEY_HOME 0x4A
#define KEY_PGUP 0x4B
#define KEY_DEL  0x4C
#define KEY_END  0x4D
#define KEY_PGDN 0x4E
#define KEY_RARW 0x4F
#define KEY_LARW 0x50
#define KEY_DARW 0x51
#define KEY_UARW 0x52
#define PAD_NLCK 0x53
#define PAD_DVDE 0x54
#define PAD_ASTR 0x55
#define PAD_MINS 0x56
#define PAD_PLUS 0x57
#define PAD_ENT  0x58
#define PAD_1    0x59
#define PAD_2    0x5A
#define PAD_3    0x5B
#define PAD_4    0x5C
#define PAD_5    0x5D
#define PAD_6    0x5E
#define PAD_7    0x5F
#define PAD_8    0x60
#define PAD_9    0x61
#define PAD_0    0x62
#define PAD_DOT  0x63
#define KEY_NUBS 0x64
#define KEY_APP  0x65
#define KEY_PWR  0x66
#define PAD_EQL  0x67
#define KEY_F13  0x68
#define KEY_F14  0x69
#define KEY_F15  0x6A
#define KEY_F16  0x6B
#define KEY_F17  0x6C
#define KEY_F18  0x6D
#define KEY_F19  0x6E
#define KEY_F20  0x6F
#define KEY_F21  0x70
#define KEY_F22  0x71
#define KEY_F23  0x72
#define KEY_F24  0x73
// Add remaining keycodes later!
#define KEY_LCTL 0xE0
#define KEY_LSFT 0xE1
#define KEY_LALT 0xE2
#define KEY_LGUI 0xE3
#define KEY_RCTL 0xE4
#define KEY_RSFT 0xE5
#define KEY_RALT 0xE6
#define KEY_RGUI 0xE7

#endif /* SCANCODES_H */
