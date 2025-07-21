#ifndef USEREDIT_H
#define USEREDIT_H

#include <QDialog>

/*
    First Name,
    Last Name,
    National Code,
    User Name,
    Password
    Age
*/

namespace Ui {
class UserEdit;
}

class UserEdit : public QDialog
{
    Q_OBJECT

public:
    explicit UserEdit(QWidget *parent = nullptr);
    ~UserEdit();

    QString getNationalCode() const;
    QString getFirstName() const;
    QString getLastName() const;
    QString getUserName() const;
    QString getPassword() const;
    int getAge() const;

public slots:
    void setNationalCode(const QString &value);
    void setFirstName(const QString &value);
    void setLastName(const QString &value);
    void setUserName(const QString &value);
    void setPassword(const QString &value);
    void setAge(int value);

signals:
    void nationalCodeChanged(const QString &value);
    void firstNameChanged(const QString &value);
    void lastNameChanged(const QString &value);
    void userNameChanged(const QString &value);
    void passwordChanged(const QString &value);
    void ageChanged(int value);

private:
    std::unique_ptr<Ui::UserEdit> ui;
};

#endif // USEREDIT_H
