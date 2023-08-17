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
#include <QScreen>
#include <QSizeGrip>
#include <QVBoxLayout>

namespace Private {
static constexpr int lineWidthSmall{5};
static constexpr int lineWidthMedium{10};
static constexpr int lineWidthLarge{15};
} // namespace Private

Qtilities::MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QDialog(parent, flags)
    , scaleFactor_(QGuiApplication::screenAt(QCursor::pos())->devicePixelRatio())
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NativeWindow);
    setMouseTracking(true);
    setSizeGripEnabled(true);
    setWindowTitle(QGuiApplication::applicationDisplayName());
    loadSettings();
}

void Qtilities::MainWindow::loadSettings()
{
    Settings &settings = static_cast<Application *>(qApp)->settings();
    Qt::WindowFlags flags = Qt::FramelessWindowHint;
    if (settings.alwaysOnTop())
        flags |= Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint;

    setWindowOpacity(settings.opacity());
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

void Qtilities::MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    isFullScreen() ? showNormal() : showFullScreen();
    event->accept();
    QDialog::mouseDoubleClickEvent(event);
}

void Qtilities::MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
#if QT_VERSION < 0x060000
        isChangedWidth_ = event->x() > width() - 5;
        IsChangedHeight_ = event->y() > height() - 5;
        dragPosition_ = event->globalPos() - frameGeometry().topLeft();
#else
        isChangedWidth_ = (event->position().x() > width() - 5);
        IsChangedHeight_ = (event->position().y() > height() - 5);
        dragPosition_ = event->globalPosition().toPoint() - frameGeometry().topLeft();
#endif
        event->accept();
    } else if (event->button() == Qt::RightButton) {
        Application *theApp = static_cast<Application *>(qApp);
        theApp->showContextMenu(cursor().pos());
    }
}

void Qtilities::MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isFullScreen())
        return;

#if QT_VERSION < 0x060000
    int px = event->x();
    int py = event->y();
    QPoint globalPos = event->globalPos();
#else
    qreal px = event->position().x();
    qreal py = event->position().y();
    QPoint globalPos = event->globalPosition().toPoint();
#endif
    bool isDraggingHorizontally = (px > (width() - 5));
    bool isDraggingVertically = (py > (height() - 5));

    if (isDraggingHorizontally)
        setCursor(Qt::SizeHorCursor);
    else if (isDraggingVertically)
        setCursor(Qt::SizeVerCursor);
    else
        setCursor(Qt::ClosedHandCursor);

    if (event->buttons() == Qt::LeftButton) {
        if ((isChangedWidth_ && !IsChangedHeight_)) {
            int x = event->pos().x();
            if (x > 30)
                resize(x, height());
        } else if (!isChangedWidth_ && IsChangedHeight_) {
            int y = event->pos().y();
            if (y > 30)
                resize(width(), y);
        } else {
            move(globalPos - dragPosition_);
        }
        update();
    }
    QDialog::mouseMoveEvent(event);
}

void Qtilities::MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    Settings &settings = static_cast<Application *>(qApp)->settings();

    painter.fillRect(rect(), settings.backgroundColor());
    painter.setPen(QPen(settings.borderColor(), 1));
    painter.drawRect(rect());

    drawTickMarks(Qt::Horizontal);
    drawTickMarks(Qt::Vertical);

    int x = pos().x() * scaleFactor_;
    int y = pos().y() * scaleFactor_;
    int w = width() * scaleFactor_;
    int h = height() * scaleFactor_;
    QString text = tr("Position:") + QString::number(x) + "," + QString::number(y) + "\n" + tr("Width:")
                   + QString::number(w) + tr("px") + "\n" + tr("Height:") + QString::number(h)
                   + tr("px");

    QPainter painter2(this);
    painter2.setPen(QPen(settings.foregroundColor(), 1));
    painter2.setFont(QFont(Default::fontFamily, Default::measureFontSize));
    painter2.drawText(rect(), Qt::AlignCenter, text);
}

void Qtilities::MainWindow::drawTickMarks(Qt::Orientation orientation)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);
    QPen pen(Qt::black);
    qreal penW = 1 / scaleFactor_;
    pen.setWidthF(penW);
    painter.setPen(pen);

    QPointF p1, p2;
    int w = (orientation == Qt::Horizontal) ? width() * scaleFactor_ : height() * scaleFactor_;
    int lineWidth = Private::lineWidthSmall;

    for (int i = 0; i < w; i += 2) {
        qreal coord = i / scaleFactor_;
        lineWidth = Private::lineWidthSmall;

        if (i % 10 == 0)
            lineWidth = Private::lineWidthMedium;

        if (i % 20 == 0)
            lineWidth = Private::lineWidthLarge;

        if (i % 100 == 0 && i > 0) {
            QRectF valTextRect = (orientation == Qt::Horizontal) ? QRectF(coord, 20, 25, 10)
                                                                 : QRectF(20, coord, 25, 10);
            painter.setFont(QFont(Default::fontFamily, Default::fontSize, QFont::Bold));
            painter.drawText(valTextRect, Qt::AlignLeft, QString::number(i));
        }
        if (orientation == Qt::Horizontal) {
            p1 = QPointF(coord, 0);
            p2 = QPointF(coord, lineWidth);
        } else {
            p1 = QPointF(0, coord);
            p2 = QPointF(lineWidth, coord);
        }
        painter.drawLine(QLineF(p1, p2));
    }
}
