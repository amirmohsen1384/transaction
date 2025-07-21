#include "include/general.h"
#include <QApplication>

QDir Storage::root()
{
    const auto &fileName = QApplication::applicationName();
    auto folder = QDir::temp();
    folder.mkpath(fileName);
    folder.cd(fileName);
    return folder;
}

QDir Storage::admin()
{
    const auto fileName = "Admins";
    auto folder = Storage::root();
    folder.mkpath(fileName);
    folder.cd(fileName);
    return folder;
}

QDir Storage::customer()
{
    const auto fileName = "Customers";
    auto folder = Storage::root();
    folder.mkpath(fileName);
    folder.cd(fileName);
    return folder;
}

QDir Storage::loanAccount()
{
    const auto fileName = "Loans";
    auto folder = Storage::root();
    folder.mkpath(fileName);
    folder.cd(fileName);
    return folder;
}

QDir Storage::depositAccount()
{
    const auto fileName = "Deposits";
    auto folder = Storage::root();
    folder.mkpath(fileName);
    folder.cd(fileName);
    return folder;
}

QDir Storage::transactionAccount()
{
    const auto fileName = "Transactions";
    auto folder = Storage::root();
    folder.mkpath(fileName);
    folder.cd(fileName);
    return folder;
}

bool Identifier::isValid(quint64 value)
{
    return (value > 0);
}

bool Identifier::isValid(quint64 value, const Account &account)
{
    if(!Identifier::isValid(value))
    {
        return false;
    }
    switch(account)
    {
    case Account::Loan:
    {
        return std::fmod(value, std::pow(10, VALID_DIGITS)) == LOAN_ID;
    }
    case Account::Deposit:
    {
        return std::fmod(value, std::pow(10, VALID_DIGITS)) == DEPOSIT_ID;
    }
    case Account::Transaction:
    {
        return std::fmod(value, std::pow(10, VALID_DIGITS)) == TRANSACTION_ID;
    }
    default:
    {
        return false;
    }
    }
}

QDir Storage::customerFolder(quint64 value)
{
    const auto name = QString::number(value);
    auto dir = Storage::customer();
    if(dir.mkpath(name))
    {
        dir.cd(name);
    }
    else
    {
        qDebug() << "Failed to create customer folder.";
    }
    return dir;
}

Account Identifier::accountMode(const Key &value)
{
    if(Identifier::isValid(value, Account::Deposit))
    {
        qDebug() << QString("%1 is a deposit account").arg(value);
        return Account::Deposit;
    }
    else if(Identifier::isValid(value, Account::Loan))
    {
        qDebug() << QString("%1 is a loan account.").arg(value);
        return Account::Loan;
    }
    else if(Identifier::isValid(value, Account::Transaction))
    {
        qDebug() << QString("%1 is a transaction account").arg(value);
        return Account::Transaction;
    }
    else
    {
        qDebug() << QString("No account related to %1 found.").arg(value);
        return Account::None;
    }
}
