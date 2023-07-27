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
#include "qtilities.hpp"

#include <QApplication>
#include <QSettings>

Qtilities::Settings::Settings()
    : alwaysOnTop_(Default::alwaysOnTop)
    , opacity_(Default::opacity)
    , bgColor_(Default::backgroundColor)
    , bdColor_(Default::borderColor)
    , fgColor_(Default::foregroundColor)
    , position_(Default::position)
    , size_(Default::size)
{
}

void Qtilities::Settings::load()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(),
                       QApplication::applicationDisplayName());

    settings.beginGroup("General");
    alwaysOnTop_ = settings.value(QSL("AlwaysOnTop"), Default::alwaysOnTop).toBool();
    bgColor_ = settings.value(QSL("BackgroundColor"), Default::backgroundColor).value<QColor>();
    bdColor_ = settings.value(QSL("BorderColor"), Default::borderColor).value<QColor>();
    fgColor_ = settings.value(QSL("ForegroundColor"), Default::foregroundColor).value<QColor>();
    opacity_ = settings.value(QSL("Opacity"), Default::opacity).toString();
    position_ = settings.value(QSL("Position"), Default::position).toPoint();
    size_ = settings.value(QSL("Size"), Default::size).toSize().expandedTo(Default::minimumSize);
    settings.endGroup();
}

void Qtilities::Settings::save()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(),
                       QApplication::applicationDisplayName());

    settings.beginGroup("General");
    settings.setValue(QSL("AlwaysOnTop"), alwaysOnTop_);
    settings.setValue(QSL("BackgroundColor"), bgColor_);
    settings.setValue(QSL("BorderColor"), bdColor_);
    settings.setValue(QSL("ForegroundColor"), fgColor_);
    settings.setValue(QSL("Opacity"), opacity_);
    settings.setValue(QSL("Position"), position_);
    settings.setValue(QSL("Size"), size_);
    settings.endGroup();
}
