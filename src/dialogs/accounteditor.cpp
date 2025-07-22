#include "include/dialogs/accounteditor.h"
#include "ui_accounteditor.h"

AccountEditor::AccountEditor(QWidget *parent) : QDialog(parent), ui(new Ui::AccountEditor)
{
    ui = std::make_unique<Ui::AccountEditor>();
    ui->setupUi(this);
}

AccountEditor::~AccountEditor() {}

QString AccountEditor::owner() const
{
    return ui->ownerView->text();
}

double AccountEditor::balance() const
{
    return ui->balanceEdit->value();
}

Key AccountEditor::accountNumber() const
{
    return ui->accountNumberView->text().toLongLong();
}

QString AccountEditor::cardNumber() const
{
    return ui->cardNumberEdit->text();
}

QString AccountEditor::shabaNumber() const
{
    return ui->shabaNumberEdit->text();
}

int AccountEditor::cvv2() const
{
    return ui->cvv2Edit->text().toInt();
}

QDate AccountEditor::expirationDate() const
{
    return ui->expirationDateEdit->date();
}

QString AccountEditor::primaryPassword() const
{
    return ui->primaryPasswordEdit->password();
}

QString AccountEditor::secondaryPassword() const
{
    return ui->secondaryPasswordEdit->password();
}

void AccountEditor::setOwner(const QString &value)
{
    ui->ownerView->setText(value);
    emit ownerChanged(value);
}

void AccountEditor::setBalance(double value)
{
    ui->balanceEdit->setValue(value);
    emit balanceChanged(value);
}

void AccountEditor::setAccountNumber(const Key &value)
{
    ui->accountNumberView->setText(QString::number(value));
    emit accountNumberChanged(value);
}

void AccountEditor::setCardNumber(const QString &value)
{
    ui->cardNumberEdit->setText(value);
    emit cardNumberChanged(value);
}

void AccountEditor::setShabaNumber(const QString &value)
{
    ui->shabaNumberEdit->setText(value);
    emit shabaNumberChanged(value);
}

void AccountEditor::setCvv2(int value)
{
    ui->cvv2Edit->setText(QString::number(value));
    emit cvv2Changed(value);
}

void AccountEditor::setExpirationDate(const QDate &value)
{
    ui->expirationDateEdit->setDate(value);
    emit expirationDateChanged(value);
}

void AccountEditor::setPrimaryPassword(const QString &value)
{
    ui->primaryPasswordEdit->setPassword(value);
    emit primaryPasswordChanged(value);
}

void AccountEditor::setSecondaryPassword(const QString &value)
{
    ui->secondaryPasswordEdit->setPassword(value);
    emit secondaryPasswordChanged(value);
}
