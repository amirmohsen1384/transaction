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
private:
    void updateModel();

public:
    explicit TransferPanel(QWidget *parent = nullptr);
    ~TransferPanel();

    CustomerModel* model();

public slots:
    void saveResult();
    QString browseImage();
    virtual void accept() override;
    void updateOwner(const QString &value);
    virtual void setModel(CustomerModel *model);

private:
    CashTransaction transaction;
    QIntValidator cvv2Validator;
    QIntValidator targetValidator;
    AccountDelegate sourceDelegate;
    QIntValidator passwordValidator;
    QDoubleValidator amountValidator;
    CustomerModel *sourceModel = nullptr;
    std::unique_ptr<Ui::TransferPanel> ui;
};

#endif // TRANSFERPANEL_H
