#include "include/models/accountlistmodel.h"
#include "include/users/customer.h"
#include <QRandomGenerator>

void AccountListModel::updateData()
{
    beginResetModel();
    container.clear();

    if(!Identifier::isValid(identifier) || !Storage::customerFolder(identifier).exists())
    {
        qDebug() << "The given customer key is not valid nor not available.";
        return;
    }

    auto keys = Customer::loadKeysFromRecord(identifier);
    if(keys.isEmpty())
    {
        qDebug() << "No card keys available for the customer.";
        return;
    }

    auto generator = QRandomGenerator::global();
    for(const Key &value : keys)
    {
        auto account = loadFromKey(value);
        if(account != nullptr)
        {
            AccountData target;
            target.id = value;
            target.data = account;
            target.background.setHsvF(generator->bounded(float(0.5)), 0.5, 0.9);
            container.append(target);
        }
    }

    endResetModel();
}

AccountListModel::AccountListModel(QObject *parent) : QAbstractListModel(parent)
{}

int AccountListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    return container.size();
}

QVariant AccountListModel::data(const QModelIndex &index, int role) const
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

Key AccountListModel::getIdentifier() const
{
    return identifier;
}

void AccountListModel::setIdentifier(const Key &value)
{
    identifier = value;
    emit identifierChanged(value);
}
