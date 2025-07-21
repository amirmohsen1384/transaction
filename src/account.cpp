#include "include/account.h"

std::shared_ptr<AbstractAccount> loadFromKey(const Key &key)
{
    switch(Identifier::accountMode(key))
    {
    case Account::Loan:
    {
        auto account = std::make_shared<LoanAccount>();
        if(Storage::loanAccount().exists(LoanAccount::getFilename(key)))
        {
            *account = LoanAccount::loadFromRecord(key);
            qDebug() << "Successful to load loan account";
            return account;
        }
        else
        {
            qDebug() << "The given key which was a loan account is not available.";
        }
    }
    case Account::Deposit:
    {
        auto account = std::make_shared<DepositAccount>();
        if(Storage::depositAccount().exists(DepositAccount::getFilename(key)))
        {
            *account = DepositAccount::loadFromRecord(key);
            qDebug() << "Successful to load deposit account";
            return account;
        }
        else
        {
            qDebug() << "The given key which was a deposit account is not available.";
        }
    }
    case Account::Transaction:
    {
        auto account = std::make_shared<TransactionAccount>();
        if(Storage::transactionAccount().exists(TransactionAccount::getFilename(key)))
        {
            *account = TransactionAccount::loadFromRecord(key);
            qDebug() << "Successful to load transaction account";
            return account;
        }
        else
        {
            qDebug() << "The given key which was a transaction account is not available.";
        }
    }
    }
    qDebug() << QString("Failed to load account with %1. It was corrupt nor invalid").arg(key);
    return nullptr;
}
