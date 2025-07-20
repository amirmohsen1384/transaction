#ifndef ABSTRACTPANEL_H
#define ABSTRACTPANEL_H

#include <QDialog>

class AbstractPanel : public QDialog
{
    Q_OBJECT
public:
    Q_DISABLE_COPY_MOVE(AbstractPanel)
    explicit AbstractPanel(QWidget *parent = nullptr);

public slots:
    virtual void reset();
    virtual void accept();
    virtual void reject();

signals:
    void accepted();
    void rejected();
};

#endif // ABSTRACTPANEL_H
