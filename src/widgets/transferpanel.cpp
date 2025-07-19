#include "include/widgets/transferpanel.h"
#include "include/users/customer.h"
#include "ui_transferpanel.h"
#include "include/account.h"
#include <QMessageBox>

TransferPanel::TransferPanel(QWidget *parent) : AbstractPanel(parent)
{
    ui = std::make_unique<Ui::TransferPanel>();
    ui->setupUi(this);
}

TransferPanel::~TransferPanel() {}

void TransferPanel::updateOwner(const QString &value)
{
    const auto key = value.toLongLong();
    auto account = loadFromKey(key);
    if(account == nullptr)
    {
        ui->ownerLabel->setStyleSheet("color:red");
        ui->ownerLabel->setText("No one found with this account number!");
    }
    else
    {
        auto user = Customer::loadFromRecord(account->getOwner());
        ui->ownerLabel->setStyleSheet("color:green");
        ui->ownerLabel->setText(QString("This account belongs to %1").arg(user.getName());

    }
}

void TransferPanel::reset()
{
    ui->destinationEdit->setText(QString());
    ui->passwordEdit->setText(QString());
    ui->amountEdit->setText(QString());
    ui->ownerLabel->setVisible(false);
    ui->cvv2Edit->setText(QString());
    transaction.reset();
}

void TransferPanel::reject()
{
    AbstractPanel::reject();
}

void TransferPanel::accept()
{
    try
    {
        transaction.setDestinationId(ui->destinationEdit->text().toLongLong());
        transaction.setSourceId(ui->sourceEdit->currentText().toLongLong());
        transaction.setPassword(ui->passwordEdit->text().toInt());
        transaction.setAmount(ui->amountEdit->text().toDouble());
        transaction.setCvv2(ui->cvv2Edit->text().toInt());
        transaction.transfer();

        QMessageBox message(this);
        message.setWindowTitle("Successful");
        message.setText("Transaction has been successful!");
        message.exec();

        AbstractPanel::accept();
    }
    catch(const std::exception &e)
    {
        QMessageBox::critical(this, "Error", e.what());
    }
}
