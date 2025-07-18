#include "include/users/user.h"

User::User() : Entity()
{}

quint64 User::getNationalCode() const
{
    return nationalCode;
}

void User::setNationalCode(quint64 value)
{
    nationalCode = value;
}

QString User::getFirstName() const
{
    return firstName;
}

void User::setFirstName(const QString &value)
{
    firstName = value;
}

QString User::getLastName() const
{
    return lastName;
}

void User::setLastName(const QString &value)
{
    lastName = value;
}

QString User::getUserName() const
{
    return userName;
}

void User::setUserName(const QString &value)
{
    userName = value;
}

QString User::getPassword() const
{
    return password;
}

void User::setPassword(const QString &value)
{
    password = value;
}

quint64 User::getAge() const
{
    return age;
}

void User::setAge(quint64 value)
{
    age = value;
}

QDataStream &operator<<(QDataStream &stream, const User &user)
{
    stream << user.nationalCode << user.firstName;
    stream << user.lastName << user.userName;
    stream << user.password << user.age;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, User &user)
{
    stream >> user.nationalCode >> user.firstName;
    stream >> user.lastName >> user.userName;
    stream >> user.password >> user.age;
    return stream;
}
