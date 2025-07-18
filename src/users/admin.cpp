#include "include/users/admin.h"

constexpr auto suffix = "adf";

Admin::Admin() : User() {}

Admin Admin::loadFromRecord(quint64 value)
{
    if(!Identifier::isValid(value))
    {
        qDebug() << QString("The given ID (%1) is not valid for an admin.").arg(value);
        return Admin();
    }

    const QString fileName = QString("%1.%2").arg(value).arg(suffix);
    QFile file(Storage::admin().absoluteFilePath(fileName));
    qDebug() << "Loading Adminstrator Data:" << value;

    if(!file.open(QFile::ReadOnly))
    {
        qDebug() << "Loading Failed: Failed to open file.";
        return Admin();
    }

    QDataStream stream(&file);
    Admin data;
    stream >> data;

    if(stream.status() != QDataStream::Ok)
    {
        qDebug() << "Load Failed: Failed to load file";
        return Admin();
    }
    else
    {
        qDebug() << "Loading Completed.";
        return data;
    }
}

void Admin::saveToRecord(quint64 value) const
{
    if(!Identifier::isValid(value))
    {
        qDebug() << QString("The given ID (%1) is not valid for an admin.").arg(value);
        return;
    }

    const QString fileName = QString("%1.%2").arg(value).arg(suffix);
    QFile file(Storage::admin().absoluteFilePath(fileName));
    qDebug() << "Saving Adminstrator Data:" << value;

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
