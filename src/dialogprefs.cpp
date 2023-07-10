/*
    QRuler - Simple on-screen pixel meter.
    Copyright (C) 2021  Andrea Zanellato <redtid3@gmail.com>

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
#include "dialogprefs.hpp"
#include "ui_dialogprefs.h"
#include "application.hpp"
#include "settings.hpp"

#include <QColorDialog>
#include <QPushButton>

QRuler::DialogPrefs::DialogPrefs(QWidget *parent)
    : QDialog(parent)
    , ui(new QRuler::Ui::DialogPrefs)
{
    ui->setupUi(this);

    ui->lblColorBg->setAutoFillBackground(true);
    ui->lblColorBd->setAutoFillBackground(true);
    ui->lblColorFg->setAutoFillBackground(true);

    loadSettings();

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this,
            &DialogPrefs::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this,
            &DialogPrefs::reject);

    connect(ui->pbnBg, &QAbstractButton::clicked, this,
            [this]() { setColorForLabel(ui->lblColorBg); });
    connect(ui->pbnBd, &QAbstractButton::clicked, this,
            [this]() { setColorForLabel(ui->lblColorBd); });
    connect(ui->pbnFg, &QAbstractButton::clicked, this,
            [this]() { setColorForLabel(ui->lblColorFg); });

    Application *theApp = static_cast<Application *>(qApp);

    setWindowIcon(theApp->icon());
    setWindowTitle(tr("Preferences"));
}

QRuler::DialogPrefs::~DialogPrefs() { delete ui; }

void QRuler::DialogPrefs::loadSettings()
{
    Settings &settings = static_cast<Application *>(qApp)->settings();

    ui->chkAlwaysOnTop->setChecked(settings.alwaysOnTop());
    ui->sbxOpacity->setValue(settings.opacity().toDouble());

    QColor bgColor = settings.backgroundColor();
    QColor bdColor = settings.borderColor();
    QColor fgColor = settings.foregroundColor();

    ui->lblColorBg->setPalette(QPalette(bgColor));
    ui->lblColorBd->setPalette(QPalette(bdColor));
    ui->lblColorFg->setPalette(QPalette(fgColor));

    ui->lblColorBg->setText(bgColor.name());
    ui->lblColorBd->setText(bdColor.name());
    ui->lblColorFg->setText(fgColor.name());
}

void QRuler::DialogPrefs::accept()
{
    Settings &settings = static_cast<Application *>(qApp)->settings();

    settings.setAlwaysOnTop(ui->chkAlwaysOnTop->isChecked());
    settings.setOpacity(QString::number(ui->sbxOpacity->value(), 'g', 2));
    settings.setBackgroundColor(
        ui->lblColorBg->palette().color(QPalette::Window));
    settings.setBorderColor(ui->lblColorBd->palette().color(QPalette::Window));
    settings.setForegroundColor(
        ui->lblColorFg->palette().color(QPalette::Window));

    QDialog::accept();

    hide();
}

void QRuler::DialogPrefs::setColorForLabel(QLabel *label)
{
    const QColor color = QColorDialog::getColor(Qt::white, this);
    if (color.isValid()) {
        label->setText(color.name());
        label->setPalette(QPalette(color));
    }
}
