#ifndef TRANSFERPANEL_H
#define TRANSFERPANEL_H

#include <QDialog>
#include <QIntValidator>
#include <QDoubleValidator>
#include "include/core/cashtransaction.h"
#include "include/models/customermodel.h"
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
    void saveResult();
    QString browseImage();
    virtual void accept() override;
    void updateOwner(const QString &value);

private:
    CustomerModel sourceModel;
    CashTransaction transaction;
    QIntValidator cvv2Validator;
    QIntValidator targetValidator;
    AccountDelegate sourceDelegate;
    QIntValidator passwordValidator;
    QDoubleValidator amountValidator;
    std::unique_ptr<Ui::TransferPanel> ui;
};

#endif // TRANSFERPANEL_H
