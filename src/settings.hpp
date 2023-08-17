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
static constexpr qreal opacity{0.5};
static constexpr QColor backgroundColor{QColor(0x92, 0xd7, 0xff, opacity)};
static constexpr QColor borderColor{QColor(0xdd, 0xdd, 0xdd, opacity)};
static constexpr QColor foregroundColor{QColor(0x94, 0x00, 0x80, opacity)};
static constexpr QPoint position{QPoint(200, 200)};
static constexpr QSize size{QSize(240, 120)};
static constexpr QSize minimumSize{QSize(120, 100)};
static constexpr int fontSize{7};
static constexpr int measureFontSize{10};
static const QString fontFamily = QStringLiteral("monospace");
} // namespace Default

class Settings
{
public:
    Settings();

    void load();
    void save();

    constexpr QColor backgroundColor() const noexcept { return bgColor_; }
    void setBackgroundColor(const QColor &bgColor) noexcept
    {
        bgColor_ = bgColor;
        bgColor_.setAlphaF(opacity_);
    }

    constexpr QColor borderColor() const noexcept { return bdColor_; }
    void setBorderColor(const QColor &bdColor) noexcept
    {
        bdColor_ = bdColor;
        bdColor_.setAlphaF(opacity_);
    }

    constexpr QColor foregroundColor() const noexcept { return fgColor_; }
    void setForegroundColor(const QColor &fgColor) noexcept
    {
        fgColor_ = fgColor;
        fgColor_.setAlphaF(opacity_);
    }

    constexpr qreal opacity() const noexcept { return opacity_; }
    void setOpacity(qreal opacity) noexcept
    {
        opacity_ = opacity;
        bgColor_.setAlphaF(opacity);
        bdColor_.setAlphaF(opacity);
        fgColor_.setAlphaF(opacity);
    }

    constexpr QPoint position() const noexcept { return position_; }
    constexpr void setPosition(const QPoint &position) noexcept { position_ = position; }

    constexpr QSize size() const noexcept { return size_; }
    constexpr void setSize(const QSize &size) noexcept { size_ = size; }

    constexpr bool alwaysOnTop() const noexcept { return alwaysOnTop_; }
    constexpr void setAlwaysOnTop(bool alwaysOnTop) noexcept { alwaysOnTop_ = alwaysOnTop; }

private:
    bool alwaysOnTop_;
    qreal opacity_;
    QColor bgColor_;
    QColor bdColor_;
    QColor fgColor_;
    QPoint position_;
    QSize size_;
};
} // namespace Qtilities
