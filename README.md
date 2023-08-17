# QRuler

[![CI]](https://github.com/qtilities/qruler/actions/workflows/build.yml)

## Overview

A simple on-screen pixel meter, based on [IRuler] (SPDX ID: GPL-2.0-or-later).

![Screenshot](resources/screenshot.png)

## Dependencies

Runtime:

- Qt5/6 base

Build:

- CMake
- Qt Linguist Tools
- [Qtilitools] CMake modules
- Git (optional, to pull latest VCS checkouts)

## Build

`CMAKE_BUILD_TYPE` is usually set to `Release`, though `None` might be a valid [alternative].<br>
`CMAKE_INSTALL_PREFIX` has to be set to `/usr` on most operating systems.<br>
Using `sudo make install` is discouraged, instead use the system package manager where possible.

```bash
cmake -B build -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr -W no-dev
cmake --build build --verbose
DESTDIR="$(pwd)/package" cmake --install build
```

## Licenses

- QRuler is licensed under the [GPLv3] license.
- Application icon is from [Openclipart], [CC0-1.0] license.
- Alternative icons are part of [Oxygen icon set], [LGPLv3].

## Packages

[![Packages]](https://repology.org/project/qruler/versions)

## Translations

Translations are managed via [LXQt Weblate] Platform.

[![Translations]](https://translate.lxqt-project.org/engage/qtilities/?utm_source=widget)


[alternative]:        https://wiki.archlinux.org/title/CMake_package_guidelines#Fixing_the_automatic_optimization_flag_override
[CC0-1.0]:         https://creativecommons.org/publicdomain/zero/1.0/
[CI]:              https://github.com/qtilities/qruler/actions/workflows/build.yml/badge.svg
[GPLv3]:           LICENSE
[IRuler]:          https://github.com/jjzhang166/IRuler/
[LGPLv3]:          resources/icons/COPYING
[LXQt Weblate]:    https://translate.lxqt-project.org/projects/qtilities/qruler/
[Openclipart]:     https://openclipart.org/
[Oxygen icon set]: https://github.com/KDE/oxygen-icons/
[Packages]:        https://repology.org/badge/vertical-allrepos/qruler.svg
[Qtilitools]:      https://github.com/qtilities/qtilitools/
[Translations]:    https://translate.lxqt-project.org/widgets/qtilities/-/qruler/multi-auto.svg
