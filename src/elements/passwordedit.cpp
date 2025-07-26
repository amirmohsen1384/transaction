#include "include/elements/passwordedit.h"

PasswordEdit::PasswordEdit(QWidget *parent) : QWidget(parent)
{
    layout = new QHBoxLayout(this);

    editor = new QLineEdit(this);
    editor->setClearButtonEnabled(true);
    editor->setEchoMode(QLineEdit::Password);
    connect(editor, &QLineEdit::textEdited, this, &PasswordEdit::passwordEdited);
    connect(editor, &QLineEdit::textChanged, this, &PasswordEdit::passwordChanged);

    toggleButton = new QPushButton(this);
    connect(toggleButton, &QPushButton::toggled, this, &PasswordEdit::togglePasswordMode);
    toggleButton->setCheckable(true);
    toggleButton->setChecked(true);
    toggleButton->setFlat(true);

    layout->addWidget(editor);
    layout->addWidget(toggleButton);
    updateIcon();

    setFocusProxy(editor);
}

bool PasswordEdit::hasFrame() const
{
    return editor->hasFrame();
}

bool PasswordEdit::isReadOnly() const
{
    return editor->isReadOnly();
}

QString PasswordEdit::password() const
{
    return editor->text();
}

QSize PasswordEdit::sizeHint() const
{
    return editor->sizeHint();
}

void PasswordEdit::setFrame(bool value)
{
    editor->setFrame(value);
}

void PasswordEdit::setReadOnly(bool value)
{
    editor->setReadOnly(value);
}

void PasswordEdit::setPassword(const QString &value)
{
    editor->setText(value);
}

void PasswordEdit::updateIcon()
{
    if(editor->echoMode() == QLineEdit::Normal)
    {
        toggleButton->setIcon(QIcon(":/images/widgets/hide-password.png"));
    }
    else
    {
        toggleButton->setIcon(QIcon(":/images/widgets/show-password.png"));
    }
}

void PasswordEdit::togglePasswordMode(bool toggle)
{
    editor->setEchoMode(toggle ? QLineEdit::Password : QLineEdit::Normal);
    updateIcon();
}
