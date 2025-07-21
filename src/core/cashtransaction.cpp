#include "include/core/cashtransaction.h"
#include "include/core/errors.h"
#include "include/account.h"
#include <QRandomGenerator>
#include <QPrinter>

CashTransaction::CashTransaction(QObject *parent) : QObject{parent}
{}

CashTransaction::Status CashTransaction::getStatus() const
{
    return state;
}

double CashTransaction::maximumTransaction() const
{
    return 3 * std::pow(10, 6);
}

double CashTransaction::maximumDailyTransaction() const
{
    return 6 * std::pow(10, 6);
}

double CashTransaction::maximumTransactionWithoutDynamicPassword() const
{
    return 1 * std::pow(10, 5);
}

long int CashTransaction::getDynamicPassword() const
{
    return dynamicPassword;
}

void CashTransaction::generateDynamicPassword()
{
    dynamicPassword = QRandomGenerator::global()->bounded(quint64(0), quint64(std::pow(10, 5) - 1));
    emit dynamicPasswordCreated();
}

Key CashTransaction::getDestinationId() const
{
    return destinationId;
}

void CashTransaction::setDestinationId(const Key &value)
{
    if (destinationId != value) {
        destinationId = value;
        emit destinationIdChanged(value);
    }
}

void CashTransaction::setStatus(const Status value)
{
    this->state = value;
    emit statusChanged(value);
}

Key CashTransaction::getSourceId() const
{
    return sourceId;
}

double CashTransaction::income() const
{
    return 0.01 / 100;
}

void CashTransaction::setSourceId(const Key &value)
{
    if (sourceId != value) {
        sourceId = value;
        emit sourceIdChanged(value);
    }
}

long int CashTransaction::getPassword() const
{
    return password;
}

void CashTransaction::setPassword(long int value)
{
    if (password != value) {
        password = value;
        emit passwordChanged(value);
    }
}

double CashTransaction::getAmount() const
{
    return amount;
}

void CashTransaction::setAmount(double value)
{
    if (amount != value) {
        amount = value;
        emit amountChanged(value);
    }
}

long int CashTransaction::getCvv2() const
{
    return cvv2;
}

void CashTransaction::setCvv2(long int value)
{
    if (cvv2 != value) {
        cvv2 = value;
        emit cvv2Changed(value);
    }
}

void CashTransaction::transfer()
{
    auto source = loadFromKey(sourceId);
    if(source == nullptr)
    {
        setStatus(CashTransaction::Failed);
        throw UnknownSourceException();
    }

    auto destination = loadFromKey(destinationId);
    if(destination == nullptr)
    {
        setStatus(CashTransaction::Failed);
        throw UnknownDestinationException();
    }

    if(QDate::currentDate() > source->getExpirationDate())
    {
        setStatus(CashTransaction::Failed);
        throw ExpiredCardException();
    }

    if(this->amount > this->maximumTransaction())
    {
        setStatus(CashTransaction::Failed);
        throw ExceededCashWithdrawException();
    }

    auto final = (1 + this->income()) * this->amount;
    if(final > source->getBalance())
    {
        setStatus(CashTransaction::Failed);
        throw NotEnoughBalanceException();
    }

    auto transferred = source->getTransferredBalance();
    if(final + transferred > this->maximumDailyTransaction())
    {
        setStatus(CashTransaction::Failed);
        throw ExceededDailyTransactionLimitExcepion();
    }

    if(cvv2 != source->getCvv2())
    {
        setStatus(CashTransaction::Failed);
        throw IncorrectCVV2Exception();
    }

    if(this->amount > maximumTransactionWithoutDynamicPassword())
    {
        if(dynamicPassword != password)
        {
            setStatus(CashTransaction::Failed);
            throw IncorrectPasswordException();
        }
    }
    else
    {
        if(password != source->getPrimaryPassword())
        {
            if(password != source->getSecondaryPassword())
            {
                setStatus(CashTransaction::Failed);
                throw IncorrectPasswordException();
            }
        }

    }

    source->setTransferredBalance(source->getTransferredBalance() + this->amount);
    destination->setBalance(destination->getBalance() + this->amount);
    source->setBalance(source->getBalance() - final);

    destination->saveToRecord(destinationId);
    source->saveToRecord(sourceId);

    setStatus(CashTransaction::Successful);
}

void CashTransaction::generatePDF() const
{

}
