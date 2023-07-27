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

#include <QColor>
#include <QPoint>
#include <QSize>
#include <QString>

namespace Qtilities {

namespace Default {
static const bool alwaysOnTop{true};
static constexpr QColor backgroundColor{QColor(0x92, 0xd7, 0xff)};
static constexpr QColor borderColor{QColor(0xdd, 0xdd, 0xdd)};
static constexpr QColor foregroundColor{QColor(0x94, 0x00, 0x80)};
static constexpr QPoint position{QPoint(200, 200)};
static constexpr QSize size{QSize(240, 120)};
static constexpr QSize minimumSize{QSize(120, 100)};
static constexpr int fontSize{7};
static constexpr int measureFontSize{10};
static const QString opacity = QStringLiteral("0.5");
static const QString fontFamily = QStringLiteral("monospace");
} // namespace Default

class Settings
{
public:
    Settings();

    void load();
    void save();

    QColor backgroundColor() const { return bgColor_; }
    void setBackgroundColor(const QColor &bgColor) { bgColor_ = bgColor; }

    QColor borderColor() const { return bdColor_; }
    void setBorderColor(const QColor &bdColor) { bdColor_ = bdColor; }

    QColor foregroundColor() const { return fgColor_; }
    void setForegroundColor(const QColor &fgColor) { fgColor_ = fgColor; }

    QString opacity() const { return opacity_; }
    void setOpacity(QString opacity) { opacity_ = opacity; }

    QPoint position() const { return position_; }
    void setPosition(const QPoint &position) { position_ = position; }

    QSize size() const { return size_; }
    void setSize(const QSize &size) { size_ = size; }

    bool alwaysOnTop() const { return alwaysOnTop_; }
    void setAlwaysOnTop(bool alwaysOnTop) { alwaysOnTop_ = alwaysOnTop; }

private:
    bool alwaysOnTop_;
    QString opacity_;
    QColor bgColor_;
    QColor bdColor_;
    QColor fgColor_;
    QPoint position_;
    QSize size_;
};
} // namespace Qtilities
