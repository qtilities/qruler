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
#include "application.hpp"
#include "mainwindow.hpp"
#include "dialogabout.hpp"
#include "dialogprefs.hpp"

#include <QKeySequence>
#include <QLibraryInfo>
#include <QLocale>
#include <QMenu>
#include <QShortcut>

Qtilities::Application::Application(int argc, char *argv[])
    : QApplication(argc, argv)
    , ctxMenu_(new QMenu)
{
    setApplicationName(PROJECT_ID);
    setApplicationDisplayName(APPLICATION_NAME);
    setOrganizationName(ORGANIZATION_NAME);
    setOrganizationDomain(ORGANIZATION_DOMAIN);

    initLocale();
    initUi();
}

void Qtilities::Application::initLocale()
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
    translationsFileName = QCoreApplication::applicationName().toLower() + '_' + locale.name();

    // Try first in the same binary directory, in case we are building,
    // otherwise read from system data
    translationsPath = QCoreApplication::applicationDirPath();

    bool isLoaded = translator_.load(translationsFileName, translationsPath);
    if (!isLoaded) {
        // "/usr/share/<appname>/translations
        isLoaded = translator_.load(translationsFileName,
                                    QStringLiteral(PROJECT_DATA_DIR) + QStringLiteral("/translations"));
    }
    if (isLoaded)
        installTranslator(&translator_);
}

void Qtilities::Application::initUi()
{
    // UseHighDpiPixmaps is default from Qt6
#if QT_VERSION < 0x060000
    setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#endif
    settings_.load();

    QString icoLocalPath
        = QCoreApplication::applicationDirPath() + '/' + QStringLiteral(PROJECT_ICON_NAME);
    QString icoSysPath = QStringLiteral(PROJECT_ICON_SYSTEM_PATH);

    // Try first to find the app icon in the current/build directory
    appIcon_ = QIcon(icoLocalPath);
    if (appIcon_.isNull())
        appIcon_ = QIcon(icoSysPath);

    mainWindow_ = new Qtilities::MainWindow;
    mainWindow_->move(settings_.position());
    mainWindow_->resize(settings_.size());
    mainWindow_->setWindowIcon(appIcon_);
    mainWindow_->setWindowTitle(applicationDisplayName());
    mainWindow_->show();

    ctxMenu_->addAction(QIcon::fromTheme("help-about", QIcon(":/help-about")), tr("&About"), this,
                        &Application::about);
#if QT_VERSION < 0x060000
    ctxMenu_->addAction(QIcon::fromTheme("preferences-system", QIcon(":/preferences-system")),
                        tr("&Preferences"), this, &Application::preferences, QKeySequence::Preferences);
    ctxMenu_->addAction(QIcon::fromTheme("application-exit", QIcon(":/application-exit")), tr("&Quit"),
                        this, &QCoreApplication::quit, QKeySequence::Quit);
#else
    ctxMenu_->addAction(QIcon::fromTheme("preferences-system", QIcon(":/preferences-system")),
                        tr("&Preferences"), QKeySequence::Preferences, this, &Application::preferences);
    ctxMenu_->addAction(QIcon::fromTheme("application-exit", QIcon(":/application-exit")), tr("&Quit"),
                        QKeySequence::Quit, this, &QCoreApplication::quit);
#endif
    QShortcut *sctPrefs = new QShortcut(QKeySequence::Preferences, mainWindow_);
    QShortcut *sctQuit = new QShortcut(QKeySequence::Quit, mainWindow_);

    connect(sctPrefs, &QShortcut::activated, this, &Application::preferences);
    connect(sctQuit, &QShortcut::activated, qApp, &QCoreApplication::quit);

    connect(this, &QApplication::aboutToQuit, ctxMenu_, &QObject::deleteLater);
    connect(this, &QApplication::aboutToQuit, mainWindow_, &QObject::deleteLater);
    connect(this, &QApplication::aboutToQuit, this, [this]() {
        mainWindow_->saveSettings();
        settings_.save();
    });
}

void Qtilities::Application::about()
{
    DialogAbout about(mainWindow_);
    about.exec();
}

void Qtilities::Application::preferences()
{
    DialogPrefs prefs(mainWindow_);
    connect(&prefs, &QDialog::accepted, mainWindow_, &MainWindow::loadSettings);
    prefs.loadSettings();
    prefs.exec();
}

void Qtilities::Application::showContextMenu(const QPoint &position) { ctxMenu_->exec(position); }

int main(int argc, char *argv[])
{
    Qtilities::Application app(argc, argv);
    return app.exec();
}
