#include "include/accounts/abstractaccount.h"

AbstractAccount::AbstractAccount() : Entity()
{}

quint64 AbstractAccount::getBalance() const
{
    return balance;
}

void AbstractAccount::setBalance(quint64 newBalance)
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

quint64 AbstractAccount::getCardNumber() const
{
    return cardNumber;
}

void AbstractAccount::setCardNumber(quint64 number)
{
    cardNumber = number;
}

quint64 AbstractAccount::getShabaNumber() const
{
    return shabaNumber;
}

void AbstractAccount::setShabaNumber(quint64 number)
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

quint64 AbstractAccount::getOwner() const
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
    return stream;
}

QDataStream& operator>>(QDataStream &stream, AbstractAccount &data)
{
    stream >> data.cardNumber >> data.shabaNumber;
    stream >> data.balance >> data.cvv2 >> data.owner;
    stream >> data.expirationDate >> data.lastCashMoved;
    stream >> data.primaryPassword >> data.secondaryPassword;
    return stream;
}
