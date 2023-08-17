/*
    MIT License

    Copyright (c) 2021-2023 Andrea Zanellato <redtid3@gmail.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to
    deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
    sell copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/
#include "dialogprefs.hpp"
#include "ui_dialogprefs.h"
#include "application.hpp"
#include "litebutton.hpp"
#include "settings.hpp"

#include <QCheckBox>
#include <QColorDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QSpinBox>

#include <cstdlib>

Qtilities::DialogPrefs::DialogPrefs(QWidget *parent)
    : QDialog(parent)
    , ui(new Qtilities::Ui::DialogPrefs)
{
    ui->setupUi(this);

    loadSettings();
    setWindowIcon(QIcon::fromTheme("preferences-system", QIcon(":/preferences-system")));
    setWindowTitle(tr("Preferences"));

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DialogPrefs::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &DialogPrefs::reject);

    connect(ui->lbnBgColor, &LiteButton::clicked, this, [this]() { setButtonColor(ui->lbnBgColor); });
    connect(ui->lbnBdColor, &LiteButton::clicked, this, [this]() { setButtonColor(ui->lbnBdColor); });
    connect(ui->lbnFgColor, &LiteButton::clicked, this, [this]() { setButtonColor(ui->lbnFgColor); });
}

Qtilities::DialogPrefs::~DialogPrefs() { delete ui; }

void Qtilities::DialogPrefs::loadSettings()
{
    Settings &settings = static_cast<Application *>(qApp)->settings();
    ui->chkAlwaysOnTop->setChecked(settings.alwaysOnTop());
    ui->sbxOpacity->setValue(settings.opacity());

    QColor bgColor = settings.backgroundColor();
    QColor bdColor = settings.borderColor();
    QColor fgColor = settings.foregroundColor();

    ui->lbnBgColor->setPalette(QPalette(bgColor));
    ui->lbnBdColor->setPalette(QPalette(bdColor));
    ui->lbnFgColor->setPalette(QPalette(fgColor));

    ui->lbnBgColor->setText(bgColor.name());
    ui->lbnBdColor->setText(bdColor.name());
    ui->lbnFgColor->setText(fgColor.name());
}

void Qtilities::DialogPrefs::accept()
{
    Settings &settings = static_cast<Application *>(qApp)->settings();
    settings.setAlwaysOnTop(ui->chkAlwaysOnTop->isChecked());
    settings.setOpacity(ui->sbxOpacity->value());
    settings.setBackgroundColor(ui->lbnBgColor->palette().color(QPalette::Window));
    settings.setBorderColor(ui->lbnBdColor->palette().color(QPalette::Window));
    settings.setForegroundColor(ui->lbnFgColor->palette().color(QPalette::Window));
    QDialog::accept();
    hide();
}

void Qtilities::DialogPrefs::setButtonColor(LiteButton *button)
{
    Settings &settings = static_cast<Application *>(qApp)->settings();
    QColor initialColor = settings.backgroundColor();
    if (button == ui->lbnBdColor)
        initialColor = settings.borderColor();
    else
        initialColor = settings.foregroundColor();

    QColorDialog clrDlg(initialColor, this);
    if (clrDlg.exec() == QDialog::Rejected)
        return;

    const QColor color = clrDlg.selectedColor();
    button->setPalette(QPalette(color));
    button->setText(color.name());
}
