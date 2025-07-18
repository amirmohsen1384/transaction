#ifndef ACCOUNTDELEGATE_H
#define ACCOUNTDELEGATE_H

#include <QStyledItemDelegate>

class AccountDelegate : public QStyledItemDelegate
{
private:
    static QMargins margins;

public:
    AccountDelegate(QObject *parent = nullptr);
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // ACCOUNTDELEGATE_H
