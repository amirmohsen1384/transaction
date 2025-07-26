#ifndef PASSWORDEDIT_H
#define PASSWORDEDIT_H

#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class PasswordEdit : public QWidget
{
    Q_OBJECT
public:
    explicit PasswordEdit(QWidget *parent = nullptr);

    bool hasFrame() const;
    bool isReadOnly() const;
    QString password() const;

    virtual QSize sizeHint() const;

public slots:
    void setFrame(bool value);
    void setReadOnly(bool value);
    void setPassword(const QString &value);

private slots:
    void updateIcon();
    void togglePasswordMode(bool toggle);

signals:
    void passwordEdited(const QString &value);
    void passwordChanged(const QString &value);

private:
    QLineEdit *editor = nullptr;
    QHBoxLayout *layout = nullptr;
    QPushButton *toggleButton = nullptr;
};

#endif // PASSWORDEDIT_H
