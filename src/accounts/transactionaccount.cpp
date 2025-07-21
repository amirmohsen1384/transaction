#include "include/accounts/transactionaccount.h"

constexpr auto suffix = "trf";

TransactionAccount::TransactionAccount() : AbstractAccount() {}

QString TransactionAccount::getFilename(quint64 value)
{
    return QString("%1.%2").arg(value).arg(suffix);
}

float TransactionAccount::profit() const
{
    return 0 * this->balance;
}

TransactionAccount TransactionAccount::loadFromRecord(quint64 value)
{
    if(!Identifier::isValid(value, Account::Transaction))
    {
        qDebug() << QString("The given ID (%1) is not valid for a transaction account").arg(value);
        return TransactionAccount();
    }

    QFile file(Storage::transactionAccount().absoluteFilePath(getFilename(value)));
    qDebug() << "Loading Transaction Account:" << value;

    if(!file.open(QFile::ReadOnly))
    {
        qDebug() << "Loading Failed: Failed to open file.";
        return TransactionAccount();
    }

    QDataStream stream(&file);
    TransactionAccount data;
    stream >> data;

    if(stream.status() != QDataStream::Ok)
    {
        qDebug() << "Loading Failed: Failed to read file";
        return TransactionAccount();
    }
    else
    {
        qDebug() << "Loading Completed.";
        return data;
    }
}

void TransactionAccount::saveToRecord(quint64 value) const
{
    if(!Identifier::isValid(value, Account::Transaction))
    {
        qDebug() << QString("The given ID (%1) is not valid for a transaction account").arg(value);
        return;
    }

    const QString fileName = QString("%1.%2").arg(value).arg(suffix);
    QFile file(Storage::transactionAccount().absoluteFilePath(fileName));
    qDebug() << "Saving Transaction Account: " << value;

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
