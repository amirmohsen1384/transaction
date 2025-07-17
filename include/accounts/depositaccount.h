#ifndef DEPOSITACCOUNT_H
#define DEPOSITACCOUNT_H

#include "abstractaccount.h"

class DepositAccount : public AbstractAccount
{
public:
    DepositAccount();

public:
    static DepositAccount loadFromRecord(quint64 value);

    virtual float profit() const override;
    virtual void saveToRecord(quint64 value) const override;
};

#endif // DEPOSITACCOUNT_H
