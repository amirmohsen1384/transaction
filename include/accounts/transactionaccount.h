#ifndef TRANSACTIONACCOUNT_H
#define TRANSACTIONACCOUNT_H

#include "abstractaccount.h"

class TransactionAccount : public AbstractAccount
{
public:
    TransactionAccount();

public:
    static QString getFilename(quint64 value);
    static TransactionAccount loadFromRecord(quint64 value);

    virtual float profit() const override;
    virtual void saveToRecord(quint64 value) const override;
};

#endif // TRANSACTIONACCOUNT_H
