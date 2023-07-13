/*
    QRuler - Simple on-screen pixel meter.
    Copyright (C) 2021 Andrea Zanellato <redtid3@gmail.com>

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
#include "application.hpp"
#include "mainwindow.hpp"
#include "dialogprefs.hpp"

#include <QLibraryInfo>
#include <QLocale>

QRuler::Application::Application(int argc, char *argv[])
    : QApplication(argc, argv)
{
    setApplicationName(APPLICATION_NAME);
    setOrganizationName(ORGANIZATION_NAME);
    setOrganizationDomain(ORGANIZATION_DOMAIN);

    initLocale();

    QString icoCurPath = QCoreApplication::applicationDirPath() + '/'
                         + QStringLiteral(PROJECT_ICON_NAME);
    QString icoSysPath = QStringLiteral(PROJECT_ICON_SYSTEM_PATH);

    // Try first to find the app icon in the current directory
    appIcon_ = QIcon(icoCurPath);
    if (appIcon_.isNull())
        appIcon_ = QIcon(icoSysPath);

        // UseHighDpiPixmaps is default from Qt6
#if QT_VERSION < 0x060000
    setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#endif
    initUi();
}

void QRuler::Application::initLocale()
{
#if 1
    QLocale locale = QLocale::system();
#else
    QLocale locale(QLocale("it"));
    QLocale::setDefault(locale);
#endif
    // Qt translations (buttons and the like)
    QString translationsPath
#if QT_VERSION < 0x060000
        = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
#else
        = QLibraryInfo::path(QLibraryInfo::TranslationsPath);
#endif
    QString translationsFileName = QStringLiteral("qt_") + locale.name();

    if (qtTranslator_.load(translationsFileName, translationsPath))
        installTranslator(&qtTranslator_);

    // E.g. "<appname>_en"
    translationsFileName
        = QCoreApplication::applicationName().toLower() + '_' + locale.name();

    // Try first in the same binary directory, in case we are building,
    // otherwise read from system data
    translationsPath = QCoreApplication::applicationDirPath();

    bool isLoaded = translator_.load(translationsFileName, translationsPath);
    if (!isLoaded) {
        // "/usr/share/<appname>/translations
        isLoaded = translator_.load(translationsFileName,
                                    QStringLiteral(PROJECT_DATA_DIR)
                                        + QStringLiteral("/translations"));
    }
    if (isLoaded)
        installTranslator(&translator_);
}

void QRuler::Application::initUi()
{
    settings_.load();

    mainWindow_ = new QRuler::MainWindow;
    dlgPrefs_ = new QRuler::DialogPrefs(mainWindow_);

    mainWindow_->move(settings_.position());
    mainWindow_->resize(settings_.size());
    mainWindow_->show();

    connect(dlgPrefs_, &QDialog::accepted, mainWindow_,
            &MainWindow::loadSettings);

    connect(this, &QApplication::aboutToQuit, dlgPrefs_, &QObject::deleteLater);
    connect(this, &QApplication::aboutToQuit, mainWindow_,
            &QObject::deleteLater);
    connect(this, &QApplication::aboutToQuit, this, [this]() {
        mainWindow_->saveSettings();
        settings_.save();
    });
}

void QRuler::Application::preferences()
{
    dlgPrefs_->loadSettings();
    dlgPrefs_->show();
}

int main(int argc, char *argv[])
{
    QRuler::Application app(argc, argv);
    return app.exec();
}
