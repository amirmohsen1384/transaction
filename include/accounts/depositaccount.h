#ifndef DEPOSITACCOUNT_H
#define DEPOSITACCOUNT_H

#include "abstractaccount.h"

constexpr auto deposit_suffix = "dpf";

class DepositAccount : public AbstractAccount
{
public:
    DepositAccount();

public:
    static quint64 generateID();
    static QString getFilename(quint64 value);
    static DepositAccount loadFromRecord(quint64 value);

    virtual float profit() const override;
    virtual void saveToRecord(quint64 value) const override;
};

#endif // DEPOSITACCOUNT_H
