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
#pragma once

#include <QWidget>

class QMenu;

namespace QRuler {
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void loadSettings();
    void saveSettings();

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;

private:
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void about();

    void drawXLine();
    void drawYLine();

    bool changeWidth;
    bool changeHeight;
    QPoint dragPosition;
    QMenu *mnuContext_;
};
} // namespace QRuler
