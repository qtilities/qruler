# QRuler

[![CI]](https://github.com/redtide/qruler/actions/workflows/build.yml)

A simple on-screen pixel meter, based on [IRuler] (SPDX ID: GPL-2.0-or-later).

![Screenshot](resources/screenshot.png)

## Dependencies

Under Debian based systems:

- cmake
- qtbase5-dev
- qttools5-dev

## Build

First time download:

```bash
git clone --recurse-submodules https://github.com/qtilities/qruler.git
```

Get missing `lxqt-build-tools` submodule:

```bash
git submodule update --init --recursive
```

then:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
cmake --build build
DESTDIR="$(pwd)/package" cmake --build build --target install
```

## Licenses

- QRuler is licensed under the [GPLv3] license.
- Application icon is from [Openclipart], [CC0-1.0] license.
- Alternative icons are part of [Oxygen icon set], [LGPLv3].

## Packages

[![Packages]](https://repology.org/project/qruler/versions)

## Translations

Translations are managed vis [LXQt Weblate] Platform.

[![Translations]](https://translate.lxqt-project.org/engage/redtide/?utm_source=widget)


[CI]:              https://github.com/redtide/qruler/actions/workflows/build.yml/badge.svg
[Packages]:        https://repology.org/badge/vertical-allrepos/qruler.svg
[CC0-1.0]:         https://creativecommons.org/publicdomain/zero/1.0/
[GPLv3]:           LICENSE
[IRuler]:          https://github.com/jjzhang166/IRuler/
[LGPLv3]:          resources/icons/COPYING
[Openclipart]:     https://openclipart.org/
[Oxygen icon set]: https://github.com/KDE/oxygen-icons/
[Translations]:    https://translate.lxqt-project.org/widgets/redtide/-/qruler/multi-auto.svg
[LXQt Weblate]:    https://translate.lxqt-project.org/projects/redtide/qruler/
