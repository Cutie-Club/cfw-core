# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- Modifier keycode support.
- I2C driver for megaAVR.
- MCP23008 I2C I/O Expander driver.

### Changed

- Fix grammar in README.md
- Fix repository link in install example in README.md
- i2cSendData() is now i2cSendBytes() for consistency.

### Removed

- Unused makefile

## 0.1.0 - 2021-01-10

### Added

- Submodules for the FreeRTOS kernel and V-USB.
- CMake build system generation config.
- Matrix initialisation and scanning task.
- USB initialisation and polling task.
- Basic FreeRTOS callbacks from the FreeRTOS example.
- megaAVR serial for debugging.
- JS utility for creating pin definitions.
- GPIO control for megaAVR MCUs (only configured for registers C and D thus far).
- Some HID scancodes (but not all of the specification yet).
