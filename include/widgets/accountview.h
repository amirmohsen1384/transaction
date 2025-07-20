#ifndef ACCOUNTVIEW_H
#define ACCOUNTVIEW_H

#include <QDialog>

namespace Ui {
class AccountView;
}

class AccountView : public QDialog
{
    Q_OBJECT

public:
    explicit AccountView(QWidget *parent = nullptr);
    ~AccountView();

private:
    Ui::AccountView *ui;
};

#endif // ACCOUNTVIEW_H
