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

#include <QRandomGenerator>

quint64 Identifier::generateID(const Account &account)
{
    auto generator = QRandomGenerator::global();
    int number = generator->bounded(int(std::pow(10, GENERAL_DIGITS - 1)), int(std::pow(10, GENERAL_DIGITS) - 1));
    number *= std::pow(10, VALID_DIGITS);
    switch(account)
    {
    case Account::Deposit:
    {
        number += DEPOSIT_ID;
        return number;
    }
    case Account::Loan:
    {
        number += LOAN_ID;
        return number;
    }
    case Account::Transaction:
    {
        number += TRANSACTION_ID;
        return number;
    }
    default:
    {
        return INVALID_ID;
    }
    }
}
