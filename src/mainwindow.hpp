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
#pragma once

#include <QDialog>

namespace Qtilities {

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

    void loadSettings();
    void saveSettings();

private:
    void mouseDoubleClickEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void drawTickMarks(Qt::Orientation);

    bool isChangedWidth_;
    bool IsChangedHeight_;
    QPoint dragPosition_;
    qreal scaleFactor_;
};
} // namespace Qtilities
