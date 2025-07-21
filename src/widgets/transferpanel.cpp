#include "include/widgets/transferpanel.h"
#include "include/users/customer.h"
#include "ui_transferpanel.h"
#include "include/account.h"
#include <QMessageBox>

TransferPanel::TransferPanel(const Key &sourceOwner, QWidget *parent) : QDialog(parent)
{
    ui = std::make_unique<Ui::TransferPanel>();
    ui->setupUi(this);

    amountValidator.setBottom(0.00);
    amountValidator.setTop(transaction.maximumTransaction());

    ui->ownerLabel->setVisible(false);
    ui->cvv2Edit->setValidator(&cvv2Validator);
    ui->amountEdit->setValidator(&amountValidator);
    ui->destinationEdit->setValidator(&targetValidator);

    if(!Storage::customerFolder(sourceOwner).exists())
    {
        qDebug() << "The transfer panel may lead to unexpected result with an invalid ID";
    }

    sourceModel.setIdentifier(sourceOwner);
    ui->sourceEdit->setModel(&sourceModel);
    ui->sourceEdit->setItemDelegate(&sourceDelegate);
}

TransferPanel::~TransferPanel() {}

void TransferPanel::updateOwner(const QString &value)
{
    const auto key = value.toLongLong();
    auto account = loadFromKey(key);
    if(account == nullptr)
    {
        ui->ownerLabel->setVisible(true);
        ui->ownerLabel->setStyleSheet("color:red");
        ui->ownerLabel->setText("No one found with this account number!");
    }
    else
    {
        auto user = Customer::loadFromRecord(account->getOwner());

        ui->ownerLabel->setVisible(true);
        ui->ownerLabel->setStyleSheet("color:green");
        ui->ownerLabel->setText(QString("This account belongs to %1").arg(user.getName()));
    }
}

void TransferPanel::accept()
{
    try
    {
        transaction.setDestinationId(ui->destinationEdit->text().toLongLong());
        transaction.setSourceId(ui->sourceEdit->currentText().toLongLong());
        transaction.setAmount(ui->amountEdit->text().toDouble());
        transaction.setPassword(ui->passwordEdit->text().toLong());
        transaction.setCvv2(ui->cvv2Edit->text().toInt());

        qDebug() << "Start transferring...";
        transaction.transfer();

        QMessageBox message(this);
        message.setWindowTitle("Successful");
        message.setText("Transaction has been successful!");
        message.exec();

        QDialog::accept();
    }
    catch(const std::exception &e)
    {
        QMessageBox::critical(this, "Error", e.what());
    }
}
