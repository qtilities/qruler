/*
    QRuler - Simple on-screen pixel meter.
    Copyright (C) 2021  Andrea Zanellato <redtid3@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once

#include "settings.hpp"

#include <QApplication>

namespace QRuler {
class MainWindow;
class DialogPrefs;
class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int &argc, char **argv);
    Settings &settings() { return settings_; }
    void preferences();

private:
    MainWindow *mainWindow_;
    DialogPrefs *dlgPrefs_;
    Settings settings_;
};
} // namespace QRuler
