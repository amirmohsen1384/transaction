#ifndef ABSTRACTACCOUNT_H
#define ABSTRACTACCOUNT_H

#include "include/general.h"
#include "include/entity.h"

class AbstractAccount : Entity
{
public:
    AbstractAccount();

    quint16 getCvv2() const;
    void setCvv2(quint16 cvv);
    
    quint64 getBalance() const;
    void setBalance(quint64 newBalance);

    quint64 getOwner() const;

    quint64 getCardNumber() const;
    void setCardNumber(quint64 number);

    quint64 getShabaNumber() const;
    void setShabaNumber(quint64 number);

    QDate getExpirationDate() const;
    void setExpirationDate(const QDate &date);

    int getPrimaryPassword() const;
    void setPrimaryPassword(int password);

    int getSecondaryPassword() const;
    void setSecondaryPassword(int password);

    QDateTime getLastCashMoved() const;
    void setLastCashMoved(const QDateTime &dateTime);

    friend QDataStream& operator>>(QDataStream &stream, AbstractAccount &data);
    friend QDataStream& operator<<(QDataStream &stream, const AbstractAccount &data);

public:
    virtual float profit() const = 0;

protected:
    int secondaryPassword = 0;
    QDateTime lastCashMoved;
    int primaryPassword = 0;
    quint64 cardNumber = 0;
    quint64 shabaNumber = 0;
    QDate expirationDate;
    quint64 balance = 0;
    quint16 cvv2 = 0;
    quint64 owner = 0;
};

QDataStream& operator>>(QDataStream &stream, AbstractAccount &data);
QDataStream& operator<<(QDataStream &stream, const AbstractAccount &data);

#endif // ABSTRACTACCOUNT_H
