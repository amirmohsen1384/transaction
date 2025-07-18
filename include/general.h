#ifndef GENERAL_H
#define GENERAL_H

#include <QDir>
#include <QtGlobal>

constexpr auto LOAN_ID = 108;
constexpr auto DEPOSIT_ID = 147;
constexpr auto TRANSACTION_ID = 234;

constexpr auto VALID_DIGITS = 3;
constexpr auto GENERAL_DIGITS = 4;

constexpr auto INVALID_ID = -1;

enum class Account {None = 0, Deposit, Loan, Transaction};

using Key = quint64;
using KeyList = QList<Key>;

namespace Storage
{
    QDir root();
    QDir admin();
    QDir customer();
    QDir loanAccount();
    QDir depositAccount();
    QDir transactionAccount();
    QDir customerFolder(quint64 value);
}

namespace Identifier
{
    quint64 createAdminID();
    quint64 createCustomerID();
    bool isValid(quint64 value);
    quint64 createAccountID(const Account &account);
    bool isValid(quint64 value, const Account &account);
}

#endif // GENERAL_H
