#include "account.h"

Account *loadFromKey(const Key &key)
{
    Account *result = nullptr;
    switch(Identifier::accountMode(key))
    {
    case Account::Loan:
    {
        auto *account = new LoanAccount;
        *account = LoanAccount::loadFromRecord(key);
        result = account;
        return result;
    }
    case Account::Deposit:
    {
        auto *account = new DepositAccount;
        *account = DepositAccount::loadFromRecord(key);
        result = account;
        return result;
    }
    case Account::Transaction:
    {
        auto *account = new TransactionAccount;
        *account = TransactionAccount::loadFromRecord(key);
        result = account;
        return result;
    }
    case Account::None:
    {
        return result;
    }
    }
}
