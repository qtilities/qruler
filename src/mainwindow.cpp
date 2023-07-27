/*
    QRuler - Simple on-screen pixel meter.
    Copyright (C) 2013 Awesomez-Qt (as IRuler)
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
#include "mainwindow.hpp"
#include "application.hpp"
#include "dialogabout.hpp"
#include "settings.hpp"

#include <QFont>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>

Qtilities::MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setMouseTracking(true);
    loadSettings();
}

void Qtilities::MainWindow::loadSettings()
{
    Settings &settings = static_cast<Application *>(qApp)->settings();
    qreal opacity = settings.opacity().toDouble();
    Qt::WindowFlags flags = Qt::FramelessWindowHint;

    setAttribute(Qt::WA_TranslucentBackground);
    setWindowOpacity(opacity);

    if (settings.alwaysOnTop())
        flags |= Qt::WindowStaysOnTopHint;

    setWindowFlags(flags);
    show(); // update the flags
}

void Qtilities::MainWindow::saveSettings()
{
    Settings &settings = static_cast<Application *>(qApp)->settings();
    settings.setPosition(pos());
    settings.setSize(size());
}

QSize Qtilities::MainWindow::minimumSizeHint() const { return sizeHint(); }

QSize Qtilities::MainWindow::sizeHint() const { return Default::minimumSize; }

void Qtilities::MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        changeWidth = event->x() > this->width() - 5;
        changeHeight = event->y() > this->height() - 5;
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    } else if (event->button() == Qt::RightButton) {
        Application *theApp = static_cast<Application *>(qApp);
        theApp->showContextMenu(this->cursor().pos());
    }
}

void Qtilities::MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->x() > (this->width() - 5))
        this->setCursor(Qt::SizeHorCursor);
    else if (event->y() > (this->height() - 5))
        this->setCursor(Qt::SizeVerCursor);
    else
        this->setCursor(Qt::ArrowCursor);

    if (event->buttons() == Qt::LeftButton) {
        if ((changeWidth && !changeHeight)) {
            int x = event->pos().x();
            if (x > 30)
                this->setFixedWidth(x);
        } else if (!changeWidth && changeHeight) {
            int y = event->pos().y();
            if (y > 30)
                this->setFixedHeight(y);
        } else {
            move(event->globalPos() - dragPosition);
            event->accept();
        }
    }
}

void Qtilities::MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    Settings &settings = static_cast<Application *>(qApp)->settings();
    int width = this->width();
    int height = this->height();
    QString showText = tr("Width:") + QString::number(width) + tr("px") + "\n" + tr("Height:")
                       + QString::number(height) + tr("px");

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

void Qtilities::MainWindow::drawXLine()
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
            painter.setFont(QFont(Default::fontFamily, Default::fontSize, QFont::Bold));
            painter.drawText(i, 20, 25, 10, Qt::AlignLeft, QString::number(i));
        }
        painter.drawLine(QPoint(i, 0), QPoint(i, lineHeight));
    }
}

void Qtilities::MainWindow::drawYLine()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(QPen(Qt::black, 1));

    int lineHeight = 5;
    for (int i = 0; i < this->height(); i += 2) {
        lineHeight = 5;

        if (i % 10 == 0)
            lineHeight = 10;

        if (i % 50 == 0 && i > 0) {
            lineHeight = 15;
            painter.setFont(QFont(Default::fontFamily, Default::fontSize, QFont::Bold));
            painter.drawText(20, i, 25, 10, Qt::AlignLeft, QString::number(i));
        }
        painter.drawLine(QPoint(0, i), QPoint(lineHeight, i));
    }
}
