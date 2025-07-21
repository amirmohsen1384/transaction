#include "include/models/customermodel.h"
#include "include/users/customer.h"
#include <QRandomGenerator>

void CustomerModel::updateData()
{
    beginResetModel();
    container.clear();

    if(!Identifier::isValid(identifier) || !Storage::customerFolder(identifier).exists())
    {
        qDebug() << "The given customer key is not valid nor not available.";
    }
    else
    {
        auto keys = Customer::loadKeysFromRecord(identifier);
        if(keys.isEmpty())
        {
            qDebug() << "No card keys available for the customer.";
        }
        else
        {
            auto generator = QRandomGenerator::global();
            for(const Key &value : keys)
            {
                auto account = loadFromKey(value);
                if(account != nullptr)
                {
                    AccountData target;
                    target.data = account;
                    target.identifier = value;
                    container.append(target);
                }
            }
        }
    }

    endResetModel();
}

CustomerModel::CustomerModel(QObject *parent) : QAbstractListModel(parent)
{
    connect(this, &CustomerModel::identifierChanged, this, &CustomerModel::updateData);
}

int CustomerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    return container.size();
}

QVariant CustomerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return {};
    }
    auto target = container[index.row()];
    switch(role)
    {
    case Qt::DisplayRole:
    {
        return target.id;
    }
    case Qt::BackgroundRole:
    {
        return target.background;
    }
    case Qt::UserRole:
    {
        return QVariant::fromValue(target.data);
    }
    case AbstractAccount::KeyRole:
    {
        return target.id;
    }
    default:
    {
        return {};
    }
    }
}

Key CustomerModel::getIdentifier() const
{
    return identifier;
}

void CustomerModel::setIdentifier(const Key &value)
{
    identifier = value;
    emit identifierChanged(value);
}
