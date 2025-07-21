#include "include/accounts/loanaccount.h"

constexpr auto suffix = "lnf";

LoanAccount::LoanAccount() : AbstractAccount() {}

QString LoanAccount::getFilename(quint64 value)
{
    return QString("%1.%2").arg(value).arg(suffix);
}

float LoanAccount::profit() const
{
    return balance * 0.01;
}

LoanAccount LoanAccount::loadFromRecord(quint64 value)
{
    if(!Identifier::isValid(value, Account::Loan))
    {
        qDebug() << QString("The given ID (%1) is not valid for a loan account").arg(value);
        return LoanAccount();
    }

    QFile file(Storage::loanAccount().absoluteFilePath(getFilename(value)));
    qDebug() << "Loading Loan Account:" << value;

    if(!file.open(QFile::ReadOnly))
    {
        qDebug() << "Loading Failed: Failed to open file.";
        return LoanAccount();
    }

    QDataStream stream(&file);
    LoanAccount data;
    stream >> data;

    if(stream.status() != QDataStream::Ok)
    {
        qDebug() << "Loading Failed: Failed to read file";
        return LoanAccount();
    }
    else
    {
        qDebug() << "Loading Completed.";
        return data;
    }
}

void LoanAccount::saveToRecord(quint64 value) const
{
    if(!Identifier::isValid(value, Account::Loan))
    {
        qDebug() << QString("The given ID (%1) is not valid for a loan account").arg(value);
        return;
    }

    const QString fileName = QString("%1.%2").arg(value).arg(suffix);
    QFile file(Storage::loanAccount().absoluteFilePath(fileName));
    qDebug() << "Saving Loan Account: " << value;

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
