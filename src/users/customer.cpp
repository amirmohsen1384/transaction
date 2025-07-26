#include "include/users/customer.h"
#include "include/account.h"
#include <QRandomGenerator>

Customer::Customer() : User() {}

quint64 Customer::generateID()
{
    return QRandomGenerator::global()->bounded(std::pow(10, 7) - 1);
}

void Customer::saveToRecord(quint64 value) const
{
    if(!Identifier::isValid(value))
    {
        qDebug() << QString("The given ID (%1) is not valid for a customer.").arg(value);
        return;
    }

    const auto fileName = Storage::customerFolder(value).absoluteFilePath(QString("metadata.%1").arg(customer_suffix));

    QFile file(fileName);
    qDebug() << "Saving Customer Data:" << value;

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

KeyList Customer::loadKeysFromRecord(Key value)
{
    if(!Identifier::isValid(value))
    {
        qDebug() << QString("The given ID (%1) is not valid for a customer.").arg(value);
        return KeyList();
    }

    const auto fileName = Storage::customerFolder(value).absoluteFilePath(QString("keys.%1").arg(customer_suffix));
    QFile file(fileName);
    qDebug() << "Loading Customer Keys:" << value;

    if(!file.open(QFile::ReadOnly))
    {
        qDebug() << "Loading Failed: Failed to open file.";
        return KeyList();
    }

    QDataStream stream(&file);
    KeyList data;
    stream >> data;

    if(stream.status() != QDataStream::Ok)
    {
        qDebug() << "Load Failed: Failed to load file";
        return KeyList();
    }
    else
    {
        qDebug() << "Loading Completed.";
        return data;
    }
}

void Customer::saveKeysToRecord(Key value, const KeyList &data) const
{
    if(!Identifier::isValid(value))
    {
        qDebug() << QString("The given ID (%1) is not valid for a customer.").arg(value);
        return;
    }

    const auto fileName = Storage::customerFolder(value).absoluteFilePath(QString("keys.%1").arg(suffix));
    QFile file(fileName);
    qDebug() << "Saving Customer Keys:" << value;

    if(!file.open(QFile::WriteOnly))
    {
        qDebug() << "Saving Failed: Failed to open file.";
        return;
    }

    auto target = data;
    for(const auto &key : target)
    {
        auto account = loadFromKey(key);
        account->setOwner(value);
        account->saveToRecord(key);
        qDebug() << QString("Changed the owner of %1 to %2").arg(key).arg(value);
    }

    QDataStream stream(&file);
    stream << data;
    if(stream.status() != QDataStream::Ok)
    {
        qDebug() << "Saving Failed: Failed to write file";
    }
    else
    {
        qDebug() << "Saving Completed.";
    }
}

Customer Customer::loadFromRecord(quint64 value)
{
    if(!Identifier::isValid(value))
    {
        qDebug() << QString("The given ID (%1) is not valid for a customer.").arg(value);
        return Customer();
    }

    const auto fileName = Storage::customerFolder(value).absoluteFilePath(QString("metadata.%1").arg(suffix));

    QFile file(fileName);
    qDebug() << "Loading Customer Data:" << value;

    if(!file.open(QFile::ReadOnly))
    {
        qDebug() << "Loading Failed: Failed to open file.";
        return Customer();
    }

    QDataStream stream(&file);
    Customer data;
    stream >> data;

    if(stream.status() != QDataStream::Ok)
    {
        qDebug() << "Load Failed: Failed to load file";
        return Customer();
    }
    else
    {
        qDebug() << "Loading Completed.";
        return data;
    }
}
