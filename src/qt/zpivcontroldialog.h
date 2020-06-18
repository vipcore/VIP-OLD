// Copyright (c) 2017-2018 The PIVX developers
// Copyright (c) 2018 The VIP developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZVIPCONTROLDIALOG_H
#define ZVIPCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "primitives/zerocoin.h"
#include "privacydialog.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZVipControlDialog;
}

class ZVipControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZVipControlDialog(QWidget *parent);
    ~ZVipControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZVipControlDialog *ui;
    WalletModel* model;
    PrivacyDialog* privacyDialog;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };

private slots:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZVIPCONTROLDIALOG_H
