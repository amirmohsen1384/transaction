#include "include/accounts/abstractaccount.h"

AbstractAccount::AbstractAccount() : Entity()
{}

double AbstractAccount::getBalance() const
{
    return balance;
}

void AbstractAccount::setBalance(double newBalance)
{
    balance = newBalance;
}

QDate AbstractAccount::getExpirationDate() const
{
    return expirationDate;
}

void AbstractAccount::setExpirationDate(const QDate &date)
{
    expirationDate = date;
}

QString AbstractAccount::getCardNumber() const
{
    return cardNumber;
}

void AbstractAccount::setCardNumber(const QString &number)
{
    cardNumber = number;
}

QString AbstractAccount::getShabaNumber() const
{
    return shabaNumber;
}

void AbstractAccount::setShabaNumber(const QString &number)
{
    shabaNumber = number;
}

quint16 AbstractAccount::getCvv2() const
{
    return cvv2;
}

void AbstractAccount::setCvv2(quint16 cvv)
{
    cvv2 = cvv;
}

QDateTime AbstractAccount::getLastCashMoved() const
{
    return lastCashMoved;
}

void AbstractAccount::setLastCashMoved(const QDateTime &dateTime)
{
    lastCashMoved = dateTime;
}

Key AbstractAccount::getOwner() const
{
    return owner;
}

int AbstractAccount::getSecondaryPassword() const
{
    return secondaryPassword;
}

void AbstractAccount::setSecondaryPassword(int password)
{
    secondaryPassword = password;
}

double AbstractAccount::getTransferredBalance() const
{
    return transferredBalance;
}

void AbstractAccount::setTransferredBalance(double value)
{
    transferredBalance = value;
}

int AbstractAccount::getPrimaryPassword() const
{
    return primaryPassword;
}

void AbstractAccount::setPrimaryPassword(int password)
{
    primaryPassword = password;
}

QDataStream& operator<<(QDataStream &stream, const AbstractAccount &data)
{
    stream << data.cardNumber << data.shabaNumber;
    stream << data.balance << data.cvv2 << data.owner;
    stream << data.expirationDate << data.lastCashMoved;
    stream << data.primaryPassword << data.secondaryPassword;
    stream << data.transferredBalance;
    return stream;
}

QDataStream& operator>>(QDataStream &stream, AbstractAccount &data)
{
    stream >> data.cardNumber >> data.shabaNumber;
    stream >> data.balance >> data.cvv2 >> data.owner;
    stream >> data.expirationDate >> data.lastCashMoved;
    stream >> data.primaryPassword >> data.secondaryPassword;
    stream >> data.transferredBalance;
    return stream;
}
