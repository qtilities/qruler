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
    ui->txtInfo->setMarkdown(text);
}

void QRuler::DialogAbout::setAuthorsText(const QString &text)
{
    ui->txtAuthors->setMarkdown(text);
}

void QRuler::DialogAbout::setLicenseText(const QString &text)
{
    ui->txtLicense->setMarkdown(text);
}
