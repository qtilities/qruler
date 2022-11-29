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
#include "qruler.hpp"
#include "application.hpp"
#include "dialogprefs.hpp"

#include <QCoreApplication>
#include <QDebug>
#include <QMouseEvent>
#include <QPen>
#include <QFont>
#include <QPainter>
#include <QMenu>
#include <QDesktopServices>
#include <QMessageBox>
#include <QShortcut>
#include <QTextStream>

azd::QRuler::QRuler(QWidget* parent)
    : QWidget(parent)
    , mnuContext_(new QMenu(this))
{
    QAction* actQuit = new QAction(QIcon::fromTheme("application-exit"), tr("Quit"), this);
    QKeySequence seqQuit = QKeySequence(Qt::CTRL + Qt::Key_Q);
    QShortcut* sctQuit = new QShortcut(seqQuit, this);
    actQuit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    connect(actQuit, &QAction::triggered, QCoreApplication::instance(), &QCoreApplication::quit);
    connect(sctQuit, &QShortcut::activated, QCoreApplication::instance(), &QCoreApplication::quit);

    QAction* actAbout = new QAction(QIcon::fromTheme("help-about"), "About", this);
    connect(actAbout, &QAction::triggered, this, &QRuler::onAboutClicked);

    Application* theApp = static_cast<Application*>(qApp);

    QAction* actPrefs = new QAction(QIcon::fromTheme("preferences-system"), "Preferences", this);
    QKeySequence seqPrefs = QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_P);
    QShortcut* sctPrefs = new QShortcut(seqPrefs, this);
    actPrefs->setShortcut(seqPrefs);
    connect(actPrefs, &QAction::triggered, theApp, &Application::preferences);
    connect(sctPrefs, &QShortcut::activated, theApp, &Application::preferences);

    mnuContext_->addAction(actAbout);
    mnuContext_->addAction(actPrefs);
    mnuContext_->addSeparator();
    mnuContext_->addAction(actQuit);

    setMouseTracking(true);
    setWindowTitle(QCoreApplication::applicationName());
    // setWindowIcon(QIcon(":appicon"));

    loadSettings();
}

void azd::QRuler::loadSettings()
{
    Settings& settings = static_cast<Application*>(qApp)->settings();
    setAttribute(Qt::WA_TranslucentBackground);
    qreal opacity = settings.opacity().toDouble();
    setWindowOpacity(opacity);

    Qt::WindowFlags flags = Qt::FramelessWindowHint;
    if (settings.alwaysOnTop())
        flags |= Qt::WindowStaysOnTopHint;

    setWindowFlags(flags);
    show();
}

void azd::QRuler::saveSettings()
{
    Settings& settings = static_cast<Application*>(qApp)->settings();
    settings.setPosition(pos());
    settings.setSize(size());
}

QSize azd::QRuler::minimumSizeHint() const
{
    return sizeHint();
}

QSize azd::QRuler::sizeHint() const
{
    return QSize(120, 100);
}

void azd::QRuler::mousePressEvent(QMouseEvent* event)
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

void azd::QRuler::mouseMoveEvent(QMouseEvent* event)
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

void azd::QRuler::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    Settings& settings = static_cast<Application*>(qApp)->settings();
    int width = this->width();
    int height = this->height();
    QString showText = tr("Width:") + QString::number(width) + tr("px") + "\n"
        + tr("Height:") + QString::number(height) + "px";

    painter.fillRect(rect(), settings.backgroundColor());

    drawXLine();
    drawYLine();

    QPainter painter2(this);
    painter2.setPen(QPen(settings.borderColor(), 1));
    painter2.drawRect(0, 0, width - 1, height - 1);
    painter2.setPen(QPen(settings.foregroundColor(), 1));
    painter2.setFont(QFont("monospace", 10));
    painter2.drawText(rect(), Qt::AlignCenter, showText);
}

void azd::QRuler::drawXLine()
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
            painter.setFont(QFont("monospace", 7, QFont::Bold));
            painter.drawText(i, 20, 25, 10, Qt::AlignLeft, QString::number(i));
        }
        painter.drawLine(QPoint(i, 0), QPoint(i, lineHeight));
    }
}

void azd::QRuler::drawYLine()
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
            painter.setFont(QFont("monospace", 7, QFont::Bold));
            painter.drawText(20, i, 25, 10, Qt::AlignLeft, QString::number(i));
        }
        painter.drawLine(QPoint(0, i), QPoint(lineHeight, i));
    }
}

void azd::QRuler::onAboutClicked()
{
    QFile f(":/about.html");
    if (!f.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << tr("Error loading about file") << '\n';
        return;
    }
    QTextStream in(&f);
    QString text = in.readAll();
    f.close();
    QMessageBox::about(this, tr("About"), text);
}
