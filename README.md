# QRuler

[![CI][1]](https://github.com/redtide/qruler/actions/workflows/build.yml)

A simple on-screen pixel meter.

![Screenshot](screenshot.png)

## Dependencies

Under Debian based systems:
- cmake
- qtbase5-dev
- qttools5-dev

## Build
```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
cmake --build build
DESTDIR="$(pwd)/buildpackage" cmake --build build --target install
```

## Licenses

QRuler is licensed under the [GPLv3][2] license.
Application icon is from [openclipart][3], [CC0-1.0][4] license.
Alternative icons are part of [Oxygen icon set][5], [LGPLv3][6].


[1]: https://github.com/redtide/qruler/actions/workflows/build.yml/badge.svg
[2]: LICENSE
[3]: https://openclipart.org/
[4]: https://creativecommons.org/publicdomain/zero/1.0/
[5]: https://github.com/KDE/oxygen-icons/
[6]: resources/icons/COPYING
