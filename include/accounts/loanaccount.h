#ifndef LOANACCOUNT_H
#define LOANACCOUNT_H

#include "abstractaccount.h"

class LoanAccount : public AbstractAccount
{
public:
    LoanAccount();

public:
    static quint64 generateID();
    static QString getFilename(quint64 value);
    static LoanAccount loadFromRecord(quint64 value);

    virtual float profit() const override;
    virtual void saveToRecord(quint64 value) const override;
};

#endif // LOANACCOUNT_H
