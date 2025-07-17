#ifndef GENERAL_H
#define GENERAL_H

#include <QDir>
#include <QtGlobal>

constexpr auto LOAN_ID = 108;
constexpr auto DEPOSIT_ID = 147;
constexpr auto TRANSACTION_ID = 234;

enum class Account {Deposit = 0, Loan, Transaction};

namespace Storage
{
    QDir root();
    QDir admin();
    QDir customer();
    QDir loanAccount();
    QDir depositAccount();
    QDir transactionAccount();
}

namespace Identifier
{
    bool isValid(quint64 value);
    bool isValid(quint64 value, const Account &account);
}

#endif // GENERAL_H
