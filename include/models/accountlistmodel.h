#ifndef ACCOUNTLISTMODEL_H
#define ACCOUNTLISTMODEL_H

#include "include/account.h"
#include <QAbstractListModel>
#include <QColor>

class AccountListModel : public QAbstractListModel
{
    Q_OBJECT
private slots:
    void updateData();

public:
    struct AccountData
    {
        Key id;
        QColor background;
        std::shared_ptr<AbstractAccount> data;
    };

public:
    explicit AccountListModel(QObject *parent = nullptr);
    explicit AccountListModel(const Key &identifier, QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public:
    Key getIdentifier() const;

public slots:
    void setIdentifier(const Key &value);

signals:
    void identifierChanged(const Key &value);

private:
    Key identifier = 0;
    QList<AccountData> container;
};

#endif // ACCOUNTLISTMODEL_H
