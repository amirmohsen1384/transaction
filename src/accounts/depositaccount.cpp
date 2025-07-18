#include "include/accounts/depositaccount.h"

constexpr auto suffix = "dpf";

DepositAccount::DepositAccount() : AbstractAccount() {}

void DepositAccount::saveToRecord(quint64 value) const
{
    if(!Identifier::isValid(value, Account::Deposit))
    {
        qDebug() << QString("The given ID (%1) is not valid for a deposit account").arg(value);
        return;
    }

    const QString fileName = QString("%1.%2").arg(value).arg(suffix);
    QFile file(Storage::depositAccount().absoluteFilePath(fileName));
    qDebug() << "Saving Deposit Account:" << value;

    if(!file.open(QFile::WriteOnly))
    {
        qDebug() << "Saving Failed: Failed to open file.";
        return;
    }

    QDataStream stream(&file);
    stream << *this;
    if(stream.status() != QDataStream::Ok)
    {
        qDebug() << "Saving Failed: Failed to write file";
    }
    else
    {
        qDebug() << "Saving Completed.";
    }
}

float DepositAccount::profit() const
{
    return 0.10 * balance;
}

DepositAccount DepositAccount::loadFromRecord(quint64 value)
{
    if(!Identifier::isValid(value, Account::Deposit))
    {
        qDebug() << QString("The given ID (%1) is not valid for a deposit account").arg(value);
        return DepositAccount();
    }

    const QString fileName = QString("%1.%2").arg(value).arg(suffix);
    QFile file(Storage::depositAccount().absoluteFilePath(fileName));
    qDebug() << "Loading Deposit Account: " << value;

    if(!file.open(QFile::ReadOnly))
    {
        qDebug() << "Loading Failed: Failed to open file.";
        return DepositAccount();
    }

    QDataStream stream(&file);
    DepositAccount data;
    stream >> data;

    if(stream.status() != QDataStream::Ok)
    {
        qDebug() << "Loading Failed: Failed to read file";
        return DepositAccount();
    }
    else
    {
        qDebug() << "Loading Completed.";
        return data;
    }
}
