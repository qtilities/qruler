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
#include "mainwindow.hpp"
#include "dialogprefs.hpp"

#include <QLibraryInfo>
#include <QLocale>
#include <QTranslator>

QRuler::Application::Application(int &argc, char **argv)
    : QApplication(argc, argv)
{
    setApplicationName(APPLICATION_NAME);
    setOrganizationName(ORGANIZATION_NAME);
    setOrganizationDomain(ORGANIZATION_DOMAIN);

#if QT_VERSION < 0x060000
    setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#endif
    settings_.load();
    mainWindow_ = new MainWindow;
    dlgPrefs_ = new DialogPrefs(mainWindow_);

    connect(dlgPrefs_, &QDialog::accepted, mainWindow_,
            &MainWindow::loadSettings);

    connect(this, &QApplication::aboutToQuit, dlgPrefs_, &QObject::deleteLater);
    connect(this, &QApplication::aboutToQuit, mainWindow_,
            &QObject::deleteLater);
    connect(this, &QApplication::aboutToQuit, this, [this]() {
        mainWindow_->saveSettings();
        settings_.save();
    });
    // no need to call mainWindow_->show() because MainWindow::loadSettings()
    // does it when setting its flags and it is called in its constructor
}

void QRuler::Application::preferences()
{
    dlgPrefs_->loadSettings();
    dlgPrefs_->show();
}

int main(int argc, char *argv[])
{
    using namespace QRuler;

    Application app(argc, argv);
    QTranslator qtTranslator, translator;
    QString filename = QStringLiteral("qt_") + QLocale::system().name();
#if QT_VERSION < 0x060000
    QString dir = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
#else
    QString dir = QLibraryInfo::path(QLibraryInfo::TranslationsPath);
#endif
    if (qtTranslator.load(filename, dir))
        app.installTranslator(&qtTranslator);

    filename = QStringLiteral(PROJECT_ID) + '_' + QLocale::system().name();
    dir = QStringLiteral(PROJECT_DATA_DIR) + QStringLiteral("/translations");

    if (translator.load(filename, dir))
        app.installTranslator(&translator);

    return app.exec();
}
