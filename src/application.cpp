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
#include "application.hpp"
#include "qruler.hpp"
#include "dialogprefs.hpp"

#include <QTranslator>

azd::Application::Application(int& argc, char** argv)
    : QApplication(argc, argv)
{
    setOrganizationName("AZDrums");
    setOrganizationDomain("azdrums.org");
    setApplicationName("QRuler");

    settings_.load();
    window_ = new QRuler;
    dlgPrefs_ = new DialogPrefs(window_);

    connect(this, &QApplication::aboutToQuit, this,
            [this]() { window_->saveSettings(); settings_.save(); });

    connect(dlgPrefs_, &QDialog::accepted, window_, &QRuler::loadSettings);

    connect(this, &QApplication::aboutToQuit, dlgPrefs_, &QObject::deleteLater);
    connect(this, &QApplication::aboutToQuit, window_, &QObject::deleteLater);
}

void azd::Application::preferences()
{
    dlgPrefs_->show();
}

int main(int argc, char* argv[])
{
    using namespace azd;
    Application app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString& locale : uiLanguages) {
        const QString baseName = "qruler_" + QLocale(locale).name();
        if (translator.load(":/translations/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }
    app.window()->move(app.settings().position());
    app.window()->resize(app.settings().size());
    app.window()->show();
    return app.exec();
}
