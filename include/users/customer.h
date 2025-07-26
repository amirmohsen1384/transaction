#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"

constexpr auto customer_suffix = "csf";

class Customer : public User
{
public:
    Customer();

public:
    static quint64 generateID();
    static Customer loadFromRecord(quint64 value);
    virtual void saveToRecord(quint64 value) const override;

    static KeyList loadKeysFromRecord(Key value);
    virtual void saveKeysToRecord(Key value, const KeyList &data) const;
};

#endif // CUSTOMER_H
