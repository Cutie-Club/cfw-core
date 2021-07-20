# CFW Keyboard Configuration

CFW aims to abstract the requirement of any programming experience away from the end user, if they are not developing complex features. In CFW, keyboards are described using YAML, which provides several advantages over containing this configuration within C files;

- We remove the need to have duplicated, boilerplate code appearing in multiple places within the repository.

- YAML provides great flexibility in terms of data structures. Much like JSON, this flexibility can be difficult to achieve with standard environment properties, as arrays would be cumbersome and objects non-existent.

As to why we have chosen to use YAML over other choices;

- YAML supports comments.

- YAML is exceptionally human-readable.

- Being a superset of JSON, YAML can contain JSON, and can be created from JSON.

Although block order does not matter in a configuration file, we follow the convention outlined below.

## Info

At the top of a configuration file lies the `info` block. Here, the device maintainer provides information about their project, and a way to contact them in the event that their device configuration is out of date or needs corrections.

```yaml
---
  # CFW Device Configuration

  info: # required for a successful pull request
    keyboard:    Vision 750 GT
    maintainer:  kbd@amber.vision
    description: 750 GT is a 75% keyboard with integrated cable. 
```

## Hardware

The `hardware` block contains information about the device, such as the type of microcontroller used, which pins are connected to rows and columns, any LED indicators, information about connected peripherals (such as I2C devices), and device descriptors for USB communication.

### Architecture

```yaml
processor: atmega32u4 # atmega328p, atmega32u4, stm32f072, nrf52840 ... in lowercase
```

The `processor` attribute is used at compile time to generate firmware correctly for your device. A list of supported microcontrollers can be found in the documentation.

Due to CFW's use of FreeRTOS™, it may be possible to port CFW to your chosen microcontroller family. Please refer to the FreeRTOS™ documentation, namely the [FreeRTOS Kernel Ports](https://www.freertos.org/RTOS_ports.html) page to see the most up to date list of FreeRTOS™ supported devices.

### Matrix

```yaml
matrix:
  # Row and column pins in order, starting from the top left of the keyboard
  rows: [ A0, B1, C2, D3 ]
  cols: [ A1, B2, C3, D4 ]
```

The `matrix` dictionary contains arrays of row and column pins. These should be listed in order from 0 to the Nth column/row.

<!-- old -->
## USB

### USB Descriptor

#### vendor id

- do we pre-set vendor ID to denote it is a cfw device? what if we provide drivers or software to interface with cfw devices? 65536
- have a default, warn if overridden?

#### product id

- usbIF

#### version number (bcdDevice)

- could be handled by revisions

- a version number consists of two bytes; a major version and minor version
  - any hexadecimal value from `0x0000` to `0xFFFF`
  - `0x0205` gives a version number of 2.5

#### serial number

- optional
- encourage the use of uuid? rfc 4122

#### manufacturer string

- optional

#### product string

- optional

hardware:
    architecture (processor declaration)
    row pins
    column pins
<!-- version? -->

supported layouts (at least 1)

usb:
    Keyboard name
    product id

"Keymaps" work to layouts
"Keyboards" implement layouts

a "Layout" matches a standard key positioning to a matrix positioning

Keyboards contain matrix position information to translate a users keymap through a Layout

A Keymap cannot!!!! exist without a layout
A Keyboard must never directly work with a Keymap!
