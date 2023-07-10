/*
    QRuler - Simple on-screen pixel meter.
    Copyright (C) 2021 Andrea Zanellato <redtid3@gmail.com>

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

class QLabel;

namespace QRuler {
namespace Ui {
class DialogPrefs;
}
class DialogPrefs : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPrefs(QWidget *parent = nullptr);
    ~DialogPrefs();

    void loadSettings();

private:
    void accept() override;

    void setColorForLabel(QLabel *label);

    Ui::DialogPrefs *ui;
};
} // namespace QRuler
