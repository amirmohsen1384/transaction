#include "include/delegates/accountdelegate.h"
#include "include/accounts/abstractaccount.h"
#include <QPainter>

QMargins AccountDelegate::margins = QMargins(10, 10, 10, 10);

AccountDelegate::AccountDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

QSize AccountDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int width = 300;
    int height = static_cast<int>(width / 1.586);
    return QSize(width + margins.left() + margins.right(), height + margins.top() + margins.bottom());
}

void AccountDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto region = option.rect;
    region.marginsRemoved(margins);
    auto data = qvariant_cast<std::shared_ptr<AbstractAccount>>(index.data(Qt::UserRole));
    {
        auto pen = painter->pen();
        auto brush = painter->brush();

        painter->setPen(Qt::NoPen);
        painter->setBrush(index.data(Qt::BackgroundRole).value<QColor>());

        painter->drawRoundedRect(region, 20.0, 15.0);
        painter->setBrush(brush);
        painter->setPen(pen);
    }
    {
        auto font = painter->font();
        painter->setFont(QFont("Lucida Console", 14));
        painter->drawText(region, data->getCardNumber(), QTextOption(Qt::AlignCenter));
        painter->setFont(font);
    }
    {
        region.marginsRemoved(margins);
        auto font = painter->font();
        painter->setFont(QFont("Segoe UI", 12, QFont::Bold));
        painter->drawText(region, QString("%1 Rials").arg(data->getBalance()),
            QTextOption(Qt::AlignRight | Qt::AlignBottom)
        );
        painter->drawText(region, QString("Expires: %1").arg(data->getExpirationDate().toString("yyyy/MM/dd")),
            QTextOption(Qt::AlignLeft | Qt::AlignBottom)
        );
        painter->setFont(font);
    }
}
