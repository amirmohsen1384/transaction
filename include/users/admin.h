#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"

class Admin : public User
{
public:
    Admin();

public:
    static Admin loadFromRecord(quint64 value);
    virtual void saveToRecord(quint64 value) const override;
};

#endif // ADMIN_H
