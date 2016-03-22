#ifndef RAISEDBUTTON_H
#define RAISEDBUTTON_H

#include "flatbutton.h"

class RaisedButton : public FlatButton
{
    Q_OBJECT

public:
    explicit RaisedButton(QWidget *parent = 0);
    ~RaisedButton();
};

#endif // RAISEDBUTTON_H
