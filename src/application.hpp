/*
    QRuler - Simple on-screen pixel meter.
    Copyright (C) 2021-2023 Andrea Zanellato <redtid3@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 3 of the License.

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
#include <QIcon>
#include <QTranslator>

class QMenu;

namespace Qtilities {

class MainWindow;
class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int argc, char *argv[]);
    void about();
    void preferences();
    void showContextMenu(const QPoint &);
    QIcon icon() const { return appIcon_; }
    Settings &settings() { return settings_; }

private:
    void initLocale();
    void initUi();

    MainWindow *mainWindow_;
    Settings settings_;

    QIcon appIcon_;
    QMenu *ctxMenu_;
    QTranslator qtTranslator_;
    QTranslator translator_;
};
} // namespace Qtilities
