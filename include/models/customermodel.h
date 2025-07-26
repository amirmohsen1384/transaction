#ifndef CUSTOMERMODEL_H
#define CUSTOMERMODEL_H

#include "include/users/customer.h"
#include "include/account.h"
#include <QAbstractListModel>
#include <QColor>

class CustomerModel : public QAbstractListModel
{
    Q_OBJECT
private slots:
    void updateData();

public:
    struct AccountData
    {
        Key identifier;
        std::shared_ptr<AbstractAccount> data;
    };
public:
    explicit CustomerModel(QObject *parent = nullptr);
    explicit CustomerModel(const Key &identifier, QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) override;
    virtual QVariant headerData(int section = 0, Qt::Orientation orientation = Qt::Horizontal, int role = Qt::UserRole) const override;

public:
    Key getIdentifier() const;

public slots:
    void setIdentifier(const Key &value);

signals:
    void identifierChanged(const Key &value);

private:
    Customer metadata;
    Key identifier = 0;
    QList<AccountData> container;
};

#endif // CUSTOMERMODEL_H
