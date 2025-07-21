#include "include/widgets/accountview.h"
#include "include/account.h"
#include "ui_accountview.h"

AccountView::AccountView(QWidget *parent) : QDialog(parent), ui(new Ui::AccountView)
{
    ui->setupUi(this);
    ui->primaryPasswordView->setReadOnly(true);
    ui->secondaryPasswordView->setReadOnly(true);
    connect(this, &AccountView::keyChanged, this, &AccountView::loadAccount);
}

AccountView::~AccountView()
{
    delete ui;
}

Key AccountView::getKey() const
{
    return value;
}

void AccountView::setKey(const Key &value)
{
    this->value = value;
    emit keyChanged(value);
}

void AccountView::loadAccount(const Key &value)
{
    auto account = loadFromKey(value);
    if(account == nullptr)
    {
        qDebug() << QString("Failed to load %1. It was null").arg(value);
        return;
    }
    switch(Identifier::accountMode(value))
    {
    case Account::Deposit:
    {
        ui->accountTypeLabel->setText("Deposit Account");
        ui->accountTypeIcon->setPixmap(QPixmap(":/images/accounts/deposit-account.png"));
        break;
    }
    case Account::Loan:
    {
        ui->accountTypeLabel->setText("Loan Account");
        ui->accountTypeIcon->setPixmap(QPixmap(":/images/accounts/loan-account.png"));
        break;
    }
    case Account::Transaction:
    {
        ui->accountTypeLabel->setText("Transaction Account");
        ui->accountTypeIcon->setPixmap(QPixmap(":/images/accounts/transaction-account.png"));
        break;
    }
    default:
    {
        ui->accountTypeLabel->setText("Unknown Account");
        ui->accountTypeIcon->setPixmap(QPixmap());
        break;
    }
    }
    ui->cardNumberLabel->setText(account->getCardNumber());
    ui->primaryPasswordView->setPassword(QString::number(account->getPrimaryPassword()));
    ui->secondaryPasswordView->setPassword(QString::number(account->getSecondaryPassword()));
    ui->cvv2Label->setText(QString::number(account->getCvv2()));
    ui->balanceView->setText(QString::number(account->getBalance(), 'f', 2));
    ui->expirationDateLabel->setText(account->getExpirationDate().toString(Qt::ISODate));
    ui->dailyTransferredView->setText(QString::number(account->getTransferredBalance(), 'f', 2));
    ui->shabaNumberLabel->setText(account->getShabaNumber());
    ui->lastTransactionView->setText(account->getLastCashMoved().toString(Qt::ISODate));
    ui->shabaNumberLabel->setText(account->getShabaNumber());
    ui->accountNumberLabel->setText(QString::number(value));
    
}

AccountView::AccountView(const Key &number, QWidget *parent) : AccountView(parent)
{
    setKey(number);
}
