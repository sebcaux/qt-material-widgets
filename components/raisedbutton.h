#ifndef RAISEDBUTTON_H
#define RAISEDBUTTON_H

#include "flatbutton.h"

class RaisedButtonPrivate;

class RaisedButton : public FlatButton
{
    Q_OBJECT

public:
    explicit RaisedButton(QWidget *parent = 0);
    ~RaisedButton();

private:
    Q_DISABLE_COPY(RaisedButton)
    Q_DECLARE_PRIVATE(RaisedButton)
};

#endif // RAISEDBUTTON_H
