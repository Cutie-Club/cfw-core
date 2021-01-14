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
  cfw pin format
  a 2 byte number (uint16_t)
  most significant byte stores the GPIO port 0 indexed
  for example Port A will be 0x00
  least significant byte stores the GPIO pin position in the port
  for example pin 3 will be 0x03
*/

const fs = require('fs');

const asHexByte = (num) => num.toString(16).toUpperCase().padStart(2, '0');

const writePinsToStream =
    (stream, startCharCode, endCharCode, maxPortBits, asciiOffset = 65) => {
      for (let charCode = startCharCode; charCode <= endCharCode; charCode++) {
        const portChar = String.fromCharCode(charCode);
        for (let portBit = 0; portBit < maxPortBits; portBit++) {
          const portLetterPosition = charCode - asciiOffset;

          const cfwPinHex = `0x${asHexByte(portLetterPosition)}${asHexByte(portBit)}`;

          stream.write(`#define ${portChar}${portBit} ${cfwPinHex}\n`);
        }
      }
    }

const streamWithIncludeGuard =
    (stream, fileName, callback) => {
      const includeGuardName = `${fileName.toUpperCase()}_H`;
      stream.write(`#ifndef ${includeGuardName}\n`);
      stream.write(`#define ${includeGuardName}\n\n`);
      callback(stream);
      stream.write(`\n#endif /* ${includeGuardName} */\n`);
    }

const startPort = 65; // ASCII 'A'
const lastPort  = 72; // ASCII 'H'

// megaAVR 8-bit port width
// STM32   16-bit port width
// AVR32   32-bit port width
const numberOfPortBits = 32;

const fileName   = process.argv[2] || 'pins';
const filePath   = `./${fileName}.h`;
const fileStream = fs.createWriteStream(filePath);

streamWithIncludeGuard(
    fileStream, fileName,
    (stream) => writePinsToStream(stream, startPort, lastPort, numberOfPortBits));

fileStream.on('finish', () => {console.log(`Pins macro ${filePath} created!`)})

fileStream.end();
