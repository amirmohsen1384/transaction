#ifndef CASHTRANSACTION_H
#define CASHTRANSACTION_H

#include <QObject>
#include "include/general.h"

class CashTransaction : public QObject
{
    Q_OBJECT
public:
    Q_DISABLE_COPY_MOVE(CashTransaction)
    explicit CashTransaction(QObject *parent = nullptr);
    long int getDynamicPassword() const;
    Key getDestinationId() const;
    long int getPassword() const;
    double getAmount() const;
    long int getCvv2() const;
    Key getSourceId() const;

protected:
    virtual double income() const;
    virtual double maximumTransaction() const;
    virtual double maximumDailyTransaction() const;
    virtual double maximumTransactionWithoutDynamicPassword() const;

public slots:
    void transfer();
    void setCvv2(long int value);
    void setAmount(double value);
    void generateDynamicPassword();
    void setPassword(long int value);
    void setSourceId(const Key &value);
    void setDestinationId(const Key &value);

signals:
    void destinationIdChanged(const Key &value);
    void sourceIdChanged(const Key &value);
    void passwordChanged(long int value);
    void amountChanged(double value);
    void cvv2Changed(long int value);
    void dynamicPasswordCreated();
    
private:
    long int dynamicPassword = 0;
    Key destinationId = 0;
    long int password = 0;
    double amount = 0.0;
    long int cvv2 = 0;
    Key sourceId = 0;
};

#endif // CASHTRANSACTION_H
