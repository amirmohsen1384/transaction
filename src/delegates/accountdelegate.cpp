#include "include/delegates/accountdelegate.h"
#include "include/accounts/abstractaccount.h"
#include <QPainter>

QMargins AccountDelegate::margins = QMargins(10, 10, 10, 10);

AccountDelegate::AccountDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

QSize AccountDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    Q_UNUSED(option)

    int width = 300;
    int height = static_cast<int>(width / 1.586);
    return QSize(width + margins.left() + margins.right(), height + margins.top() + margins.bottom());
}

void AccountDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto region = option.rect;
    if(option.state.testFlag(QStyle::State_MouseOver))
    {
        painter->fillRect(option.rect, QColor(210, 220, 220));
    }

    region = region.marginsRemoved(margins);
    painter->setRenderHint(QPainter::Antialiasing, true);

    auto data = qvariant_cast<std::shared_ptr<AbstractAccount>>(index.data(Qt::UserRole));
    {
        auto pen = painter->pen();
        auto brush = painter->brush();

        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(160, 240, 150));

        painter->drawRoundedRect(region, 20.0, 15.0);
        painter->setBrush(brush);
        painter->setPen(pen);
    }
    {
        const auto font = painter->font();
        painter->setFont(QFont("Lucida Console", 14));
        painter->drawText(region, index.data(AbstractAccount::KeyRole).toString(), QTextOption(Qt::AlignCenter));
        painter->setFont(font);
    }
    {
        auto target = region.marginsRemoved(margins);
        auto font = painter->font();
        painter->setFont(QFont("Pricedown", 18, QFont::Bold));
        painter->drawText(target, QString("%1 Ø").arg(data->getBalance()),
            QTextOption(Qt::AlignRight | Qt::AlignBottom)
        );
        painter->setFont(QFont("Segoe UI", 10, QFont::Bold));
        painter->drawText(target, QString("Expires: %1").arg(data->getExpirationDate().toString("yy/MM")),
            QTextOption(Qt::AlignLeft | Qt::AlignBottom)
        );
        painter->setFont(font);
    }
}
