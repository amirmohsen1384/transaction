#ifndef CASHTRANSACTION_H
#define CASHTRANSACTION_H

#include <QObject>

class CashTransaction : public QObject
{
    Q_OBJECT
public:
    explicit CashTransaction(QObject *parent = nullptr);

signals:
};

#endif // CASHTRANSACTION_H
