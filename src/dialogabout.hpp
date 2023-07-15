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

#include <QDialog>

namespace QRuler {
namespace Ui {
class DialogAbout;
}
class DialogAbout : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAbout(QWidget *parent = nullptr);
    ~DialogAbout();

    void setInfoText(const QString &);
    void setAuthorsText(const QString &);
    void setLicenseText(const QString &);

private:
    Ui::DialogAbout *ui;
};
} // namespace QRuler
