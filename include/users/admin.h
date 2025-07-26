#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"

constexpr auto admin_suffix = "adf";

class Admin : public User
{
public:
    Admin();

public:
    static quint64 generateID();
    static Admin loadFromRecord(quint64 value);
    virtual void saveToRecord(quint64 value) const override;
};

#endif // ADMIN_H
