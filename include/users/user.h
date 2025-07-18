#ifndef USER_H
#define USER_H

#include <QString>
#include "include/entity.h"

class User : public Entity
{
public:
    User();

    quint64 getNationalCode() const;
    void setNationalCode(quint64 value);

    QString getFirstName() const;
    void setFirstName(const QString &value);

    QString getLastName() const;
    void setLastName(const QString &value);

    QString getUserName() const;
    void setUserName(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    quint64 getAge() const;
    void setAge(quint64 value);

    friend QDataStream &operator<<(QDataStream &stream, const User &user);
    friend QDataStream &operator>>(QDataStream &stream, User &user);

private:
    quint64 nationalCode;
    QString firstName;
    QString lastName;
    QString userName;
    QString password;
    quint64 age;
};

QDataStream &operator<<(QDataStream &stream, const User &user);
QDataStream &operator>>(QDataStream &stream, User &user);

#endif // USER_H
