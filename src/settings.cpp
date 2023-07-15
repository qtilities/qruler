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
#include "settings.hpp"

#include <QApplication>
#include <QSettings>

namespace Default {
static const bool alwaysOnTop = true;
static const QString opacity = QStringLiteral("0.5");
static const QColor backgroundColor = QColor(0x92, 0xd7, 0xff);
static const QColor borderColor = QColor(0xdd, 0xdd, 0xdd);
static const QColor foregroundColor = QColor(0x94, 0x00, 0x80);
static const QPoint position = QPoint(200, 200);
static const QSize size = QSize(240, 120);
} // namespace Default

QRuler::Settings::Settings()
    : alwaysOnTop_(Default::alwaysOnTop)
    , opacity_(Default::opacity)
    , bgColor_(Default::backgroundColor)
    , bdColor_(Default::borderColor)
    , fgColor_(Default::foregroundColor)
    , position_(Default::position)
    , size_(Default::size)
{
}

void QRuler::Settings::load()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QApplication::organizationName(),
                       QApplication::applicationDisplayName());

    settings.beginGroup("Options");
    alwaysOnTop_
        = settings.value(QStringLiteral("AlwaysOnTop"), Default::alwaysOnTop)
              .toBool();
    bgColor_ = settings
                   .value(QStringLiteral("BackgroundColor"),
                          Default::backgroundColor)
                   .value<QColor>();
    bdColor_
        = settings.value(QStringLiteral("BorderColor"), Default::borderColor)
              .value<QColor>();
    fgColor_ = settings
                   .value(QStringLiteral("ForegroundColor"),
                          Default::foregroundColor)
                   .value<QColor>();
    opacity_ = settings.value(QStringLiteral("Opacity"), Default::opacity)
                   .toString();
    position_ = settings.value(QStringLiteral("Position"), Default::position)
                    .toPoint();
    size_ = settings.value(QStringLiteral("Size"), Default::size).toSize();
    settings.endGroup();
}

void QRuler::Settings::save()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QApplication::organizationName(),
                       QApplication::applicationDisplayName());

    settings.beginGroup("Options");
    settings.setValue(QStringLiteral("AlwaysOnTop"), alwaysOnTop_);
    settings.setValue(QStringLiteral("BackgroundColor"), bgColor_);
    settings.setValue(QStringLiteral("BorderColor"), bdColor_);
    settings.setValue(QStringLiteral("ForegroundColor"), fgColor_);
    settings.setValue(QStringLiteral("Opacity"), opacity_);
    settings.setValue(QStringLiteral("Position"), position_);
    settings.setValue(QStringLiteral("Size"), size_);
    settings.endGroup();
}
