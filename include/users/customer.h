#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"

class Customer : public User
{
public:
    Customer();

public:
    static Customer loadFromRecord(quint64 value);
    virtual void saveToRecord(quint64 value) const override;

    static KeyList loadKeysFromRecord(Key value);
    virtual void saveKeysToRecord(Key value, const KeyList &data) const;
};

#endif // CUSTOMER_H
