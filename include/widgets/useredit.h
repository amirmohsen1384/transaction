#ifndef USEREDIT_H
#define USEREDIT_H

#include <QDialog>

namespace Ui {
class UserEdit;
}

class UserEdit : public QDialog
{
    Q_OBJECT

public:
    explicit UserEdit(QWidget *parent = nullptr);
    ~UserEdit();

private:
    Ui::UserEdit *ui;
};

#endif // USEREDIT_H
