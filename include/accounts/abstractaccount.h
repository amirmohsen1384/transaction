#ifndef ABSTRACTACCOUNT_H
#define ABSTRACTACCOUNT_H

#include "include/general.h"
#include "include/entity.h"

class AbstractAccount : Entity
{
public:
    enum Role
    {
        KeyRole = Qt::UserRole + 1
    };

    AbstractAccount();

    quint16 getCvv2() const;
    void setCvv2(quint16 cvv);
    
    double getBalance() const;
    void setBalance(double newBalance);

    Key getOwner() const;

    QString getCardNumber() const;
    void setCardNumber(const QString &number);

    QString getShabaNumber() const;
    void setShabaNumber(const QString &number);

    QDate getExpirationDate() const;
    void setExpirationDate(const QDate &date);

    int getPrimaryPassword() const;
    void setPrimaryPassword(int password);

    int getSecondaryPassword() const;
    void setSecondaryPassword(int password);

    double getTransferredBalance() const;
    void setTransferredBalance(double value);

    QDateTime getLastCashMoved() const;
    void setLastCashMoved(const QDateTime &dateTime);

    friend QDataStream& operator>>(QDataStream &stream, AbstractAccount &data);
    friend QDataStream& operator<<(QDataStream &stream, const AbstractAccount &data);

public:
    virtual float profit() const = 0;
    virtual void saveToRecord(quint64 value) const = 0;

protected:
    double transferredBalance = 0;
    int secondaryPassword = 0;
    QDateTime lastCashMoved;
    int primaryPassword = 0;
    QDate expirationDate;
    QString shabaNumber;
    QString cardNumber;
    double balance = 0;
    quint16 cvv2 = 0;
    Key owner = 0;
};

QDataStream& operator>>(QDataStream &stream, AbstractAccount &data);
QDataStream& operator<<(QDataStream &stream, const AbstractAccount &data);

#endif // ABSTRACTACCOUNT_H
