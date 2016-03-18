#include "flatbutton.h"

FlatButton::FlatButton(QWidget *parent)
    : QAbstractButton(parent)
{
}

FlatButton::FlatButton(const QString &text, QWidget *parent)
    : QAbstractButton(parent)
{
    setText(text);
}

FlatButton::~FlatButton()
{
}
