#include "include/core/cashtransaction.h"
#include "include/users/customer.h"
#include "include/core/errors.h"
#include "include/account.h"
#include <QRandomGenerator>
#include <QPainter>
#include <QImage>

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

QDateTime CashTransaction::getEventDateTime() const
{
    return eventDateTime;
}

QImage CashTransaction::generateImage() const
{
    const auto region = QRect {0, 0, 1000, 1000};
    const auto margins = QMargins {30, 30, 30, 30};

    QImage image(region.size(), QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    const auto drawing = region.marginsRemoved(margins);
    const auto stateRegion = QRect {drawing.topLeft(), QSize(drawing.width(), 80)};
    auto sourceRegion = QRect
        {
            stateRegion.bottomLeft() + QPoint(0, margins.top() + margins.bottom()),
            QSize(drawing.width(), 80)
        };
    auto sourceOwnerRegion = QRect
        {
            sourceRegion.bottomLeft(),
            QSize(drawing.width(), 80)
        };
    auto destinationRegion = QRect
        {
            sourceOwnerRegion.bottomLeft(),
            QSize(drawing.width(), 80)
        };
    auto destinationOwnerRegion = QRect
        {
            destinationRegion.bottomLeft(),
            QSize(drawing.width(), 80)
        };
    auto amountRegion = QRect
        {
            destinationOwnerRegion.bottomLeft(),
            QSize(drawing.width(), 80)
        };
    auto eventRegion = QRect
        {
            amountRegion.bottomLeft(),
            QSize(drawing.width(), 80)
        };

    {
        auto message = QString {};
        auto background = QColor {};

        switch(state)
        {
        case CashTransaction::Successful:
        {
            background = QColor(160, 250, 140); // Green Color
            message = QString("Transaction Completed");
            break;
        }
        case CashTransaction::Pending:
        {
            background = QColor(250, 250, 170); // Yellow Color
            message = QString("Pending Transaction");
            break;
        }
        case CashTransaction::Failed:
        {
            background = QColor(250, 170, 170); // Red Color
            message = QString("Transaction Failed");
            break;
        }
        }

        auto font = painter.font();
        painter.fillRect(stateRegion, background);

        painter.setFont(QFont("Segoe Print", 24, QFont::Bold));
        painter.drawText(stateRegion, message, QTextOption(Qt::AlignCenter));

        painter.setFont(font);
    }

    {
        painter.fillRect(sourceRegion, Qt::lightGray);
        sourceRegion = sourceRegion.marginsRemoved(QMargins(5, 5, 5, 5));

        auto font = painter.font();
        painter.setFont(QFont("Segoe UI", 16, QFont::Bold));
        painter.drawText(sourceRegion, QString("Source Account:"), QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

        QString number = QString::number(sourceId);
        for(int i = 2; i <= 4; ++i)
        {
            number[i] = '*';
        }
        painter.drawText(sourceRegion, number, QTextOption(Qt::AlignRight | Qt::AlignVCenter));

        painter.setFont(font);
    }

    {
        painter.fillRect(destinationRegion, Qt::lightGray);
        destinationRegion = destinationRegion.marginsRemoved(QMargins(5, 5, 5, 5));

        auto font = painter.font();
        painter.setFont(QFont("Segoe UI", 16, QFont::Bold));
        painter.drawText(destinationRegion, QString("Destination Account:"), QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

        QString number = QString::number(destinationId);
        for(int i = 2; i <= 4; ++i)
        {
            number[i] = '*';
        }
        painter.drawText(destinationRegion, number, QTextOption(Qt::AlignRight | Qt::AlignVCenter));
        painter.setFont(font);
    }

    {
        painter.fillRect(amountRegion, Qt::lightGray);
        amountRegion = amountRegion.marginsRemoved(QMargins(5, 5, 5, 5));

        auto font = painter.font();
        painter.setFont(QFont("Segoe UI", 16, QFont::Bold));
        painter.drawText(amountRegion, QString("Transferred Amount:"), QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
        painter.drawText(amountRegion, QString("%1 Rials").arg(amount), QTextOption(Qt::AlignRight | Qt::AlignVCenter));
        painter.setFont(font);
    }

    {
        painter.fillRect(destinationOwnerRegion, Qt::lightGray);
        destinationOwnerRegion = destinationOwnerRegion.marginsRemoved(QMargins(5, 5, 5, 5));

        auto ownerKey = loadFromKey(destinationId);
        auto name = Customer::loadFromRecord(ownerKey->getOwner()).getName();

        auto font = painter.font();
        painter.setFont(QFont("Segoe UI", 16, QFont::Bold));
        painter.drawText(destinationOwnerRegion, QString("Destination's Owner:"), QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
        painter.drawText(destinationOwnerRegion, name, QTextOption(Qt::AlignRight | Qt::AlignVCenter));
        painter.setFont(font);
    }

    {
        painter.fillRect(destinationOwnerRegion, Qt::lightGray);
        destinationOwnerRegion = destinationOwnerRegion.marginsRemoved(QMargins(5, 5, 5, 5));

        auto ownerKey = loadFromKey(destinationId);
        auto name = Customer::loadFromRecord(ownerKey->getOwner()).getName();

        auto font = painter.font();
        painter.setFont(QFont("Segoe UI", 16, QFont::Bold));
        painter.drawText(destinationOwnerRegion, QString("Destination's Owner:"), QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
        painter.drawText(destinationOwnerRegion, name, QTextOption(Qt::AlignRight | Qt::AlignVCenter));
        painter.setFont(font);
    }

    {
        painter.fillRect(eventRegion, Qt::lightGray);
        eventRegion = eventRegion.marginsRemoved(QMargins(5, 5, 5, 5));

        auto font = painter.font();
        painter.setFont(QFont("Segoe UI", 16, QFont::Bold));
        painter.drawText(eventRegion, QString("Transaction Date & Time:"), QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
        painter.drawText(eventRegion, eventDateTime.toString(), QTextOption(Qt::AlignRight | Qt::AlignVCenter));
        painter.setFont(font);
    }

    {
        painter.fillRect(sourceOwnerRegion, Qt::lightGray);
        sourceOwnerRegion = sourceOwnerRegion.marginsRemoved(QMargins(5, 5, 5, 5));

        auto ownerKey = loadFromKey(sourceId);
        auto name = Customer::loadFromRecord(ownerKey->getOwner()).getName();

        auto font = painter.font();
        painter.setFont(QFont("Segoe UI", 16, QFont::Bold));
        painter.drawText(sourceOwnerRegion, QString("Source's Owner:"), QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
        painter.drawText(sourceOwnerRegion, name, QTextOption(Qt::AlignRight | Qt::AlignVCenter));
        painter.setFont(font);
    }

    return image;
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
        eventDateTime = QDateTime::currentDateTime();
        setStatus(CashTransaction::Failed);
        throw UnknownSourceException();
    }

    auto destination = loadFromKey(destinationId);
    if(destination == nullptr)
    {
        eventDateTime = QDateTime::currentDateTime();
        setStatus(CashTransaction::Failed);
        throw UnknownDestinationException();
    }

    if(QDate::currentDate() > source->getExpirationDate())
    {
        eventDateTime = QDateTime::currentDateTime();
        setStatus(CashTransaction::Failed);
        throw ExpiredCardException();
    }

    if(this->amount > this->maximumTransaction())
    {
        eventDateTime = QDateTime::currentDateTime();
        setStatus(CashTransaction::Failed);
        throw ExceededCashWithdrawException();
    }

    auto final = (1 + this->income()) * this->amount;
    if(final > source->getBalance())
    {
        eventDateTime = QDateTime::currentDateTime();
        setStatus(CashTransaction::Failed);
        throw NotEnoughBalanceException();
    }

    auto transferred = source->getTransferredBalance();
    if(final + transferred > this->maximumDailyTransaction())
    {
        eventDateTime = QDateTime::currentDateTime();
        setStatus(CashTransaction::Failed);
        throw ExceededDailyTransactionLimitExcepion();
    }

    if(cvv2 != source->getCvv2())
    {
        eventDateTime = QDateTime::currentDateTime();
        setStatus(CashTransaction::Failed);
        throw IncorrectCVV2Exception();
    }

    if(this->amount > maximumTransactionWithoutDynamicPassword())
    {
        if(dynamicPassword != password)
        {
            eventDateTime = QDateTime::currentDateTime();
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
                eventDateTime = QDateTime::currentDateTime();
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

    eventDateTime = QDateTime::currentDateTime();
    setStatus(CashTransaction::Successful);
    qDebug() << "Transaction Completed";
}
