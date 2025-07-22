#ifndef ACCOUNTEDITOR_H
#define ACCOUNTEDITOR_H

#include <QDialog>
#include "include/general.h"

namespace Ui {
class AccountEditor;
}

class AccountEditor : public QDialog
{
    Q_OBJECT

public:
    explicit AccountEditor(QWidget *parent = nullptr);
    ~AccountEditor();

    QString owner() const;
    double balance() const;
    Key accountNumber() const;

    QString cardNumber() const;
    QString shabaNumber() const;

    int cvv2() const;
    QDate expirationDate() const;

    QString primaryPassword() const;
    QString secondaryPassword() const;

public slots:
    void setOwner(const QString &value);

    void setBalance(double value);

    void setAccountNumber(const Key &value);

    void setCardNumber(const QString &value);

    void setShabaNumber(const QString &value);

    void setCvv2(int value);

    void setExpirationDate(const QDate &value);

    void setPrimaryPassword(const QString &value);

    void setSecondaryPassword(const QString &value);

signals:
    void ownerChanged(const QString &value);

    void balanceChanged(double value);

    void accountNumberChanged(const Key &value);

    void cardNumberChanged(const QString &value);

    void shabaNumberChanged(const QString &value);

    void cvv2Changed(int value);

    void expirationDateChanged(const QDate &value);

    void primaryPasswordChanged(const QString &value);

    void secondaryPasswordChanged(const QString &value);
    
private:
    std::unique_ptr<Ui::AccountEditor> ui;
};

#endif // ACCOUNTEDITOR_H
