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

#include "usb.h"
#include "FreeRTOS.h"
#include "task.h"
#include <string.h>

static unsigned char     idleRate;
static keyboard_report_t keyboard_report;

void usbSetup() {
  usbInit();

  usbDeviceDisconnect(); // enforce re-enumeration
  _delay_ms(255);
  usbDeviceConnect();

  sei(); // Enable interrupts after re-enumeration
}

usbMsgLen_t usbFunctionSetup(unsigned char data[8]) {
  usbRequest_t *rq = (void *)data;

  if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) {
    switch (rq->bRequest) {
      case USBRQ_HID_GET_REPORT:
        // send "no keys pressed" if asked here
        // wValue: ReportType (highbyte), ReportID (lowbyte)
        usbMsgPtr                  = (void *)&keyboard_report; // we only have this one
        keyboard_report.modifier   = 0;
        keyboard_report.keycode[0] = 0;
        return sizeof(keyboard_report);
      case USBRQ_HID_SET_REPORT: // if wLength == 1, should be LED state
        return (rq->wLength.word == 1) ? USB_NO_MSG : 0;
      case USBRQ_HID_GET_IDLE: // send idle rate to PC as required by spec
        usbMsgPtr = &idleRate;
        return 1;
      case USBRQ_HID_SET_IDLE: // save idle rate as required by spec
        idleRate = rq->wValue.bytes[1];
        return 0;
    }
  }

  return 0; // by default don't return any data
}

usbMsgLen_t usbFunctionWrite(uint8_t *data, unsigned char len) {
  return 1; // Data read, not expecting more
}

void sendReport(void) {
  usbSetInterrupt((void *)&keyboard_report, sizeof(keyboard_report));
}

void buildReport(char scanCodeArray[], int scanCodeArraySize) {
  keyboard_report.modifier = 0;

  for (int i = 0; i < 6; i++) { keyboard_report.keycode[i] = 0; }
  for (int i = 0; i < scanCodeArraySize; i++) {
    keyboard_report.keycode[i] = scanCodeArray[i];
  }

  if (usbReady()) { sendReport(); }
}

void usbLoop(void) { usbPoll(); }

unsigned char usbReady(void) { return usbInterruptIsReady(); }

PROGMEM const char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {
    0x05, 0x01, // USAGE_PAGE (Generic Desktop)
    0x09, 0x06, // USAGE (Keyboard)
    0xa1, 0x01, // COLLECTION (Application)
    0x05, 0x07, //   USAGE_PAGE (Keyboard)(Key Codes)
    0x19, 0xe0, //   USAGE_MINIMUM (Keyboard LeftControl)(224)
    0x29, 0xe7, //   USAGE_MAXIMUM (Keyboard Right GUI)(231)
    0x15, 0x00, //   LOGICAL_MINIMUM (0)
    0x25, 0x01, //   LOGICAL_MAXIMUM (1)
    0x75, 0x01, //   REPORT_SIZE (1)
    0x95, 0x08, //   REPORT_COUNT (8)
    0x81, 0x02, //   INPUT (Data,Var,Abs) ; Modifier byte
    0x95, 0x01, //   REPORT_COUNT (1)
    0x75, 0x08, //   REPORT_SIZE (8)
    0x81, 0x03, //   INPUT (Cnst,Var,Abs) ; Reserved byte
    0x95, 0x05, //   REPORT_COUNT (5)
    0x75, 0x01, //   REPORT_SIZE (1)
    0x05, 0x08, //   USAGE_PAGE (LEDs)
    0x19, 0x01, //   USAGE_MINIMUM (Num Lock)
    0x29, 0x05, //   USAGE_MAXIMUM (Kana)
    0x91, 0x02, //   OUTPUT (Data,Var,Abs) ; LED report
    0x95, 0x01, //   REPORT_COUNT (1)
    0x75, 0x03, //   REPORT_SIZE (3)
    0x91, 0x03, //   OUTPUT (Cnst,Var,Abs) ; LED report padding
    0x95, 0x06, //   REPORT_COUNT (6)
    0x75, 0x08, //   REPORT_SIZE (8)
    0x15, 0x00, //   LOGICAL_MINIMUM (0)
    0x25, 0x65, //   LOGICAL_MAXIMUM (101)
    0x05, 0x07, //   USAGE_PAGE (Keyboard)(Key Codes)
    0x19, 0x00, //   USAGE_MINIMUM (Reserved (no event indicated))(0)
    0x29, 0x65, //   USAGE_MAXIMUM (Keyboard Application)(101)
    0x81, 0x00, //   INPUT (Data,Ary,Abs)
    0xc0        // END_COLLECTION
};

void usbTask(void *pvParameters) {
  TickType_t       xLastWakeTime;
  const TickType_t xFrequency = 1;

  // Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount();

  for (;;) {
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    usbLoop();
  }

  // (we shouldn't get here, but for safety, let's
  // kill the task)
  vTaskDelete(NULL);
}