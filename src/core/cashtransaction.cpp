#include "include/core/cashtransaction.h"
#include "include/core/errors.h"
#include "include/account.h"
#include <QRandomGenerator>

CashTransaction::CashTransaction(QObject *parent) : QObject{parent}
{}

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

void CashTransaction::reset()
{
    dynamicPassword = 0;
    setDestinationId(0);
    setAmount(0.0);
    setSourceId(0);
    setPassword(0);
    setCvv2(0);
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
        throw UnknownSourceException();
    }

    auto destination = loadFromKey(destinationId);
    if(destination == nullptr)
    {
        throw UnknownDestinationException();
    }

    if(QDate::currentDate() > source->getExpirationDate())
    {
        throw ExpiredCardException();
    }

    if(this->amount > this->maximumTransaction())
    {
        throw ExceededCashWithdraw();
    }

    auto final = (1 + this->income()) * this->amount;
    if(final > source->getBalance())
    {
        throw NotEnoughBalanceException();
    }

    auto transferred = source->getTransferredBalance();
    if(final + transferred > this->maximumDailyTransaction())
    {
        throw ExceededDailyTransactionLimit();
    }
    auto base = double {};
    if(this->amount > maximumTransactionWithoutDynamicPassword())
    {
        base = dynamicPassword;
    }
    else
    {
        base = source->getSecondaryPassword();
    }

    if(base != password)
    {
        throw IncorrectPasswordException();
    }

    source->setTransferredBalance(source->getTransferredBalance() + this->amount);
    destination->setBalance(destination->getBalance() + this->amount);
    source->setBalance(source->getBalance() - final);

    destination->saveToRecord(destinationId);
    source->saveToRecord(sourceId);
}
