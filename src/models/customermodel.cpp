#include "include/models/customermodel.h"
#include "include/users/customer.h"
#include <QRandomGenerator>

void CustomerModel::updateData()
{
    beginResetModel();
    container.clear();

    if(!Identifier::isValid(identifier) || !Storage::customerFolder(identifier).exists())
    {
        qDebug() << "The given customer key is not valid nor available.";
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
            for(const Key &value : keys)
            {
                auto account = loadFromKey(value);
                if(account != nullptr)
                {
                    container.append({value, account});
                }
            }
        }
    }

    endResetModel();
    metadata = Customer::loadFromRecord(identifier);
}

CustomerModel::CustomerModel(QObject *parent) : QAbstractListModel(parent)
{
    connect(this, &CustomerModel::identifierChanged, this, &CustomerModel::updateData);
}

CustomerModel::CustomerModel(const Key &identifier, QObject *parent) : CustomerModel(parent)
{
    setIdentifier(identifier);
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
    auto target = container.at(index.row());
    switch(role)
    {
    case Qt::DisplayRole:
    {
        return target.identifier;
    }
    case Qt::UserRole:
    {
        return QVariant::fromValue(target.data);
    }
    case AbstractAccount::KeyRole:
    {
        return target.identifier;
    }
    default:
    {
        return {};
    }
    }
}

QVariant CustomerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(role)
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    return QVariant::fromValue(metadata);
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
