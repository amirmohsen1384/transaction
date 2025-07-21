#ifndef ACCOUNTVIEW_H
#define ACCOUNTVIEW_H

#include "include/general.h"
#include <QDialog>

namespace Ui {
class AccountView;
}

class AccountView : public QDialog
{
    Q_OBJECT
private:
    void loadAccount(const Key &value);

public:
    explicit AccountView(const Key &number, QWidget *parent = nullptr);
    explicit AccountView(QWidget *parent = nullptr);
    ~AccountView();

    Key getKey() const;

public slots:
    void setKey(const Key &value);

signals:
    void keyChanged(const Key &value);

private:
    Key value;
    std::unique_ptr<Ui::AccountView> ui;
};

#endif // ACCOUNTVIEW_H
