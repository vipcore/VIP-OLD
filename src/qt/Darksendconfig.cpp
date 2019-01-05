#include "Darksendconfig.h"
#include "ui_Darksendconfig.h"

#include "bitcoinunits.h"
#include "guiconstants.h"
#include "init.h"
#include "optionsmodel.h"
#include "walletmodel.h"

#include <QKeyEvent>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>

DarksendConfig::DarksendConfig(QWidget* parent) : QDialog(parent),
                                                        ui(new Ui::DarksendConfig),
                                                        model(0)
{
    ui->setupUi(this);

    connect(ui->buttonBasic, SIGNAL(clicked()), this, SLOT(clickBasic()));
    connect(ui->buttonHigh, SIGNAL(clicked()), this, SLOT(clickHigh()));
    connect(ui->buttonMax, SIGNAL(clicked()), this, SLOT(clickMax()));
}

DarksendConfig::~DarksendConfig()
{
    delete ui;
}

void DarksendConfig::setModel(WalletModel* model)
{
    this->model = model;
}

void DarksendConfig::clickBasic()
{
    configure(true, 1000, 2);

    QString strAmount(BitcoinUnits::formatWithUnit(
        model->getOptionsModel()->getDisplayUnit(), 1000 * COIN));
    QMessageBox::information(this, tr("Darksend Configuration"),
        tr(
            "Darksend was successfully set to basic (%1 and 2 rounds). You can change this at any time by opening Vip's configuration screen.")
            .arg(strAmount));

    close();
}

void DarksendConfig::clickHigh()
{
    configure(true, 1000, 8);

    QString strAmount(BitcoinUnits::formatWithUnit(
        model->getOptionsModel()->getDisplayUnit(), 1000 * COIN));
    QMessageBox::information(this, tr("Darksend Configuration"),
        tr(
            "Darksend was successfully set to high (%1 and 8 rounds). You can change this at any time by opening Vip's configuration screen.")
            .arg(strAmount));

    close();
}

void DarksendConfig::clickMax()
{
    configure(true, 1000, 16);

    QString strAmount(BitcoinUnits::formatWithUnit(
        model->getOptionsModel()->getDisplayUnit(), 1000 * COIN));
    QMessageBox::information(this, tr("Darksend Configuration"),
        tr(
            "Darksend was successfully set to maximum (%1 and 16 rounds). You can change this at any time by opening Vip's configuration screen.")
            .arg(strAmount));

    close();
}

void DarksendConfig::configure(bool enabled, int coins, int rounds)
{
    QSettings settings;

    settings.setValue("nDarksendRounds", rounds);
    settings.setValue("nAnonymizeVipAmount", coins);

    nDarksendRounds = rounds;
    nAnonymizeVipAmount = coins;
}