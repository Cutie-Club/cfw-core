# cfw

## About

cutefirmware (cfw) is custom computer keyboard firmware using [FreeRTOS™](https://www.freertos.org/).

This project adheres to [Semantic Versioning](https://semver.org/). For detailed version history, see [CHANGELOG.md](./CHANGELOG.md).

## Installing

To install the development environment, clone this repository recursively;

```sh
git clone --recursive git@github.com:Cutie-Club/cfw-core.git
```

If you already have a clone of this repository, you can use `git submodule update --init --recursive` to download the submodules.

## Building

cfw uses a CMake build system. To build, enter the `build` directory and enter the following command;

```sh
cmake --build .
```

This will build the project and create a `.hex` file.

To build and flash, specify the `upload` target.

```sh
cmake --build . --target upload
```

Make sure your MCU has been reset and is ready for flashing.

## Contributing

cfw is in the early stages of development; we welcome contributions of any nature as end users should assume any part of this software may change and or break at any time. Please do not submit configurations or layouts for specific keyboards to this library at this time - a separate keyboards repository that submodules cfw-core will be created for these.

## Licence

This software is licenced under the [GNU General Public Licence v3.0](https://www.gnu.org/licenses/gpl-3.0.html), or any later version.

SPDX-License-Identifier: (GPL-3.0-or-later)
Copyright (C) 2021 Cutie Club

![GNU GPLv3 or later](https://www.gnu.org/graphics/gplv3-or-later.png)
