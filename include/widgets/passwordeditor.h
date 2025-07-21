#ifndef PASSWORDEDITOR_H
#define PASSWORDEDITOR_H

#include <QWidget>

namespace Ui
{
    class PasswordEditor;
}

class PasswordEditor : public QWidget
{
    Q_OBJECT

public:
    explicit PasswordEditor(QWidget *parent = nullptr);
    ~PasswordEditor();

private:
    Ui::PasswordEditor *ui;
};

#endif // PASSWORDEDITOR_H
