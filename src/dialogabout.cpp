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
#include "dialogabout.hpp"
#include "ui_dialogabout.h"
#include "application.hpp"
#include "settings.hpp"

#include <QAbstractButton>

QRuler::DialogAbout::DialogAbout(QWidget *parent)
    : QDialog(parent)
    , ui(new QRuler::Ui::DialogAbout)
{
    ui->setupUi(this);
    ui->tabInfo->setLayout(ui->layTabInfo);
    ui->tabAuthors->setLayout(ui->layTabAuthors);
    ui->tabLicense->setLayout(ui->layTabLicense);

    // TODO: Probably needed only on X11
    Application *theApp = static_cast<Application *>(qApp);
    Settings &settings = theApp->settings();
    if (settings.alwaysOnTop()) {
        Qt::WindowFlags flags = windowFlags();
        flags |= Qt::WindowStaysOnTopHint;
        setWindowFlags(flags);
    }

    connect(ui->buttonBox, &QDialogButtonBox::clicked, this,
            &QRuler::DialogAbout::close);

    setWindowIcon(theApp->icon());
    setWindowTitle(tr("About"));
}

QRuler::DialogAbout::~DialogAbout() { delete ui; }

void QRuler::DialogAbout::setInfoText(const QString &text)
{
    QString translated = text;
    ui->txtInfo->setMarkdown(translated.replace("__AUTHOR__", tr("Author")));
}

void QRuler::DialogAbout::setAuthorsText(const QString &text)
{
    ui->txtAuthors->setMarkdown(text);
}

void QRuler::DialogAbout::setLicenseText(const QString &text)
{
    ui->txtLicense->setMarkdown(text);
}
