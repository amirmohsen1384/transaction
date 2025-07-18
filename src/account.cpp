#include "include/account.h"

std::shared_ptr<AbstractAccount> loadFromKey(const Key &key)
{
    switch(Identifier::accountMode(key))
    {
    case Account::Loan:
    {
        auto account = std::make_shared<LoanAccount>();
        *account = LoanAccount::loadFromRecord(key);
        return account;
    }
    case Account::Deposit:
    {
        auto account = std::make_shared<DepositAccount>();
        *account = DepositAccount::loadFromRecord(key);
        return account;
    }
    case Account::Transaction:
    {
        auto account = std::make_shared<TransactionAccount>();
        *account = TransactionAccount::loadFromRecord(key);
        return account;
    }
    default:
    {
        return {};
    }
    }
}
