/*
    QRuler - Simple on-screen pixel meter.
    Copyright (C) 2013  Awesomez-Qt (as IRuler)
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
#include "mainwindow.hpp"
#include "application.hpp"
#include "dialogabout.hpp"

#include <QCoreApplication>
#include <QDebug>
#include <QFont>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QTextStream>

namespace Default {
static const QSize minimumSize = QSize(120, 100);
static const QString fontFamily = QStringLiteral("monospace");
static const int measureFontSize = 10;
static const int fontSize = 7;
} // namespace Default

QRuler::MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , mnuContext_(new QMenu(this))
{
    QIcon iconAbout = QIcon::fromTheme("help-about", QIcon(":/help-about"));
    QIcon iconPrefs
        = QIcon::fromTheme("preferences-system", QIcon(":/preferences-system"));
    QIcon iconQuit
        = QIcon::fromTheme("application-exit", QIcon(":/application-exit"));

    Application *theApp = static_cast<Application *>(qApp);

    QAction *actPrefs = mnuContext_->addAction(tr("&Preferences"), theApp,
                                               &Application::preferences);
    QAction *actAbout
        = mnuContext_->addAction(tr("&About"), this, &MainWindow::about);
    QAction *actQuit
        = mnuContext_->addAction(tr("&Quit"), qApp, &QCoreApplication::quit);

    actPrefs->setShortcuts(QKeySequence::Preferences);
    actQuit->setShortcuts(QKeySequence::Quit);

    actAbout->setIcon(iconAbout);
    actPrefs->setIcon(iconPrefs);
    actQuit->setIcon(iconQuit);

    mnuContext_->addAction(actAbout);
    mnuContext_->addAction(actPrefs);
    mnuContext_->addSeparator();
    mnuContext_->addAction(actQuit);

    setWindowIcon(QIcon(":/appicon"));
    setMouseTracking(true);
    loadSettings();
}

void QRuler::MainWindow::loadSettings()
{
    Settings &settings = static_cast<Application *>(qApp)->settings();
    qreal opacity = settings.opacity().toDouble();
    Qt::WindowFlags flags = Qt::FramelessWindowHint;

    setAttribute(Qt::WA_TranslucentBackground);
    setWindowOpacity(opacity);
    if (settings.alwaysOnTop())
        flags |= Qt::WindowStaysOnTopHint;

    setWindowFlags(flags);
    resize(settings.size());
    move(settings.position());
    show(); // update the flags
}

void QRuler::MainWindow::saveSettings()
{
    Settings &settings = static_cast<Application *>(qApp)->settings();
    settings.setPosition(pos());
    settings.setSize(size());
}

QSize QRuler::MainWindow::minimumSizeHint() const { return sizeHint(); }

QSize QRuler::MainWindow::sizeHint() const { return Default::minimumSize; }

void QRuler::MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        changeWidth = event->x() > this->width() - 5;
        changeHeight = event->y() > this->height() - 5;
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    } else if (event->button() == Qt::RightButton) {
        mnuContext_->exec(this->cursor().pos());
    }
}

void QRuler::MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->x() > this->width() - 5) {
        this->setCursor(Qt::SizeHorCursor);
    } else if (event->y() > this->height() - 5) {
        this->setCursor(Qt::SizeVerCursor);
    } else {
        this->setCursor(Qt::ArrowCursor);
    }
    if (event->buttons() == Qt::LeftButton) {
        if ((changeWidth && !changeHeight)) {
            int x = event->pos().x();
            if (x > 30) {
                this->setFixedWidth(x);
            }
        } else if (!changeWidth && changeHeight) {
            int y = event->pos().y();
            if (y > 30) {
                this->setFixedHeight(y);
            }
        } else {
            move(event->globalPos() - dragPosition);
            event->accept();
        }
    }
}

void QRuler::MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    Settings &settings = static_cast<Application *>(qApp)->settings();
    int width = this->width();
    int height = this->height();
    QString showText = tr("Width:") + QString::number(width) + tr("px") + "\n"
                       + tr("Height:") + QString::number(height) + tr("px");

    painter.fillRect(rect(), settings.backgroundColor());

    drawXLine();
    drawYLine();

    QPainter painter2(this);
    painter2.setPen(QPen(settings.borderColor(), 1));
    painter2.drawRect(0, 0, width - 1, height - 1);
    painter2.setPen(QPen(settings.foregroundColor(), 1));
    painter2.setFont(QFont(Default::fontFamily, Default::measureFontSize));
    painter2.drawText(rect(), Qt::AlignCenter, showText);
}

void QRuler::MainWindow::drawXLine()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(QPen(Qt::black, 1));

    int lineHeight = 5;
    for (int i = 0; i < this->width(); i += 2) {
        lineHeight = 5;

        if (i % 10 == 0) {
            lineHeight = 10;
        }
        if (i % 50 == 0 && i > 0) {
            lineHeight = 15;
            painter.setFont(
                QFont(Default::fontFamily, Default::fontSize, QFont::Bold));
            painter.drawText(i, 20, 25, 10, Qt::AlignLeft, QString::number(i));
        }
        painter.drawLine(QPoint(i, 0), QPoint(i, lineHeight));
    }
}

void QRuler::MainWindow::drawYLine()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(QPen(Qt::black, 1));

    int lineHeight = 5;
    for (int i = 0; i < this->height(); i += 2) {
        lineHeight = 5;

        if (i % 10 == 0) {
            lineHeight = 10;
        }
        if (i % 50 == 0 && i > 0) {
            lineHeight = 15;
            painter.setFont(
                QFont(Default::fontFamily, Default::fontSize, QFont::Bold));
            painter.drawText(20, i, 25, 10, Qt::AlignLeft, QString::number(i));
        }
        painter.drawLine(QPoint(0, i), QPoint(lineHeight, i));
    }
}

void QRuler::MainWindow::about()
{
    QStringList list = {":/info", ":/authors", ":/license"};
    QStringList texts;

    for (const QString &item : list) {
        QFile f(item);
        if (!f.open(QFile::ReadOnly | QFile::Text)) {
            qDebug() << "Error loading about file" << '\n';
            return;
        }
        QTextStream in(&f);
        texts.append(in.readAll());
        f.close();
    }

    DialogAbout about;
    about.setInfoText(texts.at(0));
    about.setAuthorsText(texts.at(1));
    about.setLicenseText(texts.at(2));
    about.exec();
}
