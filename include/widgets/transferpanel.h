#ifndef TRANSFERPANEL_H
#define TRANSFERPANEL_H

#include <QDialog>
#include <QIntValidator>
#include <QDoubleValidator>
#include "include/core/cashtransaction.h"
#include "include/models/accountlistmodel.h"
#include "include/delegates/accountdelegate.h"

namespace Ui
{
    class TransferPanel;
}

class TransferPanel : public QDialog
{
    Q_OBJECT
public:
    explicit TransferPanel(const Key &sourceOwner, QWidget *parent = nullptr);
    ~TransferPanel();

public slots:
    virtual void accept() override;
    void updateOwner(const QString &value);

private:
    CashTransaction transaction;
    QIntValidator cvv2Validator;
    AccountListModel sourceModel;
    QIntValidator targetValidator;
    AccountDelegate sourceDelegate;
    QIntValidator passwordValidator;
    QDoubleValidator amountValidator;
    std::unique_ptr<Ui::TransferPanel> ui;
};

#endif // TRANSFERPANEL_H
