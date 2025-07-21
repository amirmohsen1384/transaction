#include "include/accounts/depositaccount.h"
#include <QRandomGenerator>

constexpr auto suffix = "dpf";

DepositAccount::DepositAccount() : AbstractAccount() {}

quint64 DepositAccount::generateID()
{
    auto generator = QRandomGenerator::global();
    int number = generator->bounded(int(std::pow(10, GENERAL_DIGITS - 1)), int(std::pow(10, GENERAL_DIGITS) - 1));
    number *= std::pow(10, VALID_DIGITS);
    number += DEPOSIT_ID;
    return number;
}

QString DepositAccount::getFilename(quint64 value)
{
    return QString("%1.%2").arg(value).arg(suffix);
}

void DepositAccount::saveToRecord(quint64 value) const
{
    if(!Identifier::isValid(value, Account::Deposit))
    {
        qDebug() << QString("The given ID (%1) is not valid for a deposit account").arg(value);
        return;
    }

    QFile file(Storage::depositAccount().absoluteFilePath(getFilename(value)));
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
