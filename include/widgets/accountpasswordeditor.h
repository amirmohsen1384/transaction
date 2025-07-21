#ifndef ACCOUNTPASSWORDEDITOR_H
#define ACCOUNTPASSWORDEDITOR_H

#include <QDialog>

namespace Ui {
class AccountPasswordEditor;
}

class AccountPasswordEditor : public QDialog
{
    Q_OBJECT

public:
    explicit AccountPasswordEditor(QWidget *parent = nullptr);
    ~AccountPasswordEditor();

    QString getPrimaryPassword() const;
    QString getSecondaryPassword() const;

public slots:
    void setPrimaryPassword(const QString &password);
    void setSecondaryPassword(const QString &password);

signals:
    void primaryPasswordChanged(const QString &password);
    void secondaryPasswordChanged(const QString &password);

private:
    std::unique_ptr<Ui::AccountPasswordEditor> ui;
};

#endif // ACCOUNTPASSWORDEDITOR_H
