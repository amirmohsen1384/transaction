#include "include/widgets/abstractpanel.h"

AbstractPanel::AbstractPanel(QWidget *parent) : QWidget{parent}
{}

void AbstractPanel::reset() {}

void AbstractPanel::accept()
{
    emit accepted();
    reset();
}

void AbstractPanel::reject()
{
    emit rejected();
    reset();
}
